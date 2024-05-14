#include "AuxFunctions.h"
#include "MutablePriorityQueue.h"
#include <cmath>

//static vector<vector<string>> graphs; ///< Adjacency matrix of the graph.
//vector<pair<float, float>> node_data; ///< Geographic coordinates of nodes.
//vector<bool> visited; ///< Tracks visited nodes during graph traversal. // não é preciso
//vector<int> parent; ///< Stores parent node of each node in the MST.
//vector<int> key; ///< Stores minimum key values of nodes.
//unsigned long num_vertices; ///< Number of vertices in the graph.

AuxFunctions::AuxFunctions() = default;

/*void AuxFunctions::test() {
    for (auto a : csvInfo::edgesGraph.getVertexSet()){
        cout << a->getInfo() << " - " << a->getLon() << " - " << a->getLat()<< endl;
        for(auto b : a->getAdj()) {
            cout << "Origem: " << b->getOrig()->getInfo() << "- Destino: " << b->getDest()->getInfo() << " - Weight: "
                 << b->getWeight() << endl;
        }
    }
}*/

/**
 * @brief Calculates the great-circle distance between two points on a sphere given their longitudes and latitudes.
 * This method uses the 'Haversine' formula to calculate the distance.
 *
 * Complexity: O(1)
 *
 * @param lat1
 * @param lon1
 * @param lat2
 * @param lon2
 * @return The great-circle distance between the two points in kilometers.
 */
double haversine(double lat1, double lon1, double lat2, double lon2) {

    lat1 = lat1 * M_PI / 180.00;
    lon1 = lon1 * M_PI / 180.00;
    lat2 = lat2 * M_PI / 180.0;
    lon2 = lon2 * M_PI / 180.0;


    double dlon = lon2 - lon1;
    double dlat = lat2 - lat1;
    double a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
    double c = 2 * asin(sqrt(a));


    double r = 6371;


    return c * r;
}

bool AuxFunctions::findEdge(int node1, int node2) {
    // Iterate over the adjacency list of node1
    for (auto vertex : csvInfo::edgesGraph.getVertexSet()) {
        if(vertex->getInfo() == std::to_string(node1)) {
            for (auto edge: vertex->getAdj()) {
                // If an edge exists between node1 and node2, return true
                if (edge->getDest()->getInfo() == std::to_string(node2)) {
                    return true;
                }
            }
        }
    }
    // If no edge exists between node1 and node2, return false
    return false;
}

double AuxFunctions::calculateTourDistance(const vector<string>& tour, const Graph& graph) {
    double distance = 0.0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        const string& source = tour[i];
        const string& destination = tour[i + 1];
        Edge* edge = graph.getEdge(source, destination);
        if (edge) {
            distance += edge->getWeight();
        }
    }
    return distance;
}

void AuxFunctions::backtrack(string current, vector<string>& tour, Graph& graph, double& minDistance, double& tourDistance, vector<string>& minTour) {
    Vertex* currentVertex = graph.findVertex(current);
    //cout << currentVertex->getInfo() << " ";

    if (tour.size() == graph.getVertexSet().size()+1 && currentVertex->getInfo() == "0") {
        if (tourDistance < minDistance) {
            minDistance = tourDistance;
            minTour = tour;
            for (auto a : tour){
                cout << a << " ";
            } cout << endl;
        }
        return;
    }
    for (const Edge* edge : currentVertex->getAdj()) {
        Vertex* nextVertex = edge->getDest();
        if (!nextVertex->isVisited()) {
            if (tourDistance + edge->getWeight() >= minDistance) {
                continue;
            }
            tour.push_back(edge->getDest()->getInfo());
            edge->getDest()->setVisited(true);
            tourDistance += edge->getWeight();
            backtrack(edge->getDest()->getInfo(), tour, graph, minDistance, tourDistance, minTour);
            tour.pop_back();
            edge->getDest()->setVisited(false);
            tourDistance -= edge->getWeight();
        }
    }
}



void AuxFunctions::primMST(vector<string>& prim) {
    vector<Vertex*> vertices = csvInfo::edgesGraph.getVertexSet();
    int num_vertices = vertices.size(); // Number of vertices in the graph
    if(num_vertices == 0){
        return;
    }

    for (auto vert : csvInfo::edgesGraph.getVertexSet()) {
        vert->setDist(std::numeric_limits<double>::infinity());
        vert->setVisited(false);
        vert->setPath(nullptr);
    }

    MutablePriorityQueue<Vertex> pq;

    Vertex* startVertex = csvInfo::edgesGraph.findVertex("0");
    startVertex->setDist(0);

    pq.insert(startVertex);


    while (!pq.empty()) {
        Vertex* u = pq.extractMin();
        u->setVisited(true);

        prim.push_back(u->getInfo());

        for (Edge* edge : u->getAdj()) {
            Vertex* v = edge->getDest();
            double weight = edge->getWeight();
            auto dist = v->getDist(); //antes de mudar a dist de v
            if (!v->isVisited() && weight < v->getDist()) {
                v->setDist(weight);
                v->setPath(edge);
                if (dist == std::numeric_limits<double>::infinity()) {
                    pq.insert(v);
                }
                else {
                    pq.decreaseKey(v);
                }
            }
        }
    }
}


void AuxFunctions::triangular(string node, vector<string>& tour, vector<string>& prim) {
    Vertex* v = csvInfo::edgesGraph.findVertex(node);
    v->setVisited(true);
    tour.push_back(node);

    Vertex* previousVertex = nullptr;
    Vertex* lastVertex = nullptr;
    double totalDistance = 0;
    for (auto nextNode : prim) {
        Vertex* nextVertex = csvInfo::edgesGraph.findVertex(nextNode);
        if(previousVertex != nullptr){
            if (!nextVertex->isVisited()) {
                double distance = haversine(v->getLat(), v->getLon(),nextVertex->getLat(), nextVertex->getLon());
                totalDistance += distance;
                if (totalDistance <= 2 * haversine(v->getLat(), v->getLon(),lastVertex->getLat(), lastVertex->getLon())) {
                    tour.push_back(nextNode);
                    nextVertex->setVisited(true);
                    previousVertex = v;
                    v = nextVertex;
                    lastVertex = v;
                } else {
                    tour.push_back(prim.front()); //back to the starting node
                    break;
                }
            }
        } else {
            previousVertex = nextVertex;
            tour.push_back(nextVertex->getInfo());
            lastVertex = nextVertex;
        }
    }
}


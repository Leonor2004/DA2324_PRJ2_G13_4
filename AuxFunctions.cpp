#include "AuxFunctions.h"
#include "MutablePriorityQueue.h"
#include <cmath>
#include <string>


AuxFunctions::AuxFunctions() = default;


double AuxFunctions::haversine(double lat1, double lon1, double lat2, double lon2) {

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


double AuxFunctions::calculateTourDistance(const vector<string>& tour, const Graph& graph, int graphN) {
    double distance = 0.0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        const string& source = tour[i];
        const string& destination = tour[i + 1];
        Edge* edge = graph.getEdge(source, destination);
        if (edge) {
            distance += edge->getWeight();
        } else if(graphN > 24){
            distance += haversine(graph.findVertex(source)->getLat(), graph.findVertex(source)->getLon(), graph.findVertex(destination)->getLat(), graph.findVertex(destination)->getLon());
        }
    }
    return distance;
}

void AuxFunctions::backtrack(string current, vector<string>& tour, Graph& graph, double& minDistance, double& tourDistance, vector<string>& minTour) {
    Vertex* currentVertex = graph.findVertex(current);

    if (tour.size() == graph.getVertexSet().size()+1 && currentVertex->getInfo() == "0") {
        if (tourDistance < minDistance) {
            minDistance = tourDistance;
            minTour = tour;
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
    int num_vertices = vertices.size();
    if(num_vertices == 0){
        return;
    }

    for (auto vert : csvInfo::edgesGraph.getVertexSet()) {
        vert->setDist(numeric_limits<double>::infinity());
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
            auto dist = v->getDist();
            if (!v->isVisited() && weight < v->getDist()) {
                v->setDist(weight);
                v->setPath(edge);
                if (dist == numeric_limits<double>::infinity()) {
                    pq.insert(v);
                }
                else {
                    pq.decreaseKey(v);
                }
            }
        }
    }
}


void AuxFunctions::triangular(string startNode, vector<string> &tour, vector<string> &prim) {
    Vertex* startVertex = csvInfo::edgesGraph.findVertex(startNode);
    startVertex->setVisited(true);

    Vertex* previousVertex = startVertex;

    for (const auto &nextNode : prim) {
        Vertex* nextVertex = csvInfo::edgesGraph.findVertex(nextNode);
        if (!nextVertex->isVisited()) {
            tour.push_back(nextVertex->getInfo());
            nextVertex->setVisited(true);
            previousVertex = nextVertex;
        }
    }

    tour.push_back(startNode);
}


string AuxFunctions::find_any_unvisited(const Graph &graph) {
    for (const auto &vertex : graph.getVertexSet()) {
        if (!vertex->isVisited()) {
            return vertex->getInfo();
        }
    }
    return "-1";
}


void AuxFunctions::other_heuristic(string current, vector<string> &tour, Graph &graph, double &minDistance, int tourDistance,
                                   vector<string> &minTour, int graphN){

    minTour.push_back(current);

    while(minTour.size() < graph.getVertexSet().size()){
        Vertex* currentVertex = graph.findVertex(current);
        if (currentVertex == nullptr) {
            cerr << "Error: Vertex " << current << " not found in the graph." << endl;
            return;
        }

        graph.findVertex(current)->setVisited(true);

        string nextVertex = nearest_neighbor(current, graph);

        if (nextVertex == "-1") {
            nextVertex = find_any_unvisited(graph);
            if (nextVertex == "-1" || (graphN > 24 && stoi(nextVertex) >= graphN)) {
                //cout << "Error: No unvisited neighbors found. Exiting." << endl;
                break;
            }
        }
        current = nextVertex;
        minTour.push_back(current);
    }

    if ((minTour.size()+1 == graph.getVertexSet().size() && graphN >24) || (minTour.size() == graph.getVertexSet().size())) {
        minTour.push_back(minTour.front());
    }

    minDistance = calculateTourDistance(minTour, graph , graphN);
    cout << "Minimum Tour using Nearest Neighbor algorithm:" << endl;
    int c = 0;
    for (auto a : minTour){
        cout << a << " ";
        c++;
        if (c>19){
            cout << endl;
            c = 0;
        }
    } cout << endl;

    cout << "Distancia: " << minDistance << endl;
}


string AuxFunctions::nearest_neighbor(string current, Graph &graph){
    string nearest = "-1";
    double min_distance=numeric_limits<double>::infinity();

    Vertex* currentVertex = graph.findVertex(current);

    if (currentVertex == nullptr) {
        cerr << "Error: Vertex " << current << " not found in the graph." << endl;
        return nearest;
    } else {
        for (auto edge : currentVertex->getAdj()){
            if (edge->getDest() == nullptr) {
                cerr << "Error: Destination vertex in edge is null." << endl;
                continue;

            }
            if(!edge->getDest()->isVisited() && edge->getWeight() < min_distance){
                nearest = edge->getDest()->getInfo();
                min_distance= edge->getWeight();
            }
        }
    }
    return nearest;
}
#include "AuxFunctions.h"
#include <cmath>

static vector<std::vector<string>> graphs; ///< Adjacency matrix of the graph.
vector<std::pair<float, float>> node_data; ///< Geographic coordinates of nodes.
vector<bool> visited; ///< Tracks visited nodes during graph traversal.
vector<int> parent; ///< Stores parent node of each node in the MST.
vector<int> key; ///< Stores minimum key values of nodes.
unsigned long num_vertices; ///< Number of vertices in the graph.

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


void AuxFunctions::backtrack(string current, vector<string>& tour, Graph& graph, double& minDistance, double& tourDistance, vector<vector<string>>& minTour) {
    //cout << "Current :" << current << endl;
    Vertex* currentVertex = graph.findVertex(current);

    if (tour.size() == graph.getVertexSet().size() && currentVertex->getInfo() == "0") {
        if (tourDistance < minDistance) {
            minDistance = tourDistance;
            minTour.clear();
            minTour.push_back(tour);
        } else if (tourDistance == minDistance) {
            minTour.push_back(tour);
        }
        return;
    } else {
        for (const Edge* edge : currentVertex->getAdj()) {
            Vertex* nextVertex = edge->getDest();
            if (!nextVertex->isVisited()) {
                if (tourDistance + edge->getWeight() >= minDistance) {
                    continue;
                }
                tour.push_back(nextVertex->getInfo());
                nextVertex->setVisited(true);
                tourDistance += edge->getWeight();
                backtrack(nextVertex->getInfo(), tour, graph, minDistance, tourDistance ,minTour);
                tour.pop_back();
                nextVertex->setVisited(false);
                tourDistance -= edge->getWeight();
            }
        }
    }
}



void AuxFunctions::primMST() {
    // Clear existing data
    graphs.clear();
    node_data.clear();
    visited.clear();
    parent.clear();
    key.clear();

    // Get the number of vertices
    num_vertices = csvInfo::edgesGraph.getVertexSet().size();

    // Initialize node_data with geographic coordinates of nodes
    for (int i = 0; i < num_vertices; ++i) {
        node_data.emplace_back(csvInfo::edgesGraph.getVertexSet()[i]->getLat(), csvInfo::edgesGraph.getVertexSet()[i]->getLon());
    }

    // Initialize visited, parent, and key vectors
    visited.resize(num_vertices, false);
    parent.resize(num_vertices, -1);
    key.resize(num_vertices, INT_MAX);

    // Convert the edgesGraph from csvInfo to the adjacency matrix format used by TSP
    std::map<std::string, int> vertex_to_index;
    for (int i = 0; i < num_vertices; ++i) {
        vertex_to_index[csvInfo::edgesGraph.getVertexSet()[i]->getInfo()] = i;
    }

    for (const auto& vertex : csvInfo::edgesGraph.getVertexSet()) {
        std::vector<string> row(num_vertices, to_string(INT_MAX));
        for (const auto& edge : vertex->getAdj()) {
            row[vertex_to_index[edge->getDest()->getInfo()]] = to_string(edge->getWeight());
        }
        graphs.push_back(row);
    }


    bool hasEdges = false;
    for (const auto& row : graphs) {
        for (string weight : row) {
            if (stoi(weight) != INT_MAX) {
                hasEdges = true;
                break;
            }
        }
        if (hasEdges) break;
    }
    if (!hasEdges) return;

    key[0] = 0;

    for (int count = 0; count < num_vertices - 1; count++) {
        int u = minKey();
        visited[u] = true;

        for (int v = 0; v < num_vertices; v++) {
            if (!visited[v] && AuxFunctions::findEdge(parent[v], v)) {
                bool useHaversine = !(node_data[u].first == 0 && node_data[u].second == 0) && !(node_data[v].first == 0 && node_data[v].second == 0);
                int edgeWeight = stoi(graphs[u][v]);
                double distance = useHaversine && edgeWeight == INT_MAX ? haversine(node_data[u].first, node_data[u].second, node_data[v].first, node_data[v].second) : edgeWeight;
                if (distance < key[v]) {
                    parent[v] = u;
                    key[v] = distance;
                }
            }
        }
    }


    std::fill(visited.begin(), visited.end(), false);
}


int AuxFunctions::minKey() {
    int min = INT_MAX, min_index;

    for (int v = 0; v < num_vertices; v++)
        if (!visited[v] && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}


void AuxFunctions::dfs(int node, vector<int>& tour) {
    visited[node] = true;
    tour.push_back(node);

    for (int i = 0; i < graphs[node].size(); ++i) {
        if (!visited[i] && AuxFunctions::findEdge(node, i)) {
            bool useHaversine = !(node_data[node].first == 0 && node_data[node].second == 0) && !(node_data[i].first == 0 && node_data[i].second == 0);
            int edgeWeight = stoi(graphs[node][i]);
            double distance = useHaversine && edgeWeight == INT_MAX ? haversine(node_data[node].first, node_data[node].second, node_data[i].first, node_data[i].second) : edgeWeight;
            if (distance != INT_MAX) {
                dfs(i, tour);
            }
        }
    }
}

#include "TSP.h"
#include "cmath"
#include "csvInfo.h"

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

    lat1 = lat1 * M_PI / 180.0;
    lon1 = lon1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;
    lon2 = lon2 * M_PI / 180.0;


    double dlon = lon2 - lon1;
    double dlat = lat2 - lat1;
    double a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
    double c = 2 * asin(sqrt(a));


    double r = 6371;


    return c * r;
}

TSP::TSP(csvInfo& csv_info, const std::vector<std::pair<double, double>>& node_data)
        : node_data(node_data),
          visited(csv_info.edgesGraph.getVertexSet().size(), false),
          parent(csv_info.edgesGraph.getVertexSet().size(), -1),
          key(csv_info.edgesGraph.getVertexSet().size(), INT_MAX),
          num_vertices(csv_info.edgesGraph.getVertexSet().size()) {
    // Convert the edgesGraph from csvInfo to the adjacency matrix format used by TSP
    std::map<std::string, int> vertex_to_index;
    for (int i = 0; i < csv_info.edgesGraph.getVertexSet().size(); ++i) {
        vertex_to_index[csv_info.edgesGraph.getVertexSet()[i]->getInfo()] = i;
    }

    for (const auto& vertex : csv_info.edgesGraph.getVertexSet()) {
        std::vector<int> row(num_vertices, INT_MAX);
        for (const auto& edge : vertex->getAdj()) {
            row[vertex_to_index[edge->getDest()->getInfo()]] = edge->getWeight();
        }
        graph.push_back(row);
    }
}

void TSP::primMST() {
    bool hasEdges = false;
    for (const auto& row : graph) {
        for (int weight : row) {
            if (weight != INT_MAX) {
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

        for (int v = 0; v < num_vertices; v++)
            if (!visited[v] && (graph[u][v] != INT_MAX ? graph[u][v] : haversine(node_data[u].first, node_data[u].second, node_data[v].first, node_data[v].second)) < key[v])
                parent[v] = u, key[v] = graph[u][v] != INT_MAX ? graph[u][v] : haversine(node_data[u].first, node_data[u].second, node_data[v].first, node_data[v].second);
    }

    std::fill(visited.begin(), visited.end(), false);
}


int TSP::minKey() {
    int min = INT_MAX, min_index;

    for (int v = 0; v < num_vertices; v++)
        if (!visited[v] && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}


void TSP::dfs(int node) {
    visited[node] = true;
    tour.push_back(node);

    for (int i = 0; i < graph[node].size(); ++i) {
        if (!visited[i] && (graph[node][i] != INT_MAX || haversine(node_data[node].first, node_data[node].second, node_data[i].first, node_data[i].second) != INT_MAX)) {
            dfs(i);
        }
    }
}


std::vector<int> TSP::tsp_2_approximation() {
    // Clear the tour vector
    tour.clear();

    // Create a minimum spanning tree (MST) of the graph
    primMST();

    // Perform a depth-first search (DFS) on the MST to generate a tour
    dfs(0);

    // Return to the starting city to complete the tour
    tour.push_back(0);

    return tour;
}
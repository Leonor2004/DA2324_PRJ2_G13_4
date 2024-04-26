#include "TSP.h"
#include "cmath"

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

TSP::TSP(const std::vector<std::vector<int>>& graph, const std::vector<std::pair<double, double>>& node_data)
        : graph(graph),
          node_data(node_data),
          visited(graph.size(), false),
          parent(graph.size(), -1),
          key(graph.size(), INT_MAX),
          num_vertices(graph.size()) {}

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
    tour.clear();

    dfs(0);
    tour.push_back(0);

    return tour;
}

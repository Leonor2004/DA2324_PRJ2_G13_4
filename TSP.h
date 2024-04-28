#ifndef DA2324_PRJ2_G13_4_TSP_H
#define DA2324_PRJ2_G13_4_TSP_H

#include <vector>
#include <climits>
#include "csvInfo.h"


/**
 * @class TSP
 *
 * @brief Represents a Travelling Salesman Problem (TSP).
 */
class TSP {
private:
    std::vector<std::vector<int>> graph;
    std::vector<std::pair<double, double>> node_data;
    std::vector<bool> visited;
    std::vector<int> parent;
    std::vector<int> key;
    std::vector<int> tour;
    int num_vertices;

public:
    /**
     * @brief Constructor for the TSP class.
     *
     * Complexity: ???
     *
     * @param graph The adjacency matrix representation of the graph.
     * @param node_data The geographic data of the nodes.
     */
    TSP(csvInfo& csv_info, const std::vector<std::pair<double, double>>& node_data);
    /**
     * @brief This method creates a minimum spanning tree (MST) of the graph.
     *
     * Complexity: ???
     */
    void primMST();

    /**
     * @brief This method returns the node with the minimum key value that hasn't been visited yet.
     *
     * Complexity: ???
     *
     * @return The index of the node with the minimum key value.
     */
    int minKey();

    /**
     * @brief This method performs a depth-first search (DFS) on the MST.
     *
     * Complexity: ???
     *
     * @param node The node to start the DFS from.
     */
    void dfs(int node);

    /**
     * @brief This method solves the TSP using a 2-approximation algorithm.
     *
     * Complexity: ???
     *
     * @return A vector representing the tour of the TSP.
     */
    std::vector<int> tsp_2_approximation();
};

#endif //DA2324_PRJ2_G13_4_TSP_H



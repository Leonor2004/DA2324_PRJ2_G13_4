#ifndef DA2324_PRJ2_G13_4_TSP_H
#define DA2324_PRJ2_G13_4_TSP_H

#include <vector>
#include <climits>
#include "csvInfo.h"


/**
 * @class TSP
 * @brief Represents a Travelling Salesman Problem (TSP).
 *
 * This class contains methods and data members needed to solve a TSP using a 2-approximation algorithm.
 */
class TSP {
private:
    std::vector<std::vector<int>> graph; ///< Adjacency matrix of the graph.
    std::vector<std::pair<double, double>> node_data; ///< Geographic coordinates of nodes.
    std::vector<bool> visited; ///< Tracks visited nodes during graph traversal.
    std::vector<int> parent; ///< Stores parent node of each node in the MST.
    std::vector<int> key; ///< Stores minimum key values of nodes.
    std::vector<int> tour; ///< Stores nodes in the order they are visited in the tour.
    int num_vertices; ///< Number of vertices in the graph.

public:
    /**
     * @brief Constructor for the TSP class.
     *
     * Complexity: O(n^2)
     *
     * @param csv_info The information from the CSV file.
     * @param node_data The geographic data of the nodes.
     */
    TSP(csvInfo& csv_info, const std::vector<std::pair<double, double>>& node_data);

    /**
     * @brief This method creates a minimum spanning tree (MST) of the graph.
     *
     * Complexity: O(n^2)
     */
    void primMST();

    /**
     * @brief This method returns the node with the minimum key value that hasn't been visited yet.
     *
     * Complexity: O(n)
     *
     * @return The index of the node with the minimum key value.
     */
    int minKey();

    /**
     * @brief This method performs a depth-first search (DFS) on the MST.
     *
     * Complexity: O(n)
     *
     * @param node The node to start the DFS from.
     */
    void dfs(int node);

    /**
     * @brief This method solves the TSP using a 2-approximation algorithm.
     *
     * Complexity: O(n^2)
     *
     * @return A vector representing the tour of the TSP.
     */
    std::vector<int> tsp_2_approximation();
};

#endif //DA2324_PRJ2_G13_4_TSP_H



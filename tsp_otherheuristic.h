//
// Created by Tomás Rodrigues on 28/04/2024.
//

#ifndef DA2324_PRJ2_G13_4_TSP_OTHERHEURISTIC_H
#define DA2324_PRJ2_G13_4_TSP_OTHERHEURISTIC_H


#include <vector>
#include <limits>
#include <string>
#include <algorithm>
#include "Graph.h"
#include "csvInfo.h"

class tsp_otherheuristic {
private:
    std::vector<std::vector<int>> graph;
    std::vector<bool> visited;
    std::vector<std::pair<double, double>> node_data;

public:
        /**
    * @brief Constructor for the tsp_otherheuristic class.
    *
    * Initializes the adjacency matrix and node data based on the provided Graph object.
    *
    * Complexity: O(n^2), where n is the number of vertices in the graph.
    *
    * @param edgesGraph The Graph object representing the problem to be solved.
    */
    tsp_otherheuristic(const Graph& edgesGraph): visited(edgesGraph.getVertexSet().size(), false) {
        // Initialize the adjacency matrix and node data
        graph.resize(edgesGraph.getVertexSet().size(), std::vector<int>(edgesGraph.getVertexSet().size(), 0));
        node_data.resize(edgesGraph.getVertexSet().size());

        // Fill the adjacency matrix and node data
        for (const auto& vertex : edgesGraph.getVertexSet()) {

            int id = std::stoi(vertex->getInfo());

            node_data[id] = std::make_pair(vertex->getLon(), vertex->getLat());

            for (const auto& edge : vertex->getAdj()) {
                graph[id][std::stoi(edge->getDest()->getInfo())] = static_cast<int>(edge->getWeight());
            }
        }
    }


        /**
     * @brief Finds the nearest unvisited neighbor to a given node.
     *
     * This function iterates over all nodes in the graph, checking if they have been visited and if they are connected to the current node.
     * It returns the index of the nearest unvisited neighbor.
     *
     * Complexity: O(n), where n is the number of vertices in the graph.
     *
     * @param currentNode The index of the current node.
     * @return The index of the nearest unvisited neighbor.
     */
  int nearestNeighbor(int currentNode);


        /**
      * @brief Solves the Travelling Salesman Problem (TSP) using a nearest neighbor heuristic.
      *
      * This function starts at a given node, then repeatedly visits the nearest unvisited node until all nodes have been visited.
      * It then returns to the start node to complete the cycle.
      *
      * Complexity: O(n^2), where n is the number of vertices in the graph.
      *
      * @param startNode The index of the starting node.
      * @return A vector of integers representing the path taken.
      */
    std::vector<int> tsp(int startNode);
};

#endif //DA2324_PRJ2_G13_4_TSP_OTHERHEURISTIC_H

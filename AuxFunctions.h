#ifndef DA2324_PRJ2_G13_4_AUXFUNCTIONS_H
#define DA2324_PRJ2_G13_4_AUXFUNCTIONS_H

#include "csvInfo.h"

/**
 * @brief Auxiliar Functions
 */
class AuxFunctions {
private:
public:

    /**
     * @brief Default constructor
     *
     * Complexity: O(1)
     */
    AuxFunctions();

    //static void test();

    /**
     * @brief Find an edge in the edges graph
     *
     * Complexity: O(n^2)
     *
     * @param node1 : Starting node
     * @param node2 : Ending node
     * @return True of the edge exists and false if it doesn't
     */
    static bool findEdge(int node1, int node2);


    /**
     * @brief Calculate tour distance
     *
     * Complexity: O(n^2)
     *
     * @param tour : Tour
     * @param graph : Graph
     * @return Tour distance
     */
    static double calculateTourDistance(const vector<string> &tour, const Graph &graph);

    //topico 1
    /**
     * @brief Backtrack Algorithm
     *
     * Complexity: O(n^3)
     *
     * @param current : Current node
     * @param tour : Tour
     * @param graph : Graph
     * @param minDistance : Minimum Distance
     * @param minTour : Minimum Distance Tours
     */
    static void backtrack(string current, vector<string> &tour, Graph &graph, double &minDistance, double &tourDistance,
                          vector<string> &minTour);

    //topico 2
    /**
     * @brief This method creates a minimum spanning tree (MST) of the graph.
     *
     * Complexity: O(n^2)
     *
     * COMPLETAR ???
     */
    static void primMST(vector<string> &prim);

    /**
     * @brief This method performs a depth-first search (DFS) on the MST.
     *
     * Complexity: O(n)
     *
     * @param node The node to start the DFS from.
     */
    static void triangular(string node, vector<string> &tour, vector<string> &prim);


    
    /**
     * @brief Executes an alternative heuristic for the TSP problem using the nearest neighbor approach.
     *
     * This function implements the nearest neighbor heuristic as an alternative approach for solving the
     * Travelling Salesman Problem (TSP). Starting from a given node, it iteratively selects the nearest
     * unvisited node as the next node to visit until all nodes have been visited.
     *
     * @param current The starting node for the TSP.
     * @param tour A vector to store the nodes in the order they are visited.
     * @param graph The graph representing the TSP.
     * @param minDistance The minimum distance of the tour found so far.
     * @param tourDistance The total distance of the current tour.
     * @param minTour A vector to store the nodes of the minimum tour found so far.
     *
     * Complexity: O(n^2)
     */
    static void other_heuristic(string current, vector<string> &tour, Graph &graph, double &minDistance, int tourDistance,
                                vector<string> &minTour);



    /**
     * @brief Finds the nearest unvisited neighbor to a given node.
     *
     * This function finds the nearest unvisited neighbor to a given node in the graph.
     * The "nearest" neighbor is determined based on the weight of the edge connecting the nodes.
     *
     * @param current The node for which to find the nearest neighbor.
     * @param graph The graph in which to find the neighbor.
     *
     * @return The information of the nearest unvisited neighbor. If no unvisited neighbor exists, returns "-1".
     *
     * Complexity: O(n)
     */
    static string nearest_neighbor(string current, Graph &graph);
};
#endif //DA2324_PRJ2_G13_4_AUXFUNCTIONS_H

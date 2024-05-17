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

    /**
     * @brief Calculates the great-circle distance between two points on a sphere given their longitudes and latitudes.
     * This method uses the 'Haversine' formula to calculate the distance.
     *
     * Complexity: O(1)
     *
     * @param lat1 : Latitude of node 1
     * @param lon1 : Longitude of node 1
     * @param lat2 : Latitude of node 2
     * @param lon2 : Longitude of node 2
     * @return The great-circle distance between the two points in kilometers.
     */
    static double haversine(double lat1, double lon1, double lat2, double lon2);

    /**
     * @brief Calculate tour distance
     *
     * Complexity: O(n^3)
     *
     * @param tour : Tour
     * @param graph : Graph
     * @param graphN : Graph number
     * @return Tour distance
     */
    static double calculateTourDistance(const vector<string> &tour, const Graph &graph, int graphN);

    /**
     * @brief Backtrack Algorithm
     *
     * Complexity: O(n! * n^2)
     *
     * @param current : Current node
     * @param tour : Tour
     * @param graph : Graph
     * @param minDistance : Minimum Distance
     * @param minTour : Minimum Distance Tours
     */
    static void backtrack(string current, vector<string> &tour, Graph &graph, double &minDistance, double &tourDistance, vector<string> &minTour);

    /**
     * @brief This method creates a minimum spanning tree (MST) of the graph.
     *
     * Complexity: O(n*log(n))
     *
     * @param prim : Vector of strings to save the solution
     */
    static void primMST(vector<string> &prim);

    /**
     * @brief This method performs a depth-first search (DFS) on the MST.
     *
     * Complexity: O(n)
     *
     * @param node The node to start the DFS from
     * @param tour : Tour
     * @param prim : Vector of strings with the Prim solution
     */
    static void triangular(string node, vector<string> &tour, vector<string> &prim);

    /**
     * @brief Find any unvisited Vertex
     *
     * Complexity: O(n)
     *
     * @param graph : Edges graph
     * @return Vertex id
     */
    static string find_any_unvisited(const Graph &graph);

    /**
     * @brief Executes an alternative heuristic for the TSP problem using the nearest neighbor approach.
     *
     * This function implements the nearest neighbor heuristic as an alternative approach for solving the
     * Travelling Salesman Problem (TSP). Starting from a given node, it iteratively selects the nearest
     * unvisited node as the next node to visit until all nodes have been visited.
     *
     * Complexity: O(n^2)
     *
     * @param current The starting node for the TSP.
     * @param tour A vector to store the nodes in the order they are visited.
     * @param graph The graph representing the TSP.
     * @param minDistance The minimum distance of the tour found so far.
     * @param tourDistance The total distance of the current tour.
     * @param minTour A vector to store the nodes of the minimum tour found so far.
     */
    static void other_heuristic(string current, vector<string> &tour, Graph &graph, double &minDistance, int tourDistance, vector<string> &minTour, int graphN);

    /**
     * @brief Finds the nearest unvisited neighbor to a given node.
     *
     * This function finds the nearest unvisited neighbor to a given node in the graph.
     * The "nearest" neighbor is determined based on the weight of the edge connecting the nodes.
     *
     * Complexity: O(n)
     *
     * @param current The node for which to find the nearest neighbor.
     * @param graph The graph in which to find the neighbor.
     * @return The information of the nearest unvisited neighbor. If no unvisited neighbor exists, returns "-1".
     */
    static string nearest_neighbor(string current, Graph &graph);

};
#endif //DA2324_PRJ2_G13_4_AUXFUNCTIONS_H

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
    static void backtrack(string current, vector<string> &tour, Graph &graph, double &minDistance,double& tourDistance, vector<vector<string>> &minTour);

    //topico 2
    /**
     * @brief This method creates a minimum spanning tree (MST) of the graph.
     *
     * Complexity: O(n^2)
     */
    static void primMST();

    /**
     * @brief This method returns the node with the minimum key value that hasn't been visited yet.
     *
     * Complexity: O(n)
     *
     * @return The index of the node with the minimum key value.
     */
    static int minKey();

    /**
     * @brief This method performs a depth-first search (DFS) on the MST.
     *
     * Complexity: O(n)
     *
     * @param node The node to start the DFS from.
     */
     static void dfs(int node, vector<int> &tour);

};

#endif //DA2324_PRJ2_G13_4_AUXFUNCTIONS_H

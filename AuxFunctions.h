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
     * @brief Calculate tour distance
     *
     * Complexity: O(n^2)
     *
     * @param tour : Tour
     * @param graph : Graph
     * @return Tour distance
     */
    static double calculateTourDistance(const vector<string> &tour, const Graph &graph);

    /**
     * @brief Backtrack Algorithm
     *
     * Complexity: ???
     *
     * @param current : Current node
     * @param tour : Tour
     * @param graph : Graph
     * @param minDistance : Minimum Distance
     * @param minTour : Minimum Distance Tours
     */
    static void backtrack(string current, vector<string> &tour, Graph &graph, double &minDistance, vector<vector<string>> &minTour);
};

#endif //DA2324_PRJ2_G13_4_AUXFUNCTIONS_H

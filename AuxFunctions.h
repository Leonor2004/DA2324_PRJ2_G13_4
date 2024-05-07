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
     * @brief ???
     *
     * Complexity: ???
     *
     * @param tour
     * @param graph
     * @return
     */
    static double calculateTourDistance(const vector<string> &tour, const Graph &graph);

    /**
     * @brief ???
     *
     * Complexity: ???
     *
     * @param current
     * @param tour
     * @param graph
     * @param minDistance
     * @param minTour
     */
    static void backtrack(string current, vector<string> &tour, Graph &graph, double &minDistance, vector<vector<string>> &minTour);
};

#endif //DA2324_PRJ2_G13_4_AUXFUNCTIONS_H

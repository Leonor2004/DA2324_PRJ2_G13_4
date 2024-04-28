#ifndef DA2324_PRJ2_G13_4_CSVINFO_H
#define DA2324_PRJ2_G13_4_CSVINFO_H

#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include "Graph.h"

/**
 * @brief Gets the info from the csv's.
 */
class csvInfo {
private:
public:
    /**
     * @brief Default constructor
     */
    csvInfo();

    /**
     * @brief Graph
     */
    static Graph edgesGraph;

    /**
     * @brief Vertex Vector
     */
    static vector<Vertex> vertexVector;

    /**
     * Vertex Set
     */
    static std::set<std::string> vertexSet;

    /**
     * @brief Creation of the graph
     *
     * Complexity: O(n^2)
     *
     * @param graph : Graph the user chose
     */
    static void createGraph(int graph);

    /**
     * @brief Longitude and latitude of Extra Fully Connected Graphs
     *
     * Complexity: ???
     *
     * @param graph : Number of edges
     */
    static void createNodes(int graph);

};

#endif //DA2324_PRJ2_G13_4_CSVINFO_H

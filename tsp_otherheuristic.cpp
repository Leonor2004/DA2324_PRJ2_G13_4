//
// Created by Tomás Rodrigues on 28/04/2024.
//

#include "tsp_otherheuristic.h"


int tsp_otherheuristic::nearestNeighbor(int currentNode) {
    int nearest = -1;
    int shortestDistance = std::numeric_limits<int>::max();

    for (int i = 0; i < graph.size(); i++) {
        if (!visited[i] && graph[currentNode][i] && graph[currentNode][i] < shortestDistance) {
            nearest = i;
            shortestDistance = graph[currentNode][i];
        }
    }
    return nearest;
}

std::vector<int> tsp_otherheuristic::tsp(int startNode) {
    visited[startNode] = true;

    int currentNode = startNode;
    std::vector<int> path;
    path.push_back(currentNode);

    for (int i = 0; i < graph.size() - 1; i++) {
        int nearest = nearestNeighbor(currentNode);
        visited[nearest] = true;
        path.push_back(nearest);
        currentNode = nearest;
    }

    // Return to the starting node to complete the cycle
    path.push_back(startNode);

    return path;
}
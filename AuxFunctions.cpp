#include "AuxFunctions.h"
#include <cmath>

AuxFunctions::AuxFunctions() = default;

/*void AuxFunctions::test() {
    for (auto a : csvInfo::edgesGraph.getVertexSet()){
        cout << a->getInfo() << " - " << a->getLon() << " - " << a->getLat()<< endl;
        for(auto b : a->getAdj()) {
            cout << "Origem: " << b->getOrig()->getInfo() << "- Destino: " << b->getDest()->getInfo() << " - Weight: "
                 << b->getWeight() << endl;
        }
    }
}*/



double AuxFunctions::calculateTourDistance(const vector<string>& tour, const Graph& graph) {
    double distance = 0.0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        const string& source = tour[i];
        const string& destination = tour[i + 1];
        Edge* edge = graph.getEdge(source, destination);
        if (edge) {
            distance += edge->getWeight();
        }
    }
    return distance;
}

void AuxFunctions::backtrack(string current, vector<string>& tour, Graph& graph, double& minDistance, vector<vector<string>>& minTour) {
    tour.push_back(current);
    Vertex* currentVertex = graph.findVertex(current);
    currentVertex->setVisited(true);

    if (tour.size() == graph.getVertexSet().size()) {
        tour.push_back("0");
        double distance = calculateTourDistance(tour, graph);
        if (distance < minDistance) {
            minDistance = distance;
            minTour.clear();
            minTour.push_back(tour);
        } else if (distance == minDistance) {
            minTour.push_back(tour);
        }
        tour.pop_back(); // Remove "0" added
    } else {
        for (const Edge* edge : currentVertex->getAdj()) {
            Vertex* nextVertex = edge->getDest();
            if (!nextVertex->isVisited()) {
                backtrack(nextVertex->getInfo(), tour, graph, minDistance, minTour);
            }
        }
    }

    currentVertex->setVisited(false);
    tour.pop_back();
}


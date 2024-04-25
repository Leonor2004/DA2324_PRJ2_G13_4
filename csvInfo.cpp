#include <map>
#include "csvInfo.h"


csvInfo::csvInfo() = default;

Graph csvInfo::edgesGraph;
vector<Vertex> csvInfo::vertexVector;
std::set<std::string> csvInfo::vertexSet;

void csvInfo::createGraph(string graph) {
    vertexSet.clear();
    vertexVector.clear();
    fstream file;
    if(graph == "a"){file.open("../Datasets/Toy-Graphs/Toy-Graphs/shipping.csv");}
    else if(graph == "b"){file.open("../Datasets/Toy-Graphs/Toy-Graphs/stadiums.csv");}
    else if(graph == "c"){file.open("../Datasets/Toy-Graphs/Toy-Graphs/tourism.csv");}

    if (!file.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return;
    }

    string line;
    string origem;
    string destino;
    string distancia;
    int aux = 1;

    getline(file, line);    // discard header line
    while(getline(file, line)) {
        stringstream s(line);
        getline(s, origem, ',');
        getline(s, destino, ',');
        getline(s, distancia);

        bool prov = edgesGraph.addVertex(origem,aux - 1);
        if(prov) {aux++;}
        prov = edgesGraph.addVertex(destino, aux - 1);
        if(prov) {aux++;}
        edgesGraph.addEdge(origem, destino, stod(distancia));
        //edgesGraph.addBidirectionalEdge(origem, destino, stod(distancia));
    }
    file.close();
}

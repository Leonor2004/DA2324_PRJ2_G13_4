#include <map>
#include "csvInfo.h"


csvInfo::csvInfo() = default;

Graph csvInfo::edgesGraph;
vector<Vertex> csvInfo::vertexVector;
set<string> csvInfo::vertexSet;

void csvInfo::createGraph(int graph) {
    fstream file;
    if(graph == 13){
        file.open("../Datasets/Toy-Graphs/Toy-Graphs/shipping.csv");
        vertexSet.clear();
        vertexVector.clear();
    } else if(graph == 10){
        file.open("../Datasets/Toy-Graphs/Toy-Graphs/stadiums.csv");
        vertexSet.clear();
        vertexVector.clear();
    } else if(graph == 4){
        file.open("../Datasets/Toy-Graphs/Toy-Graphs/tourism.csv");
        vertexSet.clear();
        vertexVector.clear();
    } else if(graph == 25){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_25.csv");}
    else if(graph == 50){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_50.csv");}
    else if(graph == 75){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_75.csv");}
    else if(graph == 100){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_100.csv");}
    else if(graph == 200){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_200.csv");}
    else if(graph == 300){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_300.csv");}
    else if(graph == 400){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_400.csv");}
    else if(graph == 500){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_500.csv");}
    else if(graph == 600){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_600.csv");}
    else if(graph == 700){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_700.csv");}
    else if(graph == 800){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_800.csv");}
    else if(graph == 900){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_900.csv");}
    else if(graph == 1000){file.open("../Datasets/Real-world Graphs/Real-world Graphs/graph1/edges.csv");}
    else if(graph == 5000){file.open("../Datasets/Real-world Graphs/Real-world Graphs/graph2/edges.csv");}
    else if(graph == 10000){file.open("../Datasets/Real-world Graphs/Real-world Graphs/graph3/edges.csv");}

    if (!file.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return;
    }

    string line;
    string origem;
    string destino;
    string distancia;
    int aux = 1;

    if(graph < 24 || graph > 950){getline(file, line);} // discard header line
    while(getline(file, line)) {
        stringstream s(line);
        getline(s, origem, ',');
        getline(s, destino, ',');
        getline(s, distancia);

        bool prov = false;
        if(graph < 24) {
            prov = edgesGraph.addVertex(origem, aux - 1, 0, 0);
            if (prov) {
                vertexSet.insert(origem);
                vertexVector.push_back(Vertex(origem, aux - 1, 0, 0));
                aux++;
            }
            prov = edgesGraph.addVertex(destino, aux - 1, 0, 0);
            if (prov) {
                vertexSet.insert(destino);
                vertexVector.push_back(Vertex(destino, aux - 1, 0, 0));
                aux++;
            }

        }
        if(graph < 24){
            edgesGraph.addEdge(origem, destino, stod(distancia));
            edgesGraph.addEdge(destino, origem, stod(distancia));
        } else {edgesGraph.addEdge(origem, destino, stod(distancia));}
    }
    file.close();
}

void csvInfo::createNodes(int graph) {
    vertexSet.clear();
    vertexVector.clear();
    fstream file;
    if (graph < 1000){
        file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv");
    } else if(graph == 1000){file.open("../Datasets/Real-world Graphs/Real-world Graphs/graph1/nodes.csv");}
    else if(graph == 5000){file.open("../Datasets/Real-world Graphs/Real-world Graphs/graph2/nodes.csv");}
    else if(graph == 10000){file.open("../Datasets/Real-world Graphs/Real-world Graphs/graph3/nodes.csv");}

    if (!file.is_open()) {
        cerr << "Error: Unable to open the nodes file." << endl;
        return;
    }

    string line;
    string node;
    string longitude;
    string latitude;
    int aux = 0;
    getline(file, line); // discard header line
    while(getline(file, line) && aux-1<graph) {
        stringstream s(line);
        getline(s, node, ',');
        getline(s, longitude, ',');
        getline(s, latitude);

        double convertedLat = stod(latitude);
        double convertedLon = stod(longitude);

        bool prov = edgesGraph.addVertex(node,aux, convertedLon,convertedLat);
        if(prov) {
            vertexSet.insert(node);
            vertexVector.push_back(Vertex(node, aux - 1, convertedLon, convertedLat));
            aux++;
        }
    }
    file.close();
}



#include <map>
#include "csvInfo.h"


csvInfo::csvInfo() = default;

Graph csvInfo::edgesGraph;
vector<Vertex> csvInfo::vertexVector;
std::set<std::string> csvInfo::vertexSet;

void csvInfo::createGraph(int graph) {

    fstream file;
    if(graph == 1){
        file.open("../Datasets/Toy-Graphs/Toy-Graphs/shipping.csv");
        vertexSet.clear();
        vertexVector.clear();
    } else if(graph == 2){
        file.open("../Datasets/Toy-Graphs/Toy-Graphs/stadiums.csv");
        vertexSet.clear();
        vertexVector.clear();
    } else if(graph == 3){
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

    if (!file.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return;
    }

    string line;
    string origem;
    string destino;
    string distancia;
    int aux = 1;

    if(graph < 4){getline(file, line);}    // discard header line
    while(getline(file, line)) {
        stringstream s(line);
        getline(s, origem, ',');
        getline(s, destino, ',');
        getline(s, distancia);

        bool prov = false;
        if(graph < 4) {
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
        if(graph < 4){edgesGraph.addBidirectionalEdge(origem, destino, stod(distancia));}
        else {edgesGraph.addEdge(origem, destino, stod(distancia));}
    }
    file.close();
}

void csvInfo::createNodes(int graph) {
    vertexSet.clear();
    vertexVector.clear();
    fstream file;
    file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv");
    if (!file.is_open()) {
        cerr << "Error: Unable to open the nodes file." << endl;
        return;
    }

    string line;
    string node;
    string longitude;
    string latitude;
    int aux = 0;
    getline(file, line);
    while(getline(file, line) && aux-1<graph) {
        stringstream s(line);
        getline(s, node, ',');
        getline(s, longitude, ',');
        getline(s, latitude);
        std::cout << "lat: " << latitude << std::endl;
        std::cout << "lon: " << longitude << std::endl;

        double convertedLat = std::stod(latitude);
        double convertedLon = std::stod(longitude);

        bool prov = edgesGraph.addVertex(node,aux, convertedLon,convertedLat);
        if(prov) {
            vertexSet.insert(node);
            vertexVector.push_back(Vertex(node, aux - 1, 0, 0));
            aux++;
        }
    }
    file.close();
}



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
    if(graph == "a"){
        file.open("../Datasets/Toy-Graphs/Toy-Graphs/shipping.csv");
    } else if(graph == "b"){
        file.open("../Datasets/Toy-Graphs/Toy-Graphs/stadiums.csv");
    } else if(graph == "c"){
        file.open("../Datasets/Toy-Graphs/Toy-Graphs/tourism.csv");
    } else if(graph == "25"){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_25.csv");}
    else if(graph == "50"){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_50.csv");}
    else if(graph == "75"){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_75.csv");}
    else if(graph == "100"){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_100.csv");}
    else if(graph == "200"){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_200.csv");}
    else if(graph == "300"){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_300.csv");}
    else if(graph == "400"){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_400.csv");}
    else if(graph == "500"){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_500.csv");}
    else if(graph == "600"){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_600.csv");}
    else if(graph == "700"){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_700.csv");}
    else if(graph == "800"){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_800.csv");}
    else if(graph == "900"){file.open("../Datasets/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_900.csv");}

    if (!file.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return;
    }

    string line;
    string origem;
    string destino;
    string distancia;
    int aux = 1;

    if(graph == "a" || graph == "b" || graph == "c"){getline(file, line);}    // discard header line
    while(getline(file, line)) {
        stringstream s(line);
        getline(s, origem, ',');
        getline(s, destino, ',');
        getline(s, distancia);

        if(graph == "a" || graph == "b" || graph == "c") {
            bool prov = edgesGraph.addVertex(origem, aux - 1, 0, 0);
            if (prov) { aux++; }
            prov = edgesGraph.addVertex(destino, aux - 1, 0, 0);
            if (prov) { aux++; }
        }
        edgesGraph.addEdge(origem, destino, stod(distancia));
        //edgesGraph.addBidirectionalEdge(origem, destino, stod(distancia));
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
    while(getline(file, line) && aux-1<graph) {
        stringstream s(line);
        getline(s, node, ',');
        getline(s, longitude, ',');
        getline(s, latitude);

        //cout << "Longitude: " << longitude << "Latitude: " << latitude << endl;

        bool prov = edgesGraph.addVertex(node,aux, longitude,latitude);
        if(prov) {aux++;}
    }
    file.close();
}
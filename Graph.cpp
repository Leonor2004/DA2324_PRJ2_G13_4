#include "Graph.h"

/************************* Vertex  **************************/

Vertex::Vertex(string in, int pos, double lon, double lat): info(in), vectorPos(pos), longitude(lon), latitude(lat) {}

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

string Vertex::getInfo() const {
    return this->info;
}


vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

double Vertex::getDist() const {
    return this->dist;
}

bool Vertex::isVisited() const {
    return this->visited;
}

Edge *Vertex::getPath() const {
    return this->path;
}

vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

/*int Vertex::getPos() {
    return this->vectorPos;
}*/

void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

Edge * Vertex::addEdge(Vertex *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

bool Vertex::removeEdge(string in) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getInfo() == in) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

double Vertex::getLon() const {
    return longitude;
}

double Vertex::getLat() const {
    return latitude;
}


void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getInfo() == info) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double w): orig(orig), dest(dest), weight(w)/*, capacity(w), flow(w)*/ {}

Vertex* Edge::getDest() const {
    return this->dest;
}

double Edge::getWeight() const {
    return this->weight;
}

void Edge::setWeight(double w){
    this->weight = w;
}

/*double Edge::getCapacity() const{
    return this->capacity;
}*/

Vertex* Edge::getOrig() const {
    return this->orig;
}

Edge* Edge::getReverse() const {
    return this->reverse;
}

/*double Edge::getFlow() const {
    return flow;
}*/

void Edge::setReverse(Edge* reverse) {
    this->reverse = reverse;
}

/*void Edge::setFlow(double flow) {
    this->flow = flow;
}*/

bool Edge::isTest() const{
    return this->teste;
}

void Edge::setTest(bool test){
    this->teste = test;
}

/********************** Graph  ****************************/

vector<Vertex*> Graph::getVertexSet() const {
    return vertexSet;
}

Vertex* Graph::findVertex(const string &in) const {
    for (auto v : vertexSet)
        if (v->getInfo() == in)
            return v;
    return nullptr;
}

bool Graph::addVertex(const string &in, int pos, double lon, double lat) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(in, pos, lon, lat));
    return true;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
bool Graph::removeVertex(const string &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getInfo() == in) {
            auto v = *it;
            v->removeOutgoingEdges();
            for (auto u : vertexSet) {
                u->removeEdge(v->getInfo());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

bool Graph::addEdge(const string &sourc, const string &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

Edge* Graph::getEdge(const string& source, const string& destination) const {
    // Iterate through each vertex in the graph
    for (Vertex* vertex : vertexSet) {
        // Iterate through the outgoing edges of the vertex
        for (Edge* edge : vertex->getAdj()) {
            // Check if the edge's origin vertex info matches the source vertex
            if (edge->getOrig()->getInfo() == source) {
                // Check if the edge's destination vertex info matches the destination vertex
                if (edge->getDest()->getInfo() == destination) {
                    // Return the edge if found
                    return edge;
                }
            }
        }
    }
    // Return nullptr if no matching edge is found
    return nullptr;
}

bool Graph::addBidirectionalEdge(const string &sourc, const string &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

inline void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

inline void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

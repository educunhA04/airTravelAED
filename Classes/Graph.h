#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstddef>
#include <utility>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include "airlines.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

template <class T>
class Vertex {
    T info;                // contents
    vector<Edge<T> > adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field
    int indegree;          // auxiliary field
    int num;               // auxiliary field
    int low;               // auxiliary field

    void addEdge(Vertex<T> *dest, double w);
    bool removeEdgeTo(Vertex<T> *d);
public:
    Vertex(T in);
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Edge<T>> &getAdj() const;
    void setAdj(const vector<Edge<T>> &adj);
    int getIndegree() const;
    void setIndegree(int indegree);
    int getNum() const;
    void setNum(int num);
    int getLow() const;
    void setLow(int low);

    void addEdgeAirlines(Vertex<T> *dest, double w, Airlines a);

    friend class Graph<T>;
};


template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
    Airlines airline;      // airline responsible for the flight
public:
    Edge(Vertex<T> *d, double w);
    Edge(Vertex<T> *d, double w, Airlines a);
    Vertex<T> *getDest() const;
    Airlines getAirline() const;
    void setDest(Vertex<T> *dest);
    double getWeight() const;
    void setWeight(double weight);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template<class T>
Airlines Edge<T>::getAirline() const {
    return airline;
}

template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet; // vertex set
    int _index_;                   // auxiliary field
    stack<Vertex<T>> _stack_;      // auxiliary field
    list<list<T>> _list_sccs_;     // auxiliary field

    void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
    bool dfsIsDAG(Vertex<T> *v) const;
public:
    Vertex<T> *findVertex(const T &in) const;
    int getNumVertex() const;
    bool addVertex(const T &in);
    bool removeVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    bool addEdgeAirlines(const T&sourc, const T&dest, double w, Airlines a);
    bool removeEdge(const T &sourc, const T &dest);
    vector<Vertex<T> * > getVertexSet() const;
};

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}
template<class T>
Edge<T>::Edge(Vertex<T> *d, double w, Airlines a): dest(d), weight(w), airline(std::move(a)) {}
template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
    return vertexSet;
}
template<class T>
T Vertex<T>::getInfo() const {
    return info;
}
template<class T>
void Vertex<T>::setInfo(T in) {
    Vertex::info = in;
}
template<class T>
bool Vertex<T>::isProcessing() const {
    return processing;
}
template<class T>
void Vertex<T>::setProcessing(bool p) {
    Vertex::processing = p;
}
template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}
template<class T>
void Edge<T>::setDest(Vertex<T> *d) {
    Edge::dest = d;
}
template<class T>
double Edge<T>::getWeight() const {
    return weight;
}
template<class T>
void Edge<T>::setWeight(double weight) {
    Edge::weight = weight;
}
/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}
template <class T>
bool Vertex<T>::isVisited() const {
    return visited;
}
template<class T>
int Vertex<T>::getIndegree() const {
    return indegree;
}
template<class T>
void Vertex<T>::setIndegree(int indegree) {
    Vertex::indegree = indegree;
}
template<class T>
int Vertex<T>::getNum() const {
    return num;
}
template<class T>
void Vertex<T>::setNum(int num) {
    Vertex::num = num;
}
template<class T>
int Vertex<T>::getLow() const {
    return low;
}
template<class T>
void Vertex<T>::setLow(int low) {
    Vertex::low = low;
}
template <class T>
void Vertex<T>::setVisited(bool v) {
    Vertex::visited = v;
}
template<class T>
const vector<Edge<T>> &Vertex<T>::getAdj() const {
    return adj;
}
template <class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}
/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}
template<class T>
bool Graph<T>::addEdgeAirlines(const T &sourc, const T &dest, double w, Airlines a) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdgeAirlines(v2,w,a);
    return true;
}
/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
}
/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d), an edge weight (w) and an airport (a).
 */
template<class T>
void Vertex<T>::addEdgeAirlines(Vertex<T> *dest, double w, Airlines a) {
    adj.push_back(Edge<T>(dest,w,a));
}
/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}
/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d) {
            adj.erase(it);
            return true;
        }
    return false;
}
/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->info  == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}

#endif /* GRAPH_H_ */
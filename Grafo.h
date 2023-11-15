//
// Created by estudiante on 10/11/2023.
//

#ifndef TALLERGRAFOS_GRAFO_HXX
#define TALLERGRAFOS_GRAFO_HXX

#include "Punto.h"
#include <vector>
#include <list>
#include <utility>
#include <iostream>
#include <queue>
#include <climits>

template <class C>
class Graph {

private:
    std::vector<Punto> vertices;
    std::vector<std::list<std::pair<int, C>>> edges;

public:
    //constructors
    Graph();

    //getters
    std::vector<Punto> getVertices();
    std::vector<std::list<std::pair<int, C>>> getEdges();

    //setters
    void setVertices(std::vector<Punto>& vertices);
    void setEdges(std::vector<std::list<std::pair<int, C>>>& edges);

    //inserting
    bool addVertex(Punto& vertex);
    bool addEdge(Punto& origin, Punto& destination, C cost);

    //searching
    int searchVertice(Punto& vertex);
    bool searchEdge(Punto& origin, Punto& destination);

    //tours
    void plain();
    void showEdges();

    //algorithms
    void bestRoute(Punto& initial, std::vector<int>& route, C& distance);
    void findBestRoute(int indexBegin, std::vector<bool>& visited, std::vector<int>& route, C& distance);
};

#include "Grafo.hxx"
#endif //TALLERGRAFOS_GRAFO_HXX

//
// Created by estudiante on 10/11/2023.
//

#ifndef TALLERGRAFOS_GRAFO_H
#define TALLERGRAFOS_GRAFO_H

#include <vector>
#include <list>
#include <utility>
#include <iostream>
#include "Punto.h"

template < class C >
class Graph {

private:
    std::vector < Punto > vertices;
    std::vector < std::list < std::pair < int, C > > > edges;
public:
    //constructors
    Graph();

    //getters
    std::vector < Punto > getVertices();
    std::vector < std::list < std::pair < int, C > > > getEdges();

    //setters
    void setVertices(std::vector < Punto >& vertices);
    void setEdges(std::vector < std::list < std::pair < int, C > > >& edges);

    //inserting
    bool addVertex(Punto& vertex);
    bool addEdge(Punto& origin, Punto& destination, C cost);

    //searching
    int searchVertice(Punto& vertex);
    bool searchEdge(Punto& origin, Punto& destination);

    //tours
    void plain();
    void bfs();
    void dfs();
    void showEdges();

    //algorithms
    void prim();
    void dijkstra(Punto inicio);

};

#include "Grafo.hxx"
#endif //TALLERGRAFOS_GRAFO_H

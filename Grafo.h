//
// Created by estudiante on 10/11/2023.
//

#ifndef TALLERGRAFOS_GRAFO_H
#define TALLERGRAFOS_GRAFO_H

#include <vector>
#include <list>
#include <utility>
#include <map>
#include <iostream>
#include <queue>
#include "Punto.h"

class priority_queue;

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
    std::pair<int,C> searchEdgeCost(Punto& origin, Punto& destination);

    //tours
    void plain();
    void bfs();
    void dfs();
    void showEdges();

    //algorithms
    void prim(std::string origen);


    //std::map<int, C> dijkstra(Punto& inicio);
    std::vector<C> dijkstra(Punto &origen);

    std::map<C, std::vector<Punto>> obtenerListaAdyacencia();
};

#include "Grafo.hxx"
#endif //TALLERGRAFOS_GRAFO_H

//
// Created by estudiante on 10/11/2023.
//

#ifndef TALLERGRAFOS_GRAFO_HXX
#define TALLERGRAFOS_GRAFO_HXX

#include "Grafo.h"
#include <vector>
#include <list>
#include <utility>
#include <iostream>
#include <queue>
#include <map>

//constructors

template < class C>
Graph<C>::Graph() {

}

//----------------------------------------------------------------------------------------------

//getters

template < class C >
std::vector < Punto > Graph<C>::getVertices(){
    return this->vertices;
}

template < class C >
std::vector < std::list < std::pair < int, C > > > Graph<C>::getEdges(){
    return this->edges;
}

//----------------------------------------------------------------------------------------------

//setters

template < class C >
void Graph<C>::setVertices(std::vector < Punto >& vertices){
    this->vertices = vertices;
}

template < class C >
void Graph<C>::setEdges(std::vector < std::list < std::pair < int, C > > >& edges){
    this->edges = edges;
}

//----------------------------------------------------------------------------------------------

//inserting

template < class C >
bool Graph<C>::addVertex(Punto& vertex){
    int vertexFound = searchVertice(vertex);
    if(vertexFound == -1){
        this->vertices.push_back(vertex);
        this->edges.push_back(std::list<std::pair<int, C>>());
        return true;
    }
    return false;
}

template < class C >
bool Graph<C>::addEdge(Punto& origin, Punto& destination, C cost){
    int destinationIndex = searchVertice(destination);
    int originIndex = searchVertice(origin);

    if(!searchEdge(origin, destination) && originIndex != -1 && destinationIndex != -1){
        std::pair < int, C > newEdge (destinationIndex, cost);
        this->edges[originIndex].push_back(newEdge);
        return true;
    }
    return false;
}

template <class C>
std::map<C, std::vector<Punto>> Graph<C>::obtenerListaAdyacencia() {
    return this->listaAdyacencia;
}

//----------------------------------------------------------------------------------------------

//searching

template < class C >
int Graph<C>::searchVertice(Punto& vertex){
    int vertexFound = -1;
    for(int i = 0 ; i < this->vertices.size() ; i++){
        if(this->vertices[i] == vertex){
            vertexFound = i;
        }
    }
    return vertexFound;
}

template < class C >
bool Graph<C>::searchEdge(Punto& origin, Punto& destination){
    typename  std::list < std::pair < int, C > >::iterator itL;
    int destinationIndex = searchVertice(destination);
    int originIndex = searchVertice(origin);

    if(destinationIndex != -1 && originIndex != -1){
        itL = this->edges[originIndex].begin();
        for(itL = this->edges[originIndex].begin() ; itL != this->edges[originIndex].end() ; itL++){
            if(itL->first == destinationIndex){
                return true;
            }
        }
    }
    return false;
}

template < class C >
std::pair<int,C>  Graph<C>::searchEdgeCost(Punto& origin, Punto& destination){
    typename  std::list < std::pair < int, C > >::iterator itL;
    int destinationIndex = searchVertice(destination);
    int originIndex = searchVertice(origin);

    if(destinationIndex != -1 && originIndex != -1){
        itL = this->edges[originIndex].begin();
        for(itL = this->edges[originIndex].begin() ; itL != this->edges[originIndex].end() ; itL++){
            if(itL->first == destinationIndex){
                return *itL;
            }
        }
    }
}

//----------------------------------------------------------------------------------------------

//tours

template < class C >
void Graph<C>::plain(){
    for(int i = 0 ; i < this->vertices.size() ; i++){
        std::cout << this->vertices[i] << std::endl;
    }
}

template <class C >
void Graph<C>::bfs(){

}

template < class C >
void Graph<C>::dfs(){

}

template <class C >
void Graph<C>::showEdges(){
    typename  std::list < std::pair < int, C > >::iterator itL;

    for(int i = 0 ; i < this->edges.size() ; i++){
        std::cout << "\n" << this->vertices[i] << ": \n";
        std::list < std::pair < int, C > > auxEdges = this->edges[i];
        itL = auxEdges.begin();
        for(itL = auxEdges.begin() ; itL != auxEdges.end() ; itL++){
            std::cout << "(" << this->vertices[(*itL).first] << "," << (*itL).second << ") \n";
        }
        std::cout << std::endl;
    }
}

//----------------------------------------------------------------------------------------------

//algorithms

template < class C >
void Graph<C>::prim(std::string origen){

}

template <class C>
std::vector<C> Graph<C>::dijkstra(Punto &origen) {
    int numVertices = vertices.size();
    std::vector<C> distance(numVertices, std::numeric_limits<C>::max());

    std::priority_queue<std::pair<C, int>, std::vector<std::pair<C, int>>, std::greater<std::pair<C, int>>> q;
    int indexOrigin = searchVertice(origen);

    distance[indexOrigin] = 0;
    q.push({0, indexOrigin});
    std::priority_queue<std::pair<C, int>, std::vector<std::pair<C, int>>, std::greater<std::pair<C, int>>> pq;
    pq.push({0,indexOrigin});
    while (!q.empty()) {
        int vertex = q.top().second;
        C cost = q.top().first;

        q.pop();

        for (const std::pair<int, C> &neighbor : edges[vertex]) {
            int vert = neighbor.first;
            C nCost = neighbor.second;
            if (cost + nCost < distance[vert]) {
                distance[vert] = cost + nCost;
                pq.push({distance[vert], vert});
            }
        }
    }

    // Imprimir resultados
    for (int i = 0; i < numVertices; i++) {
        std::cout << "Vertex: " << pq.top().second << ", Distance: " << pq.top().first << std::endl;
        pq.pop();
    }

    return distance;
}


#endif //TALLERGRAFOS_GRAFO_HXX
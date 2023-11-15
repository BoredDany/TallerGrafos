//
// Created by estudiante on 10/11/2023.
//


#include <cmath>
#include "Grafo.h"

template <class C>
Graph<C>::Graph() {}

template <class C>
std::vector<Punto> Graph<C>::getVertices() {
    return this->vertices;
}

template <class C>
std::vector<std::list<std::pair<int, C>>> Graph<C>::getEdges() {
    return this->edges;
}

template <class C>
void Graph<C>::setVertices(std::vector<Punto>& vertices) {
    this->vertices = vertices;
}

template <class C>
void Graph<C>::setEdges(std::vector<std::list<std::pair<int, C>>>& edges) {
this->edges = edges;
}

template <class C>
bool Graph<C>::addVertex(Punto& vertex) {
    int vertexFound = searchVertice(vertex);
    if (vertexFound == -1) {
        this->vertices.push_back(vertex);
        this->edges.push_back(std::list<std::pair<int, C>>());
        return true;
    }
    return false;
}

template <class C>
bool Graph<C>::addEdge(Punto& origin, Punto& destination, C cost) {
    int destinationIndex = searchVertice(destination);
    int originIndex = searchVertice(origin);

    if (!searchEdge(origin, destination) && originIndex != -1 && destinationIndex != -1 && originIndex != destinationIndex) {
        std::pair<int, C> newEdge(destinationIndex, cost);
        this->edges[originIndex].push_back(newEdge);
        return true;
    }
    return false;
}

template <class C>
int Graph<C>::searchVertice(Punto& vertex) {
    int vertexFound = -1;
    for (int i = 0; i < this->vertices.size(); i++) {
        if (this->vertices[i] == vertex) {
            vertexFound = i;
        }
    }
    return vertexFound;
}

template <class C>
bool Graph<C>::searchEdge(Punto& origin, Punto& destination) {
    typename std::list<std::pair<int, C>>::iterator itL;
    int destinationIndex = searchVertice(destination);
    int originIndex = searchVertice(origin);

    if (destinationIndex != -1 && originIndex != -1) {
        itL = this->edges[originIndex].begin();
        for (itL = this->edges[originIndex].begin(); itL != this->edges[originIndex].end(); itL++) {
            if (itL->first == destinationIndex) {
                return true;
            }
        }
    }
    return false;
}

template <class C>
void Graph<C>::plain() {
    for (int i = 0; i < this->vertices.size(); i++) {
        std::cout << this->vertices[i] << std::endl;
    }
}

template <class C>
void Graph<C>::showEdges() {
    typename std::list<std::pair<int, C>>::iterator itL;

    for (int i = 0; i < this->edges.size(); i++) {
        std::cout << "\n" << this->vertices[i] << ": \n";
        std::list<std::pair<int, C>> auxEdges = this->edges[i];
        itL = auxEdges.begin();
        for (itL = auxEdges.begin(); itL != auxEdges.end(); itL++) {
            std::cout << "(" << this->vertices[(*itL).first] << "," << (*itL).second << ") \n";
        }
        std::cout << std::endl;
    }
    return;
}

template <class C>
void Graph<C>::bestRoute(Punto& initial, std::vector<int>& route, C& distance) {
    int initialIndex = searchVertice(initial);
    int numVertices = vertices.size();

    // Vector para almacenar las distancias mínimas desde el vértice inicial
    std::vector<C> dist(numVertices, std::numeric_limits<C>::max());

    // Vector para almacenar si un vértice ha sido visitado
    std::vector<bool> visited(numVertices, false);

    // Priority queue para elegir el vértice más cercano en cada iteración
    std::priority_queue<std::pair<C, int>, std::vector<std::pair<C, int>>, std::greater<std::pair<C, int>>> pq;

    // Inicialización
    dist[initialIndex] = 0;
    pq.push({0, initialIndex});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Si ya hemos visitado este vértice, continuamos
        if (visited[u]) {
            continue;
        }

        visited[u] = true;

        // Actualizamos las distancias y la cola de prioridad
        for (const auto& edge : edges[u]) {
            int v = edge.first;
            C weight = edge.second;

            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Reconstruir la ruta óptima
    int currentVertex = initialIndex;
    route.clear();

    while (route.size() < numVertices - 1) {
        route.push_back(currentVertex);
        int nextVertex = -1;
        C minWeight = std::numeric_limits<C>::max();

        for (const auto& edge : edges[currentVertex]) {
            int neighbor = edge.first;
            C weight = edge.second;

            if (!visited[neighbor] && weight < minWeight) {
                nextVertex = neighbor;
                minWeight = weight;
            }
        }

        if (nextVertex == -1) {
            break;
        }

        distance += minWeight;
        currentVertex = nextVertex;
    }

    route.push_back(initialIndex);
    return;
}

template <class C>
void Graph<C>::findBestRoute(int indexBegin, std::vector<bool>& visited, std::vector<int>& route, C& distance) {
    visited[indexBegin] = true;
    route.push_back(indexBegin);

    for (const auto& edge : edges[indexBegin]) {
        int neighbor = edge.first;
        C weight = edge.second;

        if (!visited[neighbor]) {
            distance += weight;
            findBestRoute(neighbor, visited, route, distance);
        }
    }
    return;
}

#endif //TALLERGRAFOS_GRAFO_HXX
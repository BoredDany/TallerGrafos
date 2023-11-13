//
// Created by estudiante on 10/11/2023.
//

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include "Grafo.h"
#include "Punto.h"
using namespace std;

Punto INITIAL (0.0, 0.0);



void readVertices(string archivo, std::list < Graph <float> >& graphs){
    std::ifstream file (archivo);
    std::string line, word;
    int numGraphs;

    if(file.is_open()){
        file>>numGraphs;

        for (int i = 0; i < numGraphs; ++i) {
            Graph<float> graph;
            int numNodes;
            file >> numNodes;
            graph.addVertex(INITIAL);
            for (int j = 0; j < numNodes; j++) {
                float x, y;
                file >> x >> y;
                Punto p (x, y);
                graph.addVertex(p);
            }

            graphs.push_back(graph);
        }
    }else{
        std::cout<<"Archivo de conexiones no leido"<<std::endl;
    }
    file.close();
}

float calcDistance(Punto p1, Punto p2){
    float distancia = 0, distanciaX = 0, distanciaY = 0;
    distanciaX = pow(p1.x - p2.x,2);
    distanciaY = pow(p1.y - p2.y,2);
    distancia = sqrt(distanciaY+distanciaX);
    return distancia;
}

void readEdges(std::list < Graph <float> >& graphs){
    typename std::list < Graph <float> > :: iterator it = graphs.begin();
    for( ; it != graphs.end() ; it++){
        std::vector < Punto > vertices = (*it).getVertices();
        for (int i = 0; i < vertices.size(); ++i) {
            for (int j = 0; j < vertices.size(); ++j) {
                float costo = calcDistance(vertices[i], vertices[j]);
                (*it).addEdge(vertices[i], vertices[j], costo);
            }
        }
    }
}

void writeFile(string file, std::list < Graph <float> >& graphs)
{
    ofstream salida;
    salida.open(file);

        salida<<graphs.size()<<std::endl;
         std::cout<<"Cantidad de circuitos en el archivo: "<<graphs.size()<<std::endl;

    for (Graph <float> g : graphs) {
        std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<std::pair<float, int>>> pq = g.dijkstra(INITIAL);

        std::vector<Punto> orderedVertices;
        while (!pq.empty()) {
            pq.pop();
            int vertexIndex = pq.top().second;
            orderedVertices.push_back(g.getVertices()[vertexIndex]);
        }
        salida<<orderedVertices.size()-1<<std::endl;
        std::cout<<"Cantidad de agujeros: "<<orderedVertices.size()-1<<std::endl;

        for (Punto p : orderedVertices) {
            salida << p.x << " " << p.y << std::endl;
        }

        // Calcular distancia
        float totalDistance = 0;
        for (int i = 0; i < orderedVertices.size() - 1; ++i) {
            totalDistance += calcDistance(orderedVertices[i], orderedVertices[i + 1]);
        }

        std::cout << "Distancia por circuito: " << totalDistance << std::endl;
        std::cout << "---------------------------" << std::endl;
    }

    salida.close();
}


//template < class C >
int main(int argc, char* argv[]){
    if(argc < 3){
        cout << "Argumentos no validos" << endl;
        return 1;
    }
    string input = argv[1];
    string output = argv[2];
    std::list < Graph <float> > graphs;
    readVertices(input, graphs);
    for(Graph <float> g: graphs){
        cout << "GRAPH" << endl;
        g.plain();
    }

    readEdges(graphs);
    int c=0;
    for(Graph <float> g: graphs){
        cout << "EDGES" << endl;
        g.showEdges();


    }

    writeFile( output,graphs);

    return 0;
}
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
#include <cmath>
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

void readEdges(std::list < Graph <float> >& graphs){
    typename std::list < Graph <float> > :: iterator it = graphs.begin();
    for( ; it != graphs.end() ; it++){
        std::vector < Punto > vertices = (*it).getVertices();
        for (int i = 0; i < vertices.size(); ++i) {
            for (int j = 0; j < vertices.size(); ++j) {
                float costo = Punto::calcDistance(vertices[i], vertices[j]);
                (*it).addEdge(vertices[i], vertices[j], costo);
            }
        }
    }
}

void writeFile(string archivo, std::list < Graph <float> >& graphs, std::vector < std::vector <int> >& routes){
    std::ofstream file (archivo);

    if(file.is_open()){
        file << graphs.size() << "\n";
        typename std::list < Graph <float> >::iterator itG = graphs.begin();
        int itR = 0;

        for (; itG != graphs.end() && itR < routes.size(); itG++, itR++){
            file << routes[itR].size() << "\n";
            for(int i = 0 ; i < routes[itR].size() ; i++){
                file << (*itG).getVertices()[routes[itR][i]] << "\n";
            }

        }

    }else{
        std::cout<<"Archivo de salida no creado"<<std::endl;
    }
    file.close();
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Argumentos no válidos";
        cout<<endl;
        return 1;
    }

    std::list<Graph<float>> graphs;
    std::vector<std::vector<int>> routes;
    int i = 0;

    readVertices(argv[1], graphs);

    cout << "\nCantidad de circuitos en el archivo: " << graphs.size();
    cout<<endl;

    for (typename std::list<Graph<float>>::iterator itG = graphs.begin(); itG != graphs.end(); itG++) {
        std::vector<int> ruta;
        float distance = 0;

        INITIAL = Punto(0.0, 0.0);
        (*itG).addVertex(INITIAL);
        readEdges(graphs);

        (*itG).bestRoute(INITIAL, ruta, distance);

        routes.push_back(ruta);

        cout << "\nCIRCUITO " << i + 1 << endl;
        cout << "Numero de agujeros:" << ruta.size();
        cout<<endl;
        cout << "Distancia recorrida: " << distance;
        cout<<endl;

        i++;
    }

    writeFile(argv[2], graphs, routes);

    return 0;
}
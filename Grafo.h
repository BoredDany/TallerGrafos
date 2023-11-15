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


};

#include "Grafo.hxx"
#endif //TALLERGRAFOS_GRAFO_H

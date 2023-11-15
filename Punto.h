//
// Created by estudiante on 10/11/2023.
//

#ifndef TALLERGRAFOS_PUNTO_H
#define TALLERGRAFOS_PUNTO_H

#include <iostream>
#include <valarray>
#include <cmath>


struct Punto {

    std::string dato;
    float x;
    float y;
    bool visitado;

    Punto(float x_value, float y_value) : x(x_value), y(y_value) {}

    Punto& operator = (const Punto &p) {
        x = p.x;
        y = p.y;
        return *this;
    }

    bool operator == (const Punto &p) const {
        return (x == p.x && y == p.y);
    }

    friend std::ostream& operator << (std::ostream &o, const Punto &p) {
        o << p.x << " " << p.y;
        return o;
    }

    static float calcDistance(Punto &p1, Punto &p2){
        float distancia = 0, distanciaX = 0, distanciaY = 0;
        distanciaX = pow(p1.x - p2.x,2);
        distanciaY = pow(p1.y - p2.y,2);
        distancia = sqrt(distanciaY+distanciaX);
        return distancia;
    }
};


#endif //TALLERGRAFOS_PUNTO_H

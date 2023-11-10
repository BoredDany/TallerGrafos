//
// Created by estudiante on 10/11/2023.
//

#ifndef TALLERGRAFOS_PUNTO_H
#define TALLERGRAFOS_PUNTO_H

#include <iostream>
#include <valarray>

struct Punto {

    std::string dato;
    float x;
    float y;

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
        o << "(" << p.x << "," << p.y << ")";
        return o;
    }
};


#endif //TALLERGRAFOS_PUNTO_H

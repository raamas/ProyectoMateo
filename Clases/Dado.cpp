//
// Created by OMAR DENILSON on 9/11/2025.
//

#include "Dado.h"

#include "Utilidades.h"

Dado::Dado() {
    max = 0;
    direcciones = {0, 0, 0, 0};
}

Dado::Dado(int max) {
    this->max = max;
    direcciones = {0, 0, 0, 0};
}

int Dado::getMax() {
    return max;
}

void Dado::setMax(int max) {
    this->max = max;
}

vector<int> Dado::getDirecciones() {
    return direcciones;
}

void Dado::lanzar() {
    Utilidades u;
    for (auto &d :direcciones) {
        d = u.getRandomNumber(0,max);
    }
}

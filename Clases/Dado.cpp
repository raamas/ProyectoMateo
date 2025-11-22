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
    for (auto &d :direcciones) { //Cambia el contenido dentro del arreglo direcciones a 4 numeros aleatorios
        d = u.getRandomNumber(1,max);
    }
}

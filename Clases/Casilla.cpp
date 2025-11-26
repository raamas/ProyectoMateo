//
// Created by OMAR DENILSON on 9/11/2025.
//

#include "Casilla.h"

#include <iostream>

Casilla::Casilla() {
    efecto = 0;
    idJugador = -1;
    coordenadas = {-1, -1};
}

Casilla::Casilla(int e) {
    efecto = e;
    idJugador = -1;
    coordenadas = {-1, -1};
}

int Casilla::getEfecto() {
    return efecto;
}

void Casilla::setEfecto(int e) {
    if (e > 0 && e < 3) {
        efecto = e;
    } else {
        efecto = 0;
    }
}

int Casilla::getIdJugador() {
    return idJugador;
}

void Casilla::setIdJugador(int i) {
    idJugador = i;
}

vector<int> Casilla::getCoordenadas() {
    return coordenadas;
}

int Casilla::getCoordenadas(int p) {
    if (p >= 0 && p < coordenadas.size()) {
        return coordenadas[p];
    }
    return -1; // or throw an exception
}

void Casilla::setCoordenadas(vector<int> c) {
    coordenadas = c;
}

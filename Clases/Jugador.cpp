//
// Created by OMAR DENILSON on 9/11/2025.
//

#include "Jugador.h"

Jugador::Jugador() {
    puntosVida = 0;
    posicion = nullptr;
}

Jugador::Jugador(int pv, int id) {
    this->id = id;
    puntosVida = pv;
    posicion = nullptr;
}

int Jugador::getId() {
    return this->id;
};

void Jugador::setId(int id) {
    this->id = id;
};

int Jugador::getPuntosVida() {
    return puntosVida;
}

void Jugador::setPuntosVida(int pv) {
    puntosVida = pv;
}

Casilla *Jugador::getPosicion() {
    return posicion;
}

void Jugador::setPosicion(Casilla *casilla) {
    posicion = casilla;
}

void Jugador::mover() {
    // TODO: Implement mover logic
}

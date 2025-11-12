//
// Created by OMAR DENILSON on 9/11/2025.
//

#include "Jugador.h"

#include <iostream>

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
    /*
     * DEVUELVE LA DIRECCION EN MEMORIA DEL OBJETO CASILLA EN QUE EL JUGADOR ESTA
     */
    return posicion;
}

void Jugador::setPosicion(Casilla *casilla) {
    posicion = casilla;
}

void Jugador::mover(Casilla *nuevaCasilla, int nuevoPuntosVida) {
    /*
     * VA A LA DIRECCION EN MEMORIA DE LA CASILLA DONDE EL JUGADOR SE ENCUENTRA Y LA "RESETEA"
     * LUEGO VA A LA DIRECCION DE LA CASILLA A LA QUE EL JUGADOR SE VA A MOVER Y LE AGREGA EL ID DEL JUGADOR
     * DESPUES GUARDA LA DIRECCION DE LA NUEVA CASILLA EN EL MIEMBRO POSICION
     * FINALMENTE, SI LA NUEVA CASILLA TIENE EFECTO 1 (CASTIGO) ENTONCES LE QUITA TODOS LOS PUNTOS DE VIDA AL JUGADOR
     */
    posicion->setIdJugador(-1);
    posicion->setEfecto(0);

    nuevaCasilla->setIdJugador(id);
    posicion = nuevaCasilla;

    if (posicion->getEfecto() == 1) {
        puntosVida = 0;
        return;
    }

    puntosVida -= 1;
}

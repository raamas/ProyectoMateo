//
// Created by OMAR DENILSON on 9/11/2025.
//

#include "Partida.h"

Partida::Partida() {
    cantidadJugadores = 0;
    dificultad = 0;
}

Partida::Partida(int d, int cj) {
    dificultad = d;
    cantidadJugadores = cj;
    tablero = {d, cj};
}

int Partida::getCantidadJugadores() {
    return cantidadJugadores;
}

void Partida::setCantidadJugadores(int cj) {
    cantidadJugadores = cj;
    tablero.setCantidadJugadores(cj);
}

int Partida::getDificultad() {
    return dificultad;
}

void Partida::setDificultad(int d) {
    dificultad = d;
    tablero.setTamano(d);
}

Tablero &Partida::getTablero() {
    return tablero;
}

void Partida::setTablero(Tablero t) {
    tablero = t;
}



int Partida::getGanador() {
    /*
     * ESTA FUNCION DEVUELVE EL ID DEL OBJETO JUGADOR QUE HAYA ALCANZADO CONDICIONES DE VICTORIA
     * PRIMERO VERIFICA QUE LA CASILLA CENTRO ESTE VACIA, DE LO CONTRARIO DEVUELVE EL ID QUE LA ESTE OCUPANDO
     * SI NO, ENTONCES GUARDA EL ID DE TODOS LOS JUGADORES QUE ESTEN VIVOS EN ESE MOMENTO EN LA VARIABLE "jugadoresVivos"
     * SI SOLO QUEDA UN JUGADOR VIVO ENTONCES DEVUELVE SU ID;
     * DE OTRA MANERA BUSCA ENTRE TODOS LOS JUGADORES AQUEL CON MAS PUNTOS DE VIDA Y DEVUELVE SU ID
     * SI NINGUNA DE LAS ANTERIORES SE CUMPLE NO HAY GANADOR, Y DEVUELVE -1
     */
    if (tablero.getCasilla(dificultad / 2, dificultad / 2).getIdJugador() != -1) {
        return tablero.getCasilla(dificultad / 2, dificultad / 2).getIdJugador();
    }


    vector<int> jugadoresVivos;
    for (int i = 0; i < tablero.getCantidadJugadores(); i++) {
        auto jugador = tablero.getJugadores()[i];
        if (jugador.getPuntosVida() > 0) {
            jugadoresVivos.push_back(jugador.getId());
        }
    }

    if (jugadoresVivos.size() == 1) {
        return jugadoresVivos[0];
    }

    if (jugadoresVivos.size() > 1) {
        int temp = -1;
        for (int i = 0; i > jugadoresVivos.size(); i++) {
            int a = tablero.getJugadores()[jugadoresVivos[i]].getPuntosVida();
            if (i + 1 == dificultad && a > tablero.getJugadores()[temp].getPuntosVida()) {
                return tablero.getJugadores()[jugadoresVivos[i]].getId();
            }
            if (a > tablero.getJugadores()[jugadoresVivos[i + 1]].getPuntosVida()) {
                temp = tablero.getJugadores()[jugadoresVivos[i]].getId();
            }
        }
        return temp;
    }
    return -1;
};

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
    dado = Dado(d);
}

int Partida::getCantidadJugadores() {
    return cantidadJugadores;
}

void Partida::setCantidadJugadores(int cj) {
    cantidadJugadores = cj;
}

int Partida::getDificultad() {
    return dificultad;
}

void Partida::setDificultad(int d) {
    dificultad = d;
}

Tablero &Partida::getTablero() {
    return tablero;
}

void Partida::setTablero(Tablero t) {
    tablero = t;
}

Dado &Partida::getDado() {
    return dado;
}

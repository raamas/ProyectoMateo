//
// Created by OMAR DENILSON on 9/11/2025.
//

#include "Utilidades.h"

#include <iostream>
#include <random>

Utilidades::Utilidades() {
};

// LA VERDAD ESTO LO HIZO GPT LOL
int randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

int Utilidades::getRandomNumber(int min, int max) {
    return randomInt(min, max);
}

//Esto no lo hizo gpt
void Utilidades::guardarPartida(Partida *p) {
    //CANTIDADJUGADORES;DIFICULTAD;IDGANADOR;PIDJUGADOR;PUNTOSVIDAJUGADOR;MAXDADOJUGADOR;CORDENADASA,CORDENADASB;EFECTOCASILLAJUGADOR;
    ofstream writeFile("../partidas/test.txt");
    writeFile << p->getCantidadJugadores() << ";"
            << p->getDificultad() << ";"
            << "P" << p->getGanador() << ";";
    for (auto player: p->getTablero().getJugadores()) {
        writeFile << "P" << player.getId() << ";"
                << player.getPuntosVida() << ";"
                << player.getDado().getMax() << ";"
                << player.getPosicion()->getCoordenadas()[0] << "," << player.getPosicion()->getCoordenadas()[1] << ";"
                << player.getPosicion()->getEfecto() << ";";
    }
};

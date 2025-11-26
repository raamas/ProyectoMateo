//
// Created by OMAR DENILSON on 9/11/2025.
//
#include <iostream>
using namespace std;
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

    // int winnerId = -1;

    if (tablero.getCasilla(dificultad / 2, dificultad / 2).getIdJugador() != -1) {
        return tablero.getCasilla(dificultad / 2, dificultad / 2).getIdJugador();
    }


    vector<int> jugadoresVivos;
    for (int i = 0; i < cantidadJugadores; i++) {
        auto jugador = tablero.getJugadores().at(i);
        auto _ = jugador.getPuntosVida();
        if (jugador.getPuntosVida() > 0) {
            jugadoresVivos.push_back(jugador.getId());
        }
    }

    if (jugadoresVivos.size() == 1) {
        return jugadoresVivos.at(0);
    }


    return -1;
};

void Partida::setGanador(int id) {
    this->idGanador = id;
}

vector<string> split(string s, char c) {
    vector<string> res;
    string temp;
    for (char ch: s) {
        if (ch == c) {
            res.push_back(temp);
            temp.clear();
            continue;
        }

        temp += ch;
    }

    res.push_back(temp);

    return res;
}


void Partida::cargarArchivo(string route) {
    /*
     *0 CANTIDADJUGADORES;
     *1 DIFICULTAD;
     *2 IDGANADOR;
     *3 PIDJUGADOR;
     *4 PUNTOSVIDAJUGADOR;
     *5 MAXDADOJUGADOR;
     *6 CORDENADASA,CORDENADASB;
     *7 EFECTOCASILLAJUGADOR;
     *
     * m = t+i*5
     */

    ifstream readFile(route);
    string s;
    vector<string> info;

    int cj, d, idg;

    while (getline(readFile, s)) {
        info = split(s, ';');
    }

    cj = stoi(info.at(0));
    d = stoi(info.at(1));
    idg = stoi(info.at(2));

    dificultad = d;
    tablero.setTamano(d);
    tablero.setJugadores({});

    cantidadJugadores = cj;
    vector<Jugador> jugadores;
    for (int i = 0; i < cj; i++) {
        int pv, id, maxDado, a, b, efectoCasillaJugador;

        pv = stoi(info.at(4 + i * 5));
        id = stoi(info.at(3 + i * 5));
        maxDado = stoi(info.at(5 + i * 5));
        auto coordenadas = split(info[6 + i * 5], ',');
        a = stoi(coordenadas.at(0));
        b = stoi(coordenadas.at(1));
        efectoCasillaJugador = stoi(info.at(7 + i * 5));

        Jugador j = {pv, id};
        j.getDado().setMax(maxDado);

        auto casillaJugador = tablero.getCasillaAddress(a, b);
        casillaJugador->setIdJugador(id);
        casillaJugador->setEfecto(efectoCasillaJugador);
        j.setPosicion(casillaJugador);

        jugadores.push_back(j);
    }
    tablero.setJugadores(jugadores);
    idGanador = idg;
}

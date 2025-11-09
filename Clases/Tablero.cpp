//
// Created by OMAR DENILSON on 9/11/2025.
//

#include "Tablero.h"

#include <iostream>

#include "Utilidades.h"

void generarCasillas(Tablero &t) {
    Utilidades u;
    for (int i = 0; i < t.tamano; i++) {
        vector<Casilla> temp;
        for (int j = 0; j < t.tamano; j++) {
            Casilla c;
            c.setCoordenadas({i, j});
            c.setEfecto(u.getRandomNumber(0, 100));
            temp.push_back(c);
        }
        t.casillas.push_back(temp);
    }
};

void generarJugadores(Tablero &t) {
    //// CORREGIR ESTA FUNCION;
    Utilidades u;
    int a = 0;
    int b = 0;
    for (int i = 0; i < t.cantidadJugadores; i++) {
        auto temp = Jugador(t.tamano, i);
        while (i> 0 && (&t.casillas[a][b] != t.jugadores[i - 1].getPosicion())) {
            a = u.getRandomNumber(0, 1) * (t.tamano - 1);
            b = u.getRandomNumber(0, 1) * (t.tamano - 1);
        }
        cout << "a: " << a << " b: " << b << endl;


        t.casillas[a][b].setIdJugador(i);
        temp.setPosicion(&t.casillas[a][b]);

        t.jugadores.push_back(temp);
    }
};

Tablero::Tablero() {
    tamano = 0;
    cantidadJugadores = 0;
    jugadores = {};
    casillas = {};
}

Tablero::Tablero(int t, int cj) {
    tamano = t;
    cantidadJugadores = cj;
    generarCasillas(*this);
    generarJugadores(*this);
}

int Tablero::getTamano() {
    return tamano;
}

void Tablero::setTamano(int t) {
    tamano = t;
}

int Tablero::getCantidadJugadores() {
    return cantidadJugadores;
}

void Tablero::setCantidadJugadores(int cj) {
    this->cantidadJugadores = cj;
}

vector<Jugador> Tablero::getJugadores() {
    return jugadores;
}

void Tablero::setJugadores(vector<Jugador> jugadores) {
    this->jugadores = jugadores;
}

vector<vector<Casilla> > Tablero::getCasillas() {
    return casillas;
}

void Tablero::setCasillas(vector<vector<Casilla> > casillas) {
    this->casillas = casillas;
}

void Tablero::printTablero() {
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            if (-1 != casillas[i][j].getIdJugador()) {
                cout << " " << casillas[i][j].getIdJugador() + 1 << " " << endl;
            } else if (1 == casillas[i][j].getEfecto()) {
                cout << " P ";
            } else if (2 == casillas[i][j].getEfecto()) {
                cout << " C ";
            } else {
                cout << " . ";
            }
        }
        cout << endl;
    }
}

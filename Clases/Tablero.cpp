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
        do {
            a = u.getRandomNumber(0, 1) * (t.tamano - 1);
            b = u.getRandomNumber(0, 1) * (t.tamano - 1);
        } while (t.casillas[a][b].getIdJugador() != -1);
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

Casilla Tablero::getCasilla(int a, int b) {
    return casillas[a][b];
}

void Tablero::setCasillas(vector<vector<Casilla> > casillas) {
    this->casillas = casillas;
}

void Tablero::printTablero() {
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            if (-1 != casillas[i][j].getIdJugador()) {
                if (jugadores[casillas[i][j].getIdJugador()].getPuntosVida() < 1) {
                    cout << " x ";
                } else {
                    cout << " " << casillas[i][j].getIdJugador() + 1 << " ";
                }
            } else if (0 != casillas[i][j].getEfecto()) {
                // Esto hay que eliminarlo
                cout << " # ";
            } else if (i == j && i == (tamano) / 2) {
                cout << " W ";
            } else {
                cout << " . ";
            }
        }
        cout << endl;
    }
}

void killAllPlayers(Tablero &obj, int i) {
    for (int j = 0; j < obj.cantidadJugadores; j++) {
        auto jugador = &obj.jugadores[j];
        if (i != j) {
            jugador->setPuntosVida(0);
        }
    }
}

void Tablero::turnoJugador(int i, Dado &d) {
    vector<int> direcciones;
    auto jugador = &jugadores[i];
    if (jugador->getPuntosVida() <= 0) {
        jugador->setPuntosVida(0);
        return;
    }
    cout << "Puntos de vida: " << jugador->getPuntosVida() << endl;
    int opc;
    auto coordenadas = jugador->getPosicion()->getCoordenadas();
    Casilla *nuevaCasilla;

    cout << "(";
    for (int j = 0; j < 4; j++) {
        auto direccion = d.getDirecciones()[j];
        cout << " " << direccion << " ";
        if (direccion == 0) {
            direcciones.push_back(0);
            continue;
        }
        if (j == 0 && (coordenadas[0] - 1) < 0) {
            direcciones.push_back(0);
            continue;
        }

        if (j == 1 && (coordenadas[0] + 1) > tamano - 1) {
            direcciones.push_back(0);
            continue;
        }

        if (j == 2 && (coordenadas[1] - 1) < 0) {
            // ya esta a la izq
            direcciones.push_back(0);
            continue;
        }

        if (j == 3 && (coordenadas[1] + 1) > tamano - 1) {
            // ya esta a la derecha
            direcciones.push_back(0);
            continue;
        }
        if (jugador->getPuntosVida() < direccion) {
            direcciones.push_back(0);
            continue;
        }
        direcciones.push_back(1);
    }
    // cout << ")" << endl;

    if (direcciones[0] == 1) {
        cout << "1. +1 arriba" << endl;
    }

    if (direcciones[1] == 1) {
        cout << "2. +1 abajo" << endl;
    }

    if (direcciones[2] == 1) {
        cout << "3. +1 a la izquierda" << endl;
    }

    if (direcciones[3] == 1) {
        cout << "4. +1 a la derecha" << endl;
    }
    if (direcciones == vector<int>{0, 0, 0, 0}) {
        cout << "No hay movimientos validos. " << endl;
        return;
    }
    cout << "Ingrese una opcion: ";
    cin >> opc;

    switch (opc) {
        case 1: //Arriba
            nuevaCasilla = &casillas[coordenadas[0] - 1][coordenadas[1]];
            jugador->mover(nuevaCasilla, d.getDirecciones()[0]);
            if (nuevaCasilla->getEfecto() == 2) {
                cout << "1. Eliminar a los demas jugadores" << endl;
                cout << "2. Sumarse " << d.getDirecciones()[0] << " puntos de vida" << endl;
                int premio;
                cin >> premio;
                if (1 == premio) {
                    killAllPlayers(*this, i);
                    return;
                }
                if (2 == premio) {
                    jugador->setPuntosVida(d.getDirecciones()[0]);
                }
            }
            break;
        case 2: //Abajo
            nuevaCasilla = &casillas[coordenadas[0] + 1][coordenadas[1]];
            jugador->mover(nuevaCasilla, d.getDirecciones()[1]);
            if (nuevaCasilla->getEfecto() == 2) {
                cout << "1. Eliminar a los demas jugadores" << endl;
                cout << "2. Sumarse " << d.getDirecciones()[1] << " puntos de vida" << endl;
                int premio;
                cin >> premio;
                if (1 == premio) {
                    killAllPlayers(*this, i);
                    return;
                }
                if (2 == premio) {
                    jugador->setPuntosVida(d.getDirecciones()[1]);
                }
            }
            break;
        case 3: //izquierda
            nuevaCasilla = &casillas[coordenadas[0]][coordenadas[1] - 1];
            jugador->mover(nuevaCasilla, d.getDirecciones()[2]);
            if (nuevaCasilla->getEfecto() == 2) {
                cout << "1. Eliminar a los demas jugadores" << endl;
                cout << "2. Sumarse " << d.getDirecciones()[2] << " puntos de vida" << endl;
                int premio;
                cin >> premio;
                if (1 == premio) {
                    killAllPlayers(*this, i);
                    return;
                }
                if (2 == premio) {
                    jugador->setPuntosVida(d.getDirecciones()[2]);
                }
            }
            break;
        case 4:
            nuevaCasilla = &casillas[coordenadas[0]][coordenadas[1] + 1];
            jugador->mover(nuevaCasilla, d.getDirecciones()[2]);
            if (nuevaCasilla->getEfecto() == 2) {
                cout << "1. Eliminar a los demas jugadores" << endl;
                cout << "2. Sumarse " << d.getDirecciones()[3] << " puntos de vida" << endl;
                int premio;
                cin >> premio;
                if (1 == premio) {
                    killAllPlayers(*this, i);
                    return;
                }
                if (2 == premio) {
                    jugador->setPuntosVida(d.getDirecciones()[3]);
                }
            }
            break;
    }
}

//
// Created by OMAR DENILSON on 9/11/2025.
//

#include "Tablero.h"

#include <iostream>
#include <cmath>
#include "Utilidades.h"


/*
 * 15*1.5=22
 * 2*23=46
 * 4.5*31=140
 */
void generarCasillas(Tablero &t) {
    Utilidades u;
    for (int i = 0; i < t.tamano; i++) {
        vector<Casilla> temp;
        for (int j = 0; j < t.tamano; j++) {
            Casilla c;
            c.setCoordenadas({i, j});
            if (j != i || j == t.tamano / 2) {
                int k = log(pow(2, 3 * t.tamano));
                c.setEfecto(u.getRandomNumber(0, k));
            }
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
    generarCasillas(*this);
    for (auto jugador: jugadores) {
        jugador.getDado().setMax(t);
    }
}

int Tablero::getCantidadJugadores() {
    return cantidadJugadores;
}

void Tablero::setCantidadJugadores(int cj) {
    this->cantidadJugadores = cj;
    generarJugadores(*this);
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

void Tablero::ejecutarPremio(int i, Dado pe, int direccion) {
    /*
     * ESTA FUNCION EJECUTA LA PREMIACION PARA EL JUGADOR QUE LLEGUE A UNA CASILLA CON ESTE EFECTO.
     * PRIMERO SE PRESENTAN LAS OPCIONES AL JUGADOR DE: ELIMINAR A LOS DEMAS JUGADORES Y GANAR AUTOMATICAMENTE, O AÑADIRSE PUNTOS DE VIDA ACORDE AL NUMERO ARROJADO POR EL DADO
     * EN CASO DE ELEGIR LA PRIMERA OPCION SIMPLEMENTE SE CONFIGURAN LOS PUNTOS DE VIDA DE LOS DEMAS JUGADORES EN 0 Y SE RETORNA LA FUNCION
     * DE OTRA MANERA SIMPLEMENTE SE SUMA A LOS PUNTOS DE VIDA DEL JUGADOR LA CANTIDAD OBTENIDA POR MEDIO DEL OBJETO dado
     */
    cout << "1. Eliminar a los demas jugadores" << endl;
    cout << "2. Sumarse " << pe.getDirecciones()[direccion] << " puntos de vida" << endl;
    int premio;
    cin >> premio;
    if (1 == premio) {
        for (int j = 0; j < this->cantidadJugadores; j++) {
            auto jugador = &this->jugadores[j];
            if (i != j) {
                jugador->setPuntosVida(0);
            }
        }
        return;
    }
    if (2 == premio) {
        jugadores[i].setPuntosVida(jugadores[i].getPuntosVida() + pe.getDirecciones()[direccion]);
        jugadores[i].getDado().setMax(jugadores[i].getPuntosVida());
    }
}

void Tablero::turnoJugador(int i) {
    /*
     * ESTA FUNCION HACE LA MAYOR PARTE DE LA LOGICA INVOLUCRADA EN MOVER LOS JUGADORES, EJECUTAR LOS PREMIOS Y CASTIGOS, Y ACTUALIZAR LAS CASILLAS
     * RECIBE int i QUE ES EL ID DEL JUGADOR QUE TIENE EL TURNO, Y Dado &d QUE ES LA DIRECCION EN MEMORIA DEL OBJETO DADO ASIGNADO A LA PARTIDA
     * A PARTIR DE ESTO RECORRE LAS 4 DIRECCIONES DEL DADO, SI LA DIRECCION CUMPLE CON LAS SIGUIENTES CONDICIONES AGREGA 1 EN LA POSICION CORRESPONDIENTE
     * EN EL VECTOR direcciones. LAS CONDICIONES SON:
     *  - EL VALOR NO ES 0
     *  - SI LA DIRECCION ES ARRIBA EL JUGADOR NO PUEDE ESTAR EN EL VECTOR 1 DE LA MATRIZ casillas
     *  - SI LA DIRECCION ES ABAJO EL JUGADOR NO PUEDE ESTAR EN EL VECTOR tamano - 1 DE LA MATRIZ casillas
     *  - SI LA DIRECCION ES IZQUIERDA EL JUGADOR NO PUEDE ESTAR EN LA PRIMERA POSICION DE NINGUN VECTOR EN LA MATRIZ casillas
     *  - SI LA DIRECCION ES DERECHA EL JUGADOR NO PUEDE ESTAR EN LA ULTIMA POSICION DE NINGUN VECTOR EN LA MATRIZ casillas
     *
     *  UTILIZANDO ESTE VECTOR DIRECCIONES SE LE PRESENTAN AL JUGADOR LOS MOVIMIENTOS QUE PUEDE HACER
     *  LUEGO MEDIANTE UN SWITCH CASE SE DA LA INTERPRETACION A LA DECISION DEL JUGADOR
     *  DE MANERA GENERAL CADA CASO HACE LO SIGUIENTE
     *
     *  GUARDAR LA DIRECCION EN MEMORIA DE LA CASILLA DONDE EL JUGADOR SE VA A MOVER
     *  EJECUTA EL METODO jugador.mover
     *  SI LA CASILLA TIENE EFECTO DE PREMIO EJECUTA EL METODO Tablero.ejecutarPremio
     */
    vector<int> direcciones;
    auto jugador = &jugadores[i];
    Dado pe = jugadores[i].getDado();
    pe.lanzar();

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
        auto direccion = pe.getDirecciones()[j];
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
    cout << ")" << endl;

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
    if (direcciones == vector{0, 0, 0, 0}) {
        cout << "No hay movimientos validos. " << endl;
        return;
    }
    cout << "Ingrese una opcion: ";
    cin >> opc;

    switch (opc) {
        case 1: //Arriba
            //guard
            if (direcciones[0] == 0) {
                cout << "Esta direccion no es valida." << endl;
                cout << "Turno perdido. -1 puntos de vida." << endl;
                jugador->setPuntosVida(jugador->getPuntosVida() - 1);
                return;
            }
            nuevaCasilla = &casillas[coordenadas[0] - 1][coordenadas[1]];
            jugador->mover(nuevaCasilla, pe.getDirecciones()[0]);
            if (nuevaCasilla->getEfecto() == 2) {
                ejecutarPremio(i, pe, 0);
            }
            break;
        case 2: //Abajo
            //guard
            if (direcciones[1] == 0) {
                cout << "Esta direccion no es valida." << endl;
                cout << "Turno perdido. -1 puntos de vida." << endl;
                jugador->setPuntosVida(jugador->getPuntosVida() - 1);
                return;
            }
            nuevaCasilla = &casillas[coordenadas[0] + 1][coordenadas[1]];
            jugador->mover(nuevaCasilla, pe.getDirecciones()[1]);
            if (nuevaCasilla->getEfecto() == 2) {
                ejecutarPremio(i, pe, 1);
            }
            break;
        case 3: //izquierda
            //guard
            if (direcciones[2] == 0) {
                cout << "Esta direccion no es valida." << endl;
                cout << "Turno perdido. -1 puntos de vida." << endl;
                jugador->setPuntosVida(jugador->getPuntosVida() - 1);
                return;
            }
            nuevaCasilla = &casillas[coordenadas[0]][coordenadas[1] - 1];
            jugador->mover(nuevaCasilla, pe.getDirecciones()[2]);
            if (nuevaCasilla->getEfecto() == 2) {
                ejecutarPremio(i, pe, 2);
            }
            break;
        case 4:
            //guard
            if (direcciones[3] == 0) {
                cout << "Esta direccion no es valida." << endl;
                cout << "Turno perdido. -1 puntos de vida." << endl;
                jugador->setPuntosVida(jugador->getPuntosVida() - 1);
                return;
            }
            nuevaCasilla = &casillas[coordenadas[0]][coordenadas[1] + 1];
            jugador->mover(nuevaCasilla, pe.getDirecciones()[2]);
            if (nuevaCasilla->getEfecto() == 2) {
                ejecutarPremio(i, pe, 3);
            }
            break;
    }
}

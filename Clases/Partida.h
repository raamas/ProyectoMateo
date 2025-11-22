//
// Created by OMAR DENILSON on 9/11/2025.
//

#ifndef PROYECTOMATEO_PARTIDA_H
#define PROYECTOMATEO_PARTIDA_H
#include <vector>

#include "Dado.h"
#include "Jugador.h"
#include "Tablero.h"
using namespace std;

class Partida {
    int cantidadJugadores;
    int dificultad;
    Tablero tablero;
    int idGanador;

public:
    Partida();

    Partida(int d, int cj);

    int getCantidadJugadores();

    void setCantidadJugadores(int cj);

    int getDificultad();

    void setDificultad(int d);

    Tablero &getTablero();

    void setTablero(Tablero t);

    int getGanador();
};


#endif //PROYECTOMATEO_PARTIDA_H

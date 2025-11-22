//
// Created by OMAR DENILSON on 9/11/2025.
//

#ifndef PROYECTOMATEO_JUGADOR_H
#define PROYECTOMATEO_JUGADOR_H
#include "Casilla.h"
#include "Dado.h"

class Jugador {
    int id;
    int puntosVida;
    Casilla *posicion;
    Dado dado;

public:
    Jugador();

    Jugador(int pv, int id);

    int getId();

    void setId(int id);

    int getPuntosVida();

    void setPuntosVida(int pv);

    Casilla *getPosicion();

    void setPosicion(Casilla *casilla);

    Dado &getDado();

    void setDado(Dado d);

    void mover(Casilla *nuevaCasilla, int nuevoPuntosVida);
};


#endif //PROYECTOMATEO_JUGADOR_H

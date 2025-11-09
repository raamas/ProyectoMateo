//
// Created by OMAR DENILSON on 9/11/2025.
//

#ifndef PROYECTOMATEO_TABLERO_H
#define PROYECTOMATEO_TABLERO_H
#include <vector>
#include "Casilla.h"
#include "Jugador.h"
using namespace std;

class Tablero {
    int tamano;
    int cantidadJugadores;
    vector<Jugador> jugadores;
    vector<vector<Casilla> > casillas;

public:
    Tablero();

    Tablero(int t, int cj);

    int getTamano();

    void setTamano(int t);

    int getCantidadJugadores();

    void setCantidadJugadores(int cj);

    vector<Jugador> getJugadores();

    void setJugadores(vector<Jugador> jugadores);

    vector<vector<Casilla> > getCasillas();

    void setCasillas(vector<vector<Casilla> > casillas);

    void printTablero();

    friend void generarCasillas(Tablero &t);

    friend void generarJugadores(Tablero &t);
};


#endif //PROYECTOMATEO_TABLERO_H

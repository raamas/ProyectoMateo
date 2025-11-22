//
// Created by OMAR DENILSON on 9/11/2025.
//

#ifndef PROYECTOMATEO_TABLERO_H
#define PROYECTOMATEO_TABLERO_H
#include <vector>
#include "Casilla.h"
#include "Dado.h"
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

    Casilla getCasilla(int a, int b);

    void setCasillas(vector<vector<Casilla> > casillas);

    void printTablero();

    void turnoJugador(int i);

    friend void generarCasillas(Tablero &t);

    friend void generarJugadores(Tablero &t);

    void ejecutarPremio(int i,Dado pe, int direccion);
};


#endif //PROYECTOMATEO_TABLERO_H

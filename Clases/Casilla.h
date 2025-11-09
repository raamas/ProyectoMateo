//
// Created by OMAR DENILSON on 9/11/2025.
//

#ifndef PROYECTOMATEO_CASILLA_H
#define PROYECTOMATEO_CASILLA_H

#include <vector>
using namespace std;

class Casilla {
    int efecto; //1 Castigo 2 Premio
    int idJugador;
    vector<int> coordenadas;

public:
    Casilla();

    Casilla(int e);

    int getEfecto();

    void setEfecto(int e);

    int getIdJugador();

    void setIdJugador( int i);

    vector<int> getCoordenadas();

    int getCoordenadas(int p);

    void setCoordenadas(vector<int> c);
};


#endif //PROYECTOMATEO_CASILLA_H

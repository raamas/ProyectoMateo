//
// Created by OMAR DENILSON on 9/11/2025.
//

#ifndef PROYECTOMATEO_UTILIDADES_H
#define PROYECTOMATEO_UTILIDADES_H
#include "Partida.h"
#include <fstream>

class Utilidades {
public:
    Utilidades();
    int getRandomNumber(int min, int max);
    void guardarPartida(Partida *p);
    Partida cargarPartida();
    vector<string> split(string s, char c);

};


#endif //PROYECTOMATEO_UTILIDADES_H
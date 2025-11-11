#include <iostream>

#include "Clases/Partida.h"
#include "Clases/Tablero.h"
#include "Clases/Casilla.h"
#include "Clases/Utilidades.h"
using namespace std;

int main() {
    Utilidades u;
    int a = 4;
    Partida p{31, a};
    p.getTablero().printTablero();
    while (true) {
        for (int i = 0; i < a; i++) {
            cout << "Turno Jugador #" << i + 1 << endl;
            p.getDado().lanzar();
            p.getTablero().turnoJugador(i, p.getDado());
            p.getTablero().printTablero();
        }
    }

    return 0;
}

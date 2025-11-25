#include <iostream>

#include "Clases/Partida.h"
#include "Clases/Tablero.h"
#include "Clases/Casilla.h"
#include "Clases/Utilidades.h"
#include <cstdlib>
using namespace std;

int main() {
    int opc;
    Utilidades u;
    int cantidadJugadores, dificultad;
    Partida p;

    cout << "**CARRERA AL CENTRO**" << endl;
    cout << "1. Nueva partida" << endl;
    // cout << "2. Cargar partida" << endl;
    cout << "3. Salir" << endl;
    cin >> opc;

    switch (opc) {
        case 1:
            cout << "Ingrese el numero de jugadores que participaran (1-4)" << endl;
            cin >> cantidadJugadores;
            cout << "Que dificultad desea jugar." << endl;
            cout << "1. Tablero 15x15" << endl;
            cout << "2. Tablero 23x23" << endl;
            cout << "3. Tablero 31x31" << endl;
            cin >> dificultad;

            if (dificultad == 1) {
                dificultad = 15;
            } else if (dificultad == 2) {
                dificultad = 23;
            } else if (dificultad == 3) {
                dificultad = 31;
            }
            p.setDificultad(dificultad);
            p.setCantidadJugadores(cantidadJugadores);

            while (p.getGanador() == -1) {
                for (int i = 0; i < cantidadJugadores; i++) {
                    p.getTablero().printTablero();
                    cout << "Turno Jugador #" << i + 1 << endl;
                    p.getTablero().turnoJugador(i);
                    u.guardarPartida(&p);
                }
            }
            cout << "EL GANADOR ES EL JUGADOR #" << p.getGanador() + 1 << " FELICITACIONES!!!" << endl;
            break;
        case 2:
            // p = cargarPartida();
            break;
        case 3:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opcion no valida. Saliendo..." << endl;
            break;
    }


    return 0;
}

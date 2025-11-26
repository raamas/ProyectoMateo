//
// Created by OMAR DENILSON on 9/11/2025.
//

#include "Utilidades.h"

#include <iostream>
#include <random>


Utilidades::Utilidades() {
};

// LA VERDAD ESTO LO HIZO GPT LOL
int randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

int Utilidades::getRandomNumber(int min, int max) {
    return randomInt(min, max);
}

//Esto no lo hizo gpt
void Utilidades::guardarPartida(Partida *p) {
    //CANTIDADJUGADORES;DIFICULTAD;IDGANADOR;PIDJUGADOR;PUNTOSVIDAJUGADOR;MAXDADOJUGADOR;CORDENADASA,CORDENADASB;EFECTOCASILLAJUGADOR;
    ofstream writeFile("../partidas/test.txt");
    writeFile << p->getCantidadJugadores() << ";"
            << p->getDificultad() << ";"
            << p->getGanador() << ";";
    for (auto player: p->getTablero().getJugadores()) {
        writeFile << player.getId() << ";"
                << player.getPuntosVida() << ";"
                << player.getDado().getMax() << ";"
                << player.getPosicion()->getCoordenadas()[0] << "," << player.getPosicion()->getCoordenadas()[1] << ";"
                << player.getPosicion()->getEfecto() << ";";
    }
};


Partida Utilidades::cargarPartida() {
    ifstream readFile("../partidas/test.txt");
    string s;
    vector<string> info;
    while (getline(readFile, s)) {
        info = split(s, ';');
    }

    Partida p = {stoi(info[1]), stoi(info[0])};
    auto casillas = p.getTablero().getCasillas();

    vector<Jugador> temp;
    for (int i = 0; i < stoi(info[0]); i++) {
        auto _ = (info[3 + i * 5]).at(1);
        int id = _ - '0';
        Jugador j = {stoi(info[4 + i * 5]), id};
        j.getDado().setMax(stoi(info[5 + i * 5]));

        int a = stoi(split(info[6 + i * 5], ',')[0]);
        int b = stoi(split(info[6 + i * 5], ',')[1]);
        casillas.at(a).at(b).setEfecto(stoi(info[7 + i * 5]));
        casillas.at(a).at(b).setIdJugador(id);
        temp.push_back(j);
    }

    for (int i = 0; i > casillas.size(); i++) {
        for (int j = 0; j < casillas.size(); j++) {
            casillas.at(i).at(j).setCoordenadas({i, j});
            cout << casillas.at(i).at(j).getCoordenadas().at(0) << endl;
        }
    }
    p.getTablero().setCasillas(casillas);

    for (int i = 0; i < temp.size(); i++) {
        Jugador jugador = temp[i];
        int a = stoi(split(info[6 + i * 5], ',')[0]);
        int b = stoi(split(info[6 + i * 5], ',')[1]);
        auto _ = p.getTablero().getCasillaAddress(a, b);
        jugador.setPosicion(_);
    }

    p.getTablero().setJugadores(temp);

    int ganador = stoi(info[2]);
    p.setGanador(ganador);

    return p;
}

vector<string> Utilidades::split(string s, char c) {
    vector<string> res;
    string temp;
    for (char ch: s) {
        if (ch == c) {
            res.push_back(temp);
            temp.clear();
            continue;
        }

        temp += ch;
    }

    res.push_back(temp);

    return res;
}

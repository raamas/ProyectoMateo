cmake_minimum_required(VERSION 4.0)
project(ProyectoMateo)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProyectoMateo main.cpp
        Clases/Jugador.cpp
        Clases/Jugador.h
        Clases/Tablero.cpp
        Clases/Tablero.h
        Clases/Partida.cpp
        Clases/Partida.h
        Clases/Dado.cpp
        Clases/Dado.h
        Clases/Casilla.cpp
        Clases/Casilla.h
        Clases/Utilidades.cpp
        Clases/Utilidades.h)

//
// Created by OMAR DENILSON on 9/11/2025.
//

#include "Utilidades.h"

#include <iostream>
#include <random>

Utilidades::Utilidades() {
};

// Generate random integer in range [min, max]
int randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

int Utilidades::getRandomNumber(int min, int max) {
    return randomInt(min, max);
}

//
// Created by OMAR DENILSON on 9/11/2025.
//

#ifndef PROYECTOMATEO_DADO_H
#define PROYECTOMATEO_DADO_H
#include <vector>
using namespace std;

class Dado {
    vector<int> direcciones {0,0,0,0};
    int max;
public:
    Dado();
    Dado(int max);

    int getMax();
    void setMax(int max);

    vector<int> getDirecciones();
    // void setDirecciones()

    void lanzar();
};


#endif //PROYECTOMATEO_DADO_H
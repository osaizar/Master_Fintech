//
// Created by Andoni on 26/09/2018.
//
#include <iostream>
#include <random>
#include "Matriz.h"

matriz::matriz (int f, int c) :
    filas{f},
    columnas{c}
{
    valores = new double [filas*columnas];
    for(int i = 0; i < (filas*columnas) ; i++){
        valores[i] = 0;
    }

};

matriz::matriz() :
    filas{0},
    columnas{0}
{
}

void matriz::pintar_matriz(){
    using namespace std;
    for(int i = 0; i < (filas*columnas); i++){
     cout << valores[i] << " ";
    if((i+1)%(filas) == 0) cout << "\n";
    }
}

void matriz::rellenar_matriz() {

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 100.0);
    for (int n = 0; n < (filas*columnas); ++n) {
        //Use dis to transform the random unsigned int generated by gen into a double in [1, 2)
       valores[n]=dis(gen);
    }
}

matriz matriz::operator+(matriz &m) {
    int i, j;
    int fil = m.filas;
    int col = m.columnas;
    matriz matrizRes(fil,col);
    for  (i=0;i<(fil*col);i++)
    {
        matrizRes.valores[i] = this->valores[i]+m.valores[i];
    }
    return matrizRes;
}

double matriz::operator()(double f, double c) {
    int valor = f*(columnas-1) + c-1;
    return valores[valor];

}


matriz matriz::operator*(matriz &m) {
    matriz mRes(filas, m.columnas);
    int i, j, k;

    /* Final matrix position loop */
    for (i = 0; i < m.columnas ; i++) {
        /* Each matrix rotation loop */
        for (j = 0; j < this->filas; j++) {
            for (k = 0; k < m.columnas; k++) {
                /* Ex: M3(1,1) = M3(1,1) + M1(1,2)*M2(2,1) */
                mRes.valores[i * mRes.columnas + j] = mRes.valores[i * mRes.columnas + j] +
                                                  valores[(i * this->columnas) + k] * m.valores[k * m.columnas + j];
            }
        }
    }
    return mRes;
}
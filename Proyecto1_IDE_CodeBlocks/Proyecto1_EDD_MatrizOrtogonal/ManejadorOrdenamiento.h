#ifndef MANEJADORORDENAMIENTO_H
#define MANEJADORORDENAMIENTO_H

#include <cstdlib>
#include <iostream>
#include <string>
#include "MatrizOrtogonal.cpp"

using namespace std;
class ManejadorOrdenamiento{//en realidad esta clase debería estar en la de MatrizOrtogonal, pero si lo hago creo que crearía un bucle por los include, aunque en Java el bucle solo sucede si dos clases que se implementan entre sí y en sus constructores se ini a ambas...
    private:
        MatrizOrtogonal<string>* matrizOrdenada;
        string getMenorDato(MatrizOrtogonal<string>*, NodoOrtogonal<string>*,
            NodoOrtogonal<string>*, NodoOrtogonal<string>*, int);//hasta donde sé, este método solo se utiliza para ordenar la matriz...

    public:
        void ordenarMatriz(MatrizOrtogonal<string>*, string);
        bool esMatrizOrdenada(MatrizOrtogonal<string>*);
        MatrizOrtogonal<string>* getMatrizOrdenada();
};
#endif

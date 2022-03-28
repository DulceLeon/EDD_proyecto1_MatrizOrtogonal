#ifndef TABLERO_H
#define TABLERO_H

#include <cstdlib>
#include <iostream>
#include <string>
#include "MatrizOrtogonal.cpp"

using namespace std;//no me recuerdo si debo incluirlo en ambos archivos [cabecera y def de la clase...]
class Tablero{
    private:            
        MatrizOrtogonal<string>* matriz;
        string symbBlank;
        NodoOrtogonal<string>* espacioVacio;
        string movimientosPosibles[6];//el tamaño de los arreglos si es nec colocarlo en el .h en caso de tener archivos separados...
    
    public:
        Tablero();//cnstrct por defecto
        Tablero(int, int, int);//ancho, alto, #niveles
        void agregarElementos(string);        
        void setEspacioVacio(void);
        int getLevels(void);
        int getWidth(void);
        int getHeight(void);
        string getSymbBlank();
        string* getMovimientosPosibles(void);//si mal no recuedo, para devolver un arreglo, debe devolverse un puntero...
        MatrizOrtogonal<string>* getMatrizOrtogonal(void);
        NodoOrtogonal<string>* getNodoVacio(void);

        ~Tablero();
};
#endif
//aquí se tendrá a la matriz ortogonal con los punteros en Z ya establecidos
//tb se tendrá el ptero para el espacio vacío
//E imagino que lo pteros de una vez, o el nombre de las direcciones posibles
//que se pueden escoger a partir del ptro
    //Sería bueno inventar un algoritmo para calc...

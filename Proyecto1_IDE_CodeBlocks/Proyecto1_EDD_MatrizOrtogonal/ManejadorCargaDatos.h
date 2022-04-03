#ifndef MANEJADOR_CARGA_DATOS_H
#define MANEJADOR_CARGA_DATOS_H
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>//permite escribir y leer archivos
#include "Tablero.h"

class ManejadorCargaDatos{
    private:
        char delimitador;
        //Tablero* tableroCargado;

    public:
        ManejadorCargaDatos();
        bool cargarDatos(Tablero**, string*);
        //Tablero* getTableroCargado();
};
#endif

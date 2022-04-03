#ifndef CREADORTABLERO_H
#define CREADORTABLERO_H

#include <cstdlib>
#include <iostream>
#include <cstring>
#include "Tablero.h"
#include "ManejadorCargaDatos.h"

class ManejadorTablero{
    private:
        char solicitarDatos(Tablero**);
        string jugador;
        Tablero* tableroOriginal;
        ManejadorCargaDatos* manejadorCargaDatos;

    public:
        ManejadorTablero();
        char crearTableroManual(Tablero**);
        char crearTableroAleatorio(Tablero*);
        bool cargarTablero(Tablero**);
        //Tablero* getTableroCargado();
        char confirmarAccion(char);//se va a tener aquí para mientras, cuando ya se verfique que todo funciona, se pasará a otra clase y si no funciona después de eso es por la "definición múltiple", que el compilador detectaría a pesar de tener los #ifndef, def, y endif, lo cual podría tener la raíz en no haber declarado en el orden correcto la compi en el Makefile...
        string getNombreJugador();
        Tablero* getTableroOriginal();
};
#endif

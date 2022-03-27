#ifndef CREADORTABLERO_H
#define CREADORTABLERO_H

#include <cstdlib>
#include <iostream>
#include <cstring>
#include "Tablero.h"

class ManejadorTablero{
    private:    
        char solicitarDatos(Tablero*);        
        //char* jugador;
        string jugador;
        Tablero* tableroOriginal;

    public:
        ManejadorTablero();
        char crearTableroManual(Tablero*);
        char crearTableroAleatorio(Tablero*);
        char cargarTablero(Tablero*);
        //void setNombre(char*);
        char confirmarAccion(char);//se va a tener aquí para mientras, cuando ya se verfique que todo funciona, se pasará a otra clase y si no funciona después de eso es por la "definición múltiple", que el compilador detectaría a pesar de tener los #ifndef, def, y endif, lo cual podría tener la raíz en no haber declarado en el orden correcto la compi en el Makefile...
        string getNombreJugador();
        Tablero* getMatrizOriginal();
};
#endif
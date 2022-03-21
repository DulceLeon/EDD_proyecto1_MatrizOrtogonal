//#include <cstdlib>
//#include <iostream>
//#include <string>//hasta donde leí, por la defin de los .h, esto no debo incluirlo...
#include "Tablero.h"

using namespace std;

Tablero::Tablero(int ancho, int alto, int niveles){
    this->symbBlank = new string("x");
    matriz = new MatrizOrtogonal<string>(ancho, alto, niveles);
    movimientosPosibles[6];//si da error, es poque le diste tamaño aqui, por lo tanto deberás colocar movP[6] en el .h
}

void Tablero::agregarElementos(string elemento){//se invocará en el manejador del juego del 15, en cada forma de ingresar datos...
    this->matriz->agregarContenido(new string(elemento));    
}

void Tablero::setEspacioVacio(){
    espacioVacio = this->matriz->buscarNodo(this->symbBlank);//new string("x")
}//se invocará antes del método para obtener los movimientos posibles, específicamente después de crear solicitar todos los datos, porque despues este nodo se obtendrá del método shift...

string* Tablero::getMovimientosPosibles(){//pongo el *, porque, se deolverá un arreglo y ellos son objs entonces hay que hacer ref a ellos, con esto se obtiene acceso al 1er elemento y como una lista enlazada, al menos en ese sentido, se puede acceder a los demás...        
    if(this->espacioVacio->getAnterior() != NULL){
        movimientosPosibles[0] = "izquierda";
    }else{
        movimientosPosibles[0] = "";
    }
    if(this->espacioVacio->getSiguiente() != NULL){
        movimientosPosibles[1] = "derecha";
    }else{
        movimientosPosibles[1] = "";
    }
    if(this->espacioVacio->getArriba() != NULL){
        movimientosPosibles[2] = "arriba";
    }else{
        movimientosPosibles[2] = "";
    }
    if(this->espacioVacio->getAbajo() != NULL){
        movimientosPosibles[3] = "abajo";
    }else{
        movimientosPosibles[3] = "";
    }
    if(this->espacioVacio->getSaliente() != NULL){
        movimientosPosibles[4] = "saliente";
    }else{
        movimientosPosibles[4] = "";
    }
    if(this->espacioVacio->getEntrante() != NULL){
        movimientosPosibles[5] = "entrante";
    }else{
        movimientosPosibles[5] = "";
    }
    return movimientosPosibles;
}//este siempre será invocado después de tener 

MatrizOrtogonal<string>* Tablero::getMatrizOrtogonal(){return this->matriz;}

NodoOrtogonal<string>* Tablero::getNodoVacio(){return this->espacioVacio;}

int Tablero::getLevels(){this->matriz->getNumeroNiveles();}

int Tablero::getWidth(){this->matriz->getAncho();}

int Tablero::getHeight(){this->matriz->getAlto();}

Tablero::~Tablero(){
    delete matriz;
    delete movimientosPosibles;
    delete symbBlank;
}
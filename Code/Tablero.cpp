//#include <cstdlib>
//#include <iostream>
//#include <string>//hasta donde leí, por la defin de los .h, esto no debo incluirlo...
#include "Tablero.h"

using namespace std;

Tablero::Tablero(){}

Tablero::Tablero(int ancho, int alto, int niveles){
    this->symbBlank = ("x");
    matriz = new MatrizOrtogonal<string>(ancho, alto, niveles);        
    cout<<"instancia matriz-tablero: "<<matriz;
}

void Tablero::agregarElementos(string elemento){//se invocará en el manejador del juego del 15, en cada forma de ingresar datos...
    this->matriz->agregarContenido(elemento);    
}

void Tablero::setEspacioVacio(void){
    espacioVacio = this->matriz->getUltimoNodo();//pues por defecto se tendrá eso..
}//se invocará antes del método para obtener los movimientos posibles, específicamente después de crear solicitar todos los datos, porque despues este nodo se obtendrá del método shift...

string* Tablero::getMovimientosPosibles(void){//pongo el *, porque, se deolverá un arreglo y ellos son objs entonces hay que hacer ref a ellos, con esto se obtiene acceso al 1er elemento y como una lista enlazada, al menos en ese sentido, se puede acceder a los demás...        
    if(this->espacioVacio->getAnterior() != NULL){
        movimientosPosibles[0] = "izquierda";//si al arreglo le add un * [es decir, indicara que es un puntero], el contenido debería asignarlo: new string("izquierda")
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

MatrizOrtogonal<string>* Tablero::getMatrizOrtogonal(void){return this->matriz;}

string Tablero::getSymbBlank(){return this->symbBlank;}

NodoOrtogonal<string>* Tablero::getNodoVacio(void){return this->espacioVacio;}

int Tablero::getLevels(void){return this->matriz->getNumeroNiveles();}

int Tablero::getWidth(void){return this->matriz->getAncho();}

int Tablero::getHeight(void){return this->matriz->getAlto();}

Tablero::~Tablero(){
    this->matriz->~MatrizOrtogonal();//para eliminar lo que contiene dentro
    delete matriz;//y luego de eso eliminarse a si misma xD
    //delete movimientosPosibles;//creo que debo hacerlo un puntero... me recuerdo que la aux mencionó algo así, y dijjo que recordaba que sin el * no iba a funcionar pero en realidad si le salió...    
}
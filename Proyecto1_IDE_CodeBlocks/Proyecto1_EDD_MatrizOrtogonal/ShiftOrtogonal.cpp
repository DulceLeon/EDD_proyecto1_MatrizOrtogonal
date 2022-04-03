#ifndef SHIFTORTOGONAL_H
#define SHIFTORTOGONAL_H
#include <cstdlib>
#include <iostream>
#include "NodoOrtogonal.cpp"

using namespace std;

template <class T>
class ShiftOrtogonal{
    public:
        //si le colocara a este método tb shift, podría comprobar si sucede algún conflicto, aunque no debería porque en cada método especifiqué la clase y en el caso de las plantillas, tb esta "firma"
        void shiftNodes(NodoOrtogonal<T>*, NodoOrtogonal<T>*, int);//1. el nodo en cuestión, 2. el nodo de intercambio, 3. el tipo de intercambio a hacer al nodo en cuestión...

    private:
        void shiftX(NodoOrtogonal<T>*, NodoOrtogonal<T>*, int);
        void shiftY(NodoOrtogonal<T>*, NodoOrtogonal<T>*, int);
        void shiftZ(NodoOrtogonal<T>*, NodoOrtogonal<T>*, int);
        void shiftAround(NodoOrtogonal<T>*, int, int);//1. nodo, 2. tipoNodo, 3. tipoIntercambio
};

template <class T>//Recuerda que indicar que es una plantilla, debe colocarse en cada método, sea que solo exista un arch .cpp o que esté separado como este, y esto se hace porque debe indicarse especificamente a quine pertenece y en qué consiste, para que sepa cómo trabajar con él el compilador...
    void ShiftOrtogonal<T>::shiftNodes(NodoOrtogonal<T> *nodoFoco, NodoOrtogonal<T> *nodoIntercambio, int tipoShift){
        //cout<<"shiftNodes: "<<nodoFoco<<", ";
        //cout<<"shiftNodes "<<(*nodoFoco)<<endl;
        cout<<"shiftNodes "<<(nodoFoco)<<endl;
        //cout<<(&(*nodoFoco));

        switch(tipoShift){
            case 0: case 1:
                shiftX(nodoFoco, nodoIntercambio, tipoShift);
            break;
            case 2: case 3:
                shiftY(nodoFoco, nodoIntercambio, tipoShift);
            break;
            case 4: case 5:
                shiftZ(nodoFoco, nodoIntercambio, tipoShift);
            break;
        }

        shiftAround(nodoFoco, 1, tipoShift);//0-1 sX, 2-3 sY, 4-5 sZ
        shiftAround(nodoIntercambio, 2, tipoShift);//0-1 sX, 2-3 sY, 4-5 sZ
    }


template <class T>
    void ShiftOrtogonal<T>::shiftX(NodoOrtogonal<T> *nodoFoco, NodoOrtogonal<T>*nodoIntercambio, int tipoShiftX){//0 == izq, 1 == der
        NodoOrtogonal<T> *auxiliar = new NodoOrtogonal<T>();
        auxiliar->copiarNodo(nodoFoco);
        NodoOrtogonal<T> *auxiliarIntercambio = new NodoOrtogonal<T>();
        auxiliarIntercambio->copiarNodo(nodoIntercambio);

        //cout<<"shiftOrtogonal "<<(*nodoFoco)<<" ";
        cout<<"shiftOrtogonal "<<(nodoFoco)<<" ";
        cout<<nodoFoco<<endl;

        //bloques de actualizaciones del nodoFoco
        (nodoFoco)->setNodoSiguiente(((tipoShiftX==0)?(nodoIntercambio):(auxiliarIntercambio)->getSiguiente()));
        (nodoFoco)->setNodoAnterior(((tipoShiftX==0)?(auxiliarIntercambio)->getAnterior():(nodoIntercambio)));

        (nodoFoco)->setNodoArriba((auxiliarIntercambio)->getArriba());//puede seguir usándose el getAnterior o emplear el getSiguiente, puesto que ya se actualizó...
        (nodoFoco)->setNodoAbajo((auxiliarIntercambio)->getAbajo());
        (nodoFoco)->setNodoSaliente((auxiliarIntercambio)->getSaliente());
        (nodoFoco)->setNodoEntrante((auxiliarIntercambio)->getEntrante());

        //acualizaciones de ptro del nodoIntercambio
        (nodoIntercambio)->setNodoSiguiente(((tipoShiftX == 0)?(auxiliar->getSiguiente()):(nodoFoco)));//el seteo del nodo con el vacío movido debe ser con el nodo que tiene las ref de los ptros actualizadas... obvidamente xD
        (nodoIntercambio)->setNodoAnterior(((tipoShiftX == 0)?(nodoFoco):(auxiliar->getAnterior())));

        (nodoIntercambio)->setNodoArriba(auxiliar->getArriba());
        (nodoIntercambio)->setNodoAbajo(auxiliar->getAbajo());
        (nodoIntercambio)->setNodoSaliente(auxiliar->getSaliente());
        (nodoIntercambio)->setNodoEntrante(auxiliar->getEntrante());
    }

template <class T>
    void ShiftOrtogonal<T>::shiftY(NodoOrtogonal<T> *nodoFoco, NodoOrtogonal<T> *nodoIntercambio, int tipoShiftY){//2 == arriba, 3 == abajo
        NodoOrtogonal<T> *auxiliar = new NodoOrtogonal<T>();
        auxiliar->copiarNodo(nodoFoco);

        //bloques de actualizaciones del nodoFoco
        (nodoFoco)->setNodoAbajo(((tipoShiftY==2)?(nodoIntercambio):(nodoIntercambio)->getAbajo()));
        (nodoFoco)->setNodoArriba(((tipoShiftY==2)?(nodoIntercambio)->getArriba():(nodoIntercambio)));

        (nodoFoco)->setNodoSiguiente((nodoIntercambio)->getSiguiente());//puede seguir usándose el getAnterior o emplear el getSiguiente, puesto que ya se actualizó...
        (nodoFoco)->setNodoAnterior((nodoIntercambio)->getAnterior());
        (nodoFoco)->setNodoSaliente((nodoIntercambio)->getSaliente());
        (nodoFoco)->setNodoEntrante((nodoIntercambio)->getEntrante());

        //acualizaciones de ptro del nodoIntercambio
        (nodoIntercambio)->setNodoAbajo(((tipoShiftY == 2)?(auxiliar->getAbajo()):(nodoFoco)));//el seteo del nodo con el vacío movido debe ser con el nodo que tiene las ref de los ptros actualizadas... obvidamente xD
        (nodoIntercambio)->setNodoArriba(((tipoShiftY == 2)?(nodoFoco):(auxiliar->getArriba())));

        (nodoIntercambio)->setNodoSiguiente(auxiliar->getSiguiente());
        (nodoIntercambio)->setNodoAnterior(auxiliar->getAnterior());
        (nodoIntercambio)->setNodoSaliente(auxiliar->getSaliente());
        (nodoIntercambio)->setNodoEntrante(auxiliar->getEntrante());
    }

template <class T>
    void ShiftOrtogonal<T>::shiftZ(NodoOrtogonal<T> *nodoFoco, NodoOrtogonal<T> *nodoIntercambio, int tipoShiftZ){//4 = saliente (z1), 5 = entrante (z2)
        NodoOrtogonal<T> *auxiliar = new NodoOrtogonal<T>();
        auxiliar->copiarNodo(nodoFoco);

        //bloques de actualizaciones del nodoFoco
        (nodoFoco)->setNodoEntrante(((tipoShiftZ==4)?(nodoIntercambio):(nodoIntercambio)->getEntrante()));
        (nodoFoco)->setNodoSaliente(((tipoShiftZ==4)?(nodoIntercambio)->getSaliente():(nodoIntercambio)));

        (nodoFoco)->setNodoSiguiente((nodoIntercambio)->getSiguiente());//puede seguir usándose el getAnterior o emplear el getSiguiente, puesto que ya se actualizó...
        (nodoFoco)->setNodoAnterior((nodoIntercambio)->getAnterior());
        (nodoFoco)->setNodoArriba((nodoIntercambio)->getArriba());
        (nodoFoco)->setNodoAbajo((nodoIntercambio)->getAbajo());

        //acualizaciones de ptro del nodoIntercambio
        (nodoIntercambio)->setNodoEntrante(((tipoShiftZ == 4)?(auxiliar->getEntrante()):(nodoFoco)));//el seteo del nodo con el vacío movido debe ser con el nodo que tiene las ref de los ptros actualizadas... obvidamente xD
        (nodoIntercambio)->setNodoSaliente(((tipoShiftZ == 4)?(nodoFoco):(auxiliar->getSaliente())));

        (nodoIntercambio)->setNodoSiguiente(auxiliar->getSiguiente());
        (nodoIntercambio)->setNodoAnterior(auxiliar->getAnterior());
        (nodoIntercambio)->setNodoArriba(auxiliar->getArriba());
        (nodoIntercambio)->setNodoAbajo(auxiliar->getAbajo());
    }

template <class T>
    void ShiftOrtogonal<T>::shiftAround(NodoOrtogonal<T> *nodo, int tipoNodo, int tipoIntercambio){//los tipos de intercambio son iguales a los casos... | tipoNodo: 1 = nodoFoco, 2 = nodoIntercambio
        //reseteos de alrededores en X
        if((tipoIntercambio != 0 || tipoNodo != 2) && (tipoIntercambio != 1 || tipoNodo != 1)&& ((nodo)->getAnterior()!=NULL)){
            (nodo)->getAnterior()->setNodoSiguiente((nodo));
        }

        if((tipoIntercambio != 0 || tipoNodo != 1) && (tipoIntercambio != 1 || tipoNodo != 2) && ((nodo)->getSiguiente()!=NULL)){
            (nodo)->getSiguiente()->setNodoAnterior((nodo));
        }

        //reseteos de alrededores en Y
        if((tipoIntercambio != 2 || tipoNodo != 2) && (tipoIntercambio != 3 || tipoNodo != 1)&& ((nodo)->getArriba()!=NULL)){//TI2= arr, TI3 = ab; TN1 = nodoFoco, TN2 = nodoInter
            (nodo)->getArriba()->setNodoAbajo((nodo));
        }

        if((tipoIntercambio != 2 || tipoNodo != 1) && (tipoIntercambio != 3 || tipoNodo != 2) && ((nodo)->getAbajo()!=NULL)){
            (nodo)->getAbajo()->setNodoArriba((nodo));
        }

        //reseteos de alrededores en Z
        if((tipoIntercambio != 4 || tipoNodo != 2) && (tipoIntercambio != 5 || tipoNodo != 1)&& ((nodo)->getSaliente()!=NULL)){//TI4 = sal, TI5 = ent
            (nodo)->getSaliente()->setNodoEntrante((nodo));
        }

        if((tipoIntercambio != 4 || tipoNodo != 1) && (tipoIntercambio != 5 || tipoNodo != 2) && ((nodo)->getEntrante()!=NULL)){
            (nodo)->getEntrante()->setNodoSaliente((nodo));
        }
    }
#endif // SHIFT_H

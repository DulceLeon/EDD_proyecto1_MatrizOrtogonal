#ifndef SHIFT_H
#define SHIFT_H
#include <cstdlib>
#include <iostream>
#include "NodoOrtogonal.cpp"

using namespace std;


template <class T>
Class Shift{
    public:
        void shift(NodoOrtogonal<T>**, NodoOrtogonal<T>**, int);//el nodo en cuestión, el nodo de intercambio
        void shiftX(NodoOrtogonal<T>**, NodoOrtogonal<T>**, int);
        void shiftY(NodoOrtogonal<T>**, NodoOrtogonal<T>**, int);
        void shiftZ(NodoOrtogonal<T>**, NodoOrtogonal<T>**, int);
        void shiftAround(NodoOrtogonal<T>**, NodoOrtogonal<T>**, int);//1. nodoFoco, 2. nodoIntercambio, puesto que sin importar dónde se haya hecho el intercambio, esto se debe app a los dos involucrados en el shift, 3. el tipo puesto que dep de cómo estén ubicados en el espacio, algunos no se deberán establecer, en general el máximo de alrededores totales de esta pareja es de 10
};

template <class T>//Recuerda que indicar que es una plantilla, debe colocarse en cada método, sea que solo exista un arch .cpp o que esté separado como este, y esto se hace porque debe indicarse especificamente a quine pertenece y en qué consiste, para que sepa cómo trabajar con él el compilador...
    Shift<T>::shift(NodoOrtogonal<T> **nodoFoco, NodoOrtogonal<T>**nodoIntercambio, int tipoShift){
        switch(tipoShift){
            case 0: case 1:
                shiftX(*nodoFoco, *nodoIntercambio, tipoShift);
            break;
            case 2: case 3:
                shiftY(*nodoFoco, *nodoIntercambio, tipoShift);
            break;
            case 4: case 5:
                shiftZ(*nodoFoco, *nodoIntercambio, tipoShift);
            break;
        }

        shiftAround((*nodoFoco), (*nodoIntercambio), ((tipoShift <= 1)?1:((tipoShift <=3)?2:3)));//0-1 sX, 2-3 sY, 4-5 sZ
    }


template <class T>
    Shift<T>::shiftX(NodoOrtogonal<T> **nodoFoco, NodoOrtogonal<T>**nodoIntercambio, int tipoShiftX){
      template <class T>
    NodoOrtogonal<T>* MatrizOrtogonal<T>::shift(NodoOrtogonal<T> **nodoFoco,int ubicacionSustituto){//esta ubic es a la que se pasará el nodo vacío
        NodoOrtogonal<T> *auxiliar = new NodoOrtogonal<T>();
        auxiliar->copiarNodo(*nodoFoco);

        //bloques de actualizaciones del nodoFoco
        (*nodoFoco)->setNodoSiguiente(((tipoShiftX==0)?(*nodoIntercambio):(*nodoIntercambio)->getSiguiente());
        (*nodoFoco)->setNodoAnterior(((tipoShiftX==0)?(*nodoIntercambio)->getAnterior():(*nodoIntercambio));

        (*nodoFoco)->setNodoArriba((*nodoIntercambio)->getArriba());//puede seguir usándose el getAnterior o emplear el getSiguiente, puesto que ya se actualizó...
        (*nodoFoco)->setNodoAbajo((*nodoIntercambio)->getAbajo());
        (*nodoFoco)->setNodoSaliente((*nodoIntercambio)->getSaliente());
        (*nodoFoco)->setNodoEntrante((*nodoIntercambio)->getEntrante());

        //acualizaciones de ptro del nodoIntercambio
        (*nodoIntercambio)->setNodoSiguiente(((tipoShiftX == 0)?(auxiliar->getSiguiente()):(*nodoFoco)));
        (*nodoIntercambio)->setNodoAnterior((*nodoFoco));//debe ser este, pues ya tiene las referencias actuaalizadas a todos los punteros
        (*nodoIntercambio)->setNodoArriba(auxiliar->getArriba());
        (*nodoIntercambio)->setNodoAbajo(auxiliar->getAbajo());
        (*nodoIntercambio)->setNodoSaliente(auxiliar->getSaliente());
        (*nodoIntercambio)->setNodoEntrante(auxiliar->getEntrante());



    }

template <class T>
    Shift::shiftY(NodoOrtogonal<T> **nodoFoco, NodoOrtogonal<T> **nodoIntercambio, int tipoShiftY){
    break;
        case 2://haz los equivalentes xD, luego haz el método de búsuqeda, pero antes revisa si está bien esto, apurébalo y si puedes simplificarlo, hazlo, después de eso tendrías que hacer los métodos del tablero, para los diferentes tipos de entrada de datos [aletorio, pasas todo a string y cuando sea 0 lo vuelves x, por entrada user, especificarás que el cout recibirá strings e idnicarás que el signo de vacío es una x, y el otro recibirás puros strings, ya tienes el signo de vacío, después de eso debes exe le método para buscar el vacío [con T busqueda = "X", ojo que puse comillas xD, luego creas la matriz, muestras los datos, y con eso pasas a imple el algoritmo para... ah no ese ya lo tengo iba a decir el shift xD, entonces lo pruebas, luego ves lo demás y al terminar todo lo codificable miras lo del algoritmo de resolución a base de lo que te responda el inge...]]
            (*nodoFoco)->setNodoAbajo((*nodoFoco)->getArriba());
            (*nodoFoco)->setNodoAnterior((*nodoFoco)->getArriba()->getAnterior());
            (*nodoFoco)->setNodoSiguiente((*nodoFoco)->getArriba()->getSiguiente());//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...
            cout<<"siguiente nodoFoco: [afterReset] "<<(*nodoFoco)->getSiguiente();
            cout<<"siguiente auxiliar: [afterReset] "<<auxiliar->getSiguiente();
            (*nodoFoco)->setNodoSaliente((*nodoFoco)->getArriba()->getSaliente());
            (*nodoFoco)->setNodoEntrante((*nodoFoco)->getArriba()->getEntrante());

            (*nodoFoco)->setNodoArriba((*nodoFoco)->getArriba()->getArriba());//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...

            (*nodoFoco)->getAbajo()->setNodoSiguiente(auxiliar->getSiguiente());
            (*nodoFoco)->getAbajo()->setNodoAnterior(auxiliar->getAnterior());
            (*nodoFoco)->getAbajo()->setNodoArriba((*nodoFoco));
            (*nodoFoco)->getAbajo()->setNodoAbajo(auxiliar->getAbajo());
            cout<<"siguiente nodoFoco: [afterReset] "<<(*nodoFoco)->getAbajo();
            cout<<"siguiente auxiliar: [afterReset] "<<auxiliar->getAbajo();
            (*nodoFoco)->getAbajo()->setNodoSaliente(auxiliar->getSaliente());
            (*nodoFoco)->getAbajo()->setNodoEntrante(auxiliar->getEntrante());
            break;
        case 3://abajo: y2
            (*nodoFoco)->setNodoArriba((*nodoFoco)->getAbajo());//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...
            (*nodoFoco)->setNodoAnterior((*nodoFoco)->getAbajo()->getAnterior());
            (*nodoFoco)->setNodoSiguiente((*nodoFoco)->getAbajo()->getSiguiente());//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...
            cout<<"siguiente nodoFoco: [afterReset] "<<(*nodoFoco)->getSiguiente();
            cout<<"siguiente auxiliar: [afterReset] "<<auxiliar->getSiguiente();
            (*nodoFoco)->setNodoSaliente((*nodoFoco)->getAbajo()->getSaliente());
            (*nodoFoco)->setNodoEntrante((*nodoFoco)->getAbajo()->getEntrante());

            (*nodoFoco)->setNodoAbajo((*nodoFoco)->getAbajo()->getAbajo());

            (*nodoFoco)->getArriba()->setNodoSiguiente(auxiliar->getSiguiente());
            (*nodoFoco)->getArriba()->setNodoAnterior(auxiliar->getAnterior());
            (*nodoFoco)->getArriba()->setNodoArriba(auxiliar->getArriba());
            (*nodoFoco)->getArriba()->setNodoAbajo((*nodoFoco));
            (*nodoFoco)->getArriba()->setNodoSaliente(auxiliar->getSaliente());
            (*nodoFoco)->getArriba()->setNodoEntrante(auxiliar->getEntrante());
            break;
        case 4://saliente: z1
            (*nodoFoco)->setNodoEntrante((*nodoFoco)->getSaliente());
            (*nodoFoco)->setNodoAnterior((*nodoFoco)->getSaliente()->getAnterior());
            (*nodoFoco)->setNodoSiguiente((*nodoFoco)->getSaliente()->getSiguiente());//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...
            cout<<"siguiente nodoFoco: [afterReset] "<<(*nodoFoco)->getSiguiente();
            cout<<"siguiente auxiliar: [afterReset] "<<auxiliar->getSiguiente();
            (*nodoFoco)->setNodoArriba((*nodoFoco)->getSaliente()->getArriba());//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...
            (*nodoFoco)->setNodoAbajo((*nodoFoco)->getSaliente()->getAbajo());

            (*nodoFoco)->setNodoSaliente((*nodoFoco)->getSaliente()->getSaliente());

            (*nodoFoco)->getEntrante()->setNodoSiguiente(auxiliar->getSiguiente());
            (*nodoFoco)->getEntrante()->setNodoAnterior(auxiliar->getAnterior());
            (*nodoFoco)->getEntrante()->setNodoArriba(auxiliar->getArriba());
            (*nodoFoco)->getEntrante()->setNodoAbajo(auxiliar->getAbajo());
            (*nodoFoco)->getEntrante()->setNodoSaliente((*nodoFoco));
            (*nodoFoco)->getEntrante()->setNodoEntrante(auxiliar->getEntrante());
            break;
        case 5://entrante: z2
            (*nodoFoco)->setNodoSaliente((*nodoFoco)->getEntrante());
            (*nodoFoco)->setNodoAnterior((*nodoFoco)->getEntrante()->getAnterior());
            (*nodoFoco)->setNodoSiguiente((*nodoFoco)->getEntrante()->getSiguiente());//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...
            cout<<"siguiente nodoFoco: [afterReset] "<<(*nodoFoco)->getSiguiente();
            cout<<"siguiente auxiliar: [afterReset] "<<auxiliar->getSiguiente();
            (*nodoFoco)->setNodoArriba((*nodoFoco)->getEntrante()->getArriba());//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...
            (*nodoFoco)->setNodoAbajo((*nodoFoco)->getEntrante()->getAbajo());

            (*nodoFoco)->setNodoEntrante((*nodoFoco)->getEntrante()->getEntrante());

            (*nodoFoco)->getSaliente()->setNodoSiguiente(auxiliar->getSiguiente());
            (*nodoFoco)->getSaliente()->setNodoAnterior(auxiliar->getAnterior());
            (*nodoFoco)->getSaliente()->setNodoArriba(auxiliar->getArriba());
            (*nodoFoco)->getSaliente()->setNodoAbajo(auxiliar->getAbajo());
            (*nodoFoco)->getSaliente()->setNodoSaliente(auxiliar->getSaliente());
            (*nodoFoco)->getSaliente()->setNodoEntrante((*nodoFoco));
            break;
        default://aunque en realidad de no ingresar un dato correcto el usuario, se solicitará que ingrese de nuevo xD, así que no hay pena xD
            cout<<"direccion inexistente";
            break;
        }
        return *nodoFoco;
    }

template <class T>
    Shift::shiftZ(NodoOrtogonal<T> **nodoFoco, NodoOrtogonal<T> **nodoIntercambio, int tipoShiftZ){

    }

template <class T>
    Shift::shiftAround(NodoOrtogonal<T> **nodoFoco, NodoOrtogonal<T> **nodoIntercambio, int tipoIntercambio){//> 1, != shiftX, 2. != shiftY, 3. != shiftZ
        //establecimiento de los alrededores del nodoFoco
        if(tipoIntercambio > 1 && (*nodoFoco)->getAnterior()!=NULL){


        }

        //establecimiento de los alrededores del nodoIntercambio
    }

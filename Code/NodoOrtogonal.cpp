//recuerda que para las clases genéricas, es recomndable tenerlo todo en un solo archivo, es decir no separar el archivo de cabecera.h para definar la interfaz y tener otro para la implentación .cpp, sino tener ambas secciones en el archivo.cpp
#ifndef NODOORTOGONAL_H
#define NODOORTOGONAL_H
#include <cstdlib>
#include <iostream>

using namespace std;

template <class T>//forma equivalente de crear una clase genérica a la de Java
class NodoOrtogonal {
    private:
    //pongo el *puesto que debe poder hacer referencia a un obj creado almacenado en él...        
        NodoOrtogonal<T>* x1;//ant [izq]
        NodoOrtogonal<T>* x2;//sig [der]
        NodoOrtogonal<T>* y1;//arr
        NodoOrtogonal<T>* y2;//aba
        NodoOrtogonal<T>* z1;//saliendo
        NodoOrtogonal<T>* z2;//entrando
        T* contenido;

    public://se declaran los prototipos de las funciones, métodos normales y cnstrcs xD        
        NodoOrtogonal();//para inicializar el primer nodo, de cada fila y creo que tb matriz...
        NodoOrtogonal(NodoOrtogonal<T>*);//x1        
        void setContenido(T*);        
        void setNodoAnterior(NodoOrtogonal<T>*);//x1
        void setNodoSiguiente(NodoOrtogonal<T>*);//x2
        void setNodoArriba(NodoOrtogonal<T>*);//y1
        void setNodoAbajo(NodoOrtogonal<T>*);//y2
        void setNodoSaliente(NodoOrtogonal<T>*);//z1 [arr]
        void setNodoEntrante(NodoOrtogonal<T>*);//z2 [aba]
        NodoOrtogonal<T>* getAnterior();//x1 [izq]
        NodoOrtogonal<T>* getSiguiente();
        NodoOrtogonal<T>* getArriba();//y1
        NodoOrtogonal<T>* getAbajo();
        NodoOrtogonal<T>* getSaliente();
        NodoOrtogonal<T>* getEntrante();//z2        
        T* getContenido();
       ~NodoOrtogonal();//Destructor       
};
    template <class T>//Recuerda que indicar que es una plantilla, debe colocarse en cada método, sea que solo exista un arch .cpp o que esté separado como este, y esto se hace porque debe indicarse especificamente a quine pertenece y en qué consiste, para que sepa cómo trabajar con él el compilador...
    NodoOrtogonal<T>::NodoOrtogonal()//recuerd que en las definiciones de los métodos sí debes colocar la clase a la cual pertenecen, sea que seencuentrene en el mismo archivo de las "declaraciones" o no
    {        
        //ahorita veremos que cosas debemos hacer null...
    }

    template <class T>//Recuerda que indicar que es una plantilla, debe colocarse en cada método, sea que solo exista un arch .cpp o que esté separado como este, y esto se hace porque debe indicarse especificamente a quine pertenece y en qué consiste, para que sepa cómo trabajar con él el compilador...
    NodoOrtogonal<T>::NodoOrtogonal(NodoOrtogonal<T> *anterior)//recuerd que en las definiciones de los métodos sí debes colocar la clase a la cual pertenecen, sea que seencuentrene en el mismo archivo de las "declaraciones" o no
    {        
        x1 = anterior;
    }    

    template <class T>
    void NodoOrtogonal<T>::setContenido(T* content){
        contenido = content;
    }

    template <class T>
    void NodoOrtogonal<T>::setNodoAnterior(NodoOrtogonal<T> *nodoX1){
        x1 = nodoX1;
    }

    template <class T>
    void NodoOrtogonal<T>::setNodoSiguiente(NodoOrtogonal<T> *nodoX2){
        x2 = nodoX2;
    }

    template <class T>
    void NodoOrtogonal<T>::setNodoArriba(NodoOrtogonal<T> *nodoY1){
        y1 = nodoY1;
    }

    template <class T>
    void NodoOrtogonal<T>::setNodoAbajo(NodoOrtogonal<T> *nodoY2){
        y2 = nodoY2;
    }

    template <class T>
    void NodoOrtogonal<T>::setNodoSaliente(NodoOrtogonal<T> *nodoZ1){//[^]
        z1 = nodoZ1;
    }

    template <class T>
    void NodoOrtogonal<T>::setNodoEntrante(NodoOrtogonal<T> *nodoZ2){ //[v]
        z2 = nodoZ2;
    }

    template <class T>
    NodoOrtogonal<T>* NodoOrtogonal<T>::getAnterior(){
        return x1;
    }

    template <class T>
    NodoOrtogonal<T>* NodoOrtogonal<T>::getSiguiente(){
        return x2;
    }

    template <class T>
    NodoOrtogonal<T>* NodoOrtogonal<T>::getArriba(){
        return y1;
    }
    template <class T>
    NodoOrtogonal<T>* NodoOrtogonal<T>::getAbajo(){
        return y2;
    }

    template <class T>
    NodoOrtogonal<T>* NodoOrtogonal<T>::getSaliente(){
        return z1;
    }

    template <class T>
    NodoOrtogonal<T>* NodoOrtogonal<T>::getEntrante(){
        return z2;
    }

    template <class T>
    T* NodoOrtogonal<T>::getContenido(){
        return contenido;
    }

    template <class T>
    NodoOrtogonal<T>::~NodoOrtogonal<T>(){//el destructor
        delete x1;
        delete x2:
        delete y1;
        delete y2;
        delete z1;
        delete z2;
        //no creo que de problemas si la lista está vacía :v xD
    }

#endif


//x1, x2, y1, y2, z1, z2
//por la forma en que pensaste esto solo deberás tener insertar adelante
//cnstrct1: () [puesto que decidí setear contenidos después, si vas a cb esto entonces recibirá content], 
//cnstrct2: (X1 [ant])
//cnstrct3: (X1, Y1 [arriba])
//setX2, setY2, setZ1, setZ2 [puesto que esto se establecerá después de tener a cada matriz ortogonal creada, a menos que cb de opinión y lo hagas en el mismo método con el que creas una matriz [practicamente bidimensional...]]
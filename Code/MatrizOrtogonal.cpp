//métodos
//crearMatriz2D [primera parte, retorna la instancia que creó]
//crearMatriz3D [recibe todas las instancias que se creen en 2D, y hace el set de los Z respectivos y devuelve la primer matriz que recibió]
#ifndef MATRIZORTOGONAL_H
#define MATRIZORTOGONAL_H

#include <cstdlib>
#include <iostream>
#include <string>
#include "NodoOrtogonal.cpp"

using namespace std;

template <class T>
class MatrizOrtogonal{
    private: 
        NodoOrtogonal<T>* primerNodo;//del primer nivel
        NodoOrtogonal<T>* ultimoNodo;//del último nivel
        int ancho;//x's
        int alto;//y's
        int niveles;//#capas en z
        void borderExactly();

    public:        
        MatrizOrtogonal(int, int, int);//ancho, alto, #niveles        
        ~MatrizOrtogonal();

        MatrizOrtogonal<T>* crearMatriz2d();//add el asterisco, puesto que un objeto en realidad es un ptro        
        void crearMatriz3d();//no debe devolver nada puesto que este modificará directamente los atrib de esta clase...        
        void crearMatrizCompleta();
        void shift(NodoOrtogonal<T>*, string);//nodo con contenido X [por el contexto del juego], string-> tipo pteo: izq, der, arr, aba, sal, ent        
        void mostrarDatos();        
        void clean();
        
        int getAncho();
        int getAlto();
        int getNumeroNiveles();
        NodoOrtogonal<T>* getPrimerNodo();
        NodoOrtogonal<T>* getUltimoNodo();
};

    template <class T>
    MatrizOrtogonal<T>::MatrizOrtogonal(int width, int height, int levels){
        this-> ancho = width;
        this-> alto = height;
        this-> niveles = levels;

        crearMatriz3d();
    }

    template <class T>
    void MatrizOrtogonal<T>::crearMatriz3d(){//recuerda, con estos métodos solo estás creando los nodos, a parte tendrás un método para add el contenido, a menos que cbes de opinión debido a favorecimiento
        //nivel1
        primerNodo = crearMatriz2d()->getPrimerNodo();
        NodoOrtogonal<T>* previousNode = primerNodo;//este nodo se utilizará para accedere a todo de la capa
        NodoOrtogonal<T>* laterNode;
        NodoOrtogonal<T>* actualPreviousRow;//con este se accederá a las filas
        NodoOrtogonal<T>* actualLaterRow;
        NodoOrtogonal<T>* actualPreviusNode;//con este se accderá a las columnas
        NodoOrtogonal<T>* actualLaterNode;
        
        int capaActual = 1;//lo inicializo en 1, para que no se entre al ciclo, en caso de que solo se req 1 capa...

        while(capaActual<niveles)
        {
            laterNode = crearMatriz2d()->getPrimerNodo();    

            actualPreviousRow = previousNode;
            actualLaterRow = laterNode;        

            do{//para recorrer cada fila
                actualPreviusNode = actualPreviousRow;
                actualLaterNode = actualLaterRow;

                do{
                    //se hace lo nec para establecer la 3er dimensión [de izq a der]
                    actualPreviusNode->setNodoEntrante(actualLaterNode);//se setea z2
                    actualLaterNode->setNodoSaliente(actualPreviusNode);//se setea z1

                    actualPreviusNode = actualPreviusNode->getSiguiente();
                    actualLaterNode = actualLaterNode->getSiguiente();
                }while(actualPreviusNode!=null);

                actualPreviousRow = nodoFilaActual->getAbajo();//para así ir a la siguiente fila...
                actualLaterRow = nodoFilaActual->getAbajo();//para así ir a la siguiente fila...
            }while(actualPreviousRow!=null);//con revisar uno basta por el hecho de tener =# de elementos

            previousNode = laterNode;//para obtener el primer nodo de la siguiente capa y así repetir el ciclo con él
            capaActual++;
        }
    }//NICE

    template <class T>
    MatrizOrtogonal<T>* MatrizOrtogonal<T>::crearMatriz2d(){
        int filasCreadas = 0;
        NodoOrtogonal<T>* actualRow;
        NodoOrtogonal<T>* previousRow = null;
        NodoOrtogonal<T>* actualNode;        

        do{//pues al menos habrán 2 filas
            actualRow = new NodoOrtogonal();//aquí se crea la primer columna
            actualNode = actualRow;

            for (int columnaActual = 0; columnaActual < ancho; columnaActual++)
            {
                if(previousRow != null){//nec que se exe == #cols [ancho]; otra forma de poner la condi es filasCreadas >0
                    previousRow->setNodoAbajo(actualNode);
                    actualNode->setNodoArriba(previousRow);

                    previousRow = previousRow->getSiguiente();
                }    

                if(columnaActual < (ancho-1)){//pues se deben crear las c-1 cols restantes
                    NodoOrtogonal<T>* siguiente = new NodoOrtogonal(actualNode);//se cre el sig, se setea el ant del sig
                    actualNode->setNodoSiguiente(siguiente);                

                    actualNode = actualNode->getSiguiente();
                }                
            }            

            previousRow = actualRow;
            filasCreadas++;
        }while(filasCreadas < alto);
    }//NICE

    template <class T>
    void MatrizOrtogonal<T>::crearMatrizCompleta(){
        int capasCreadas = 0;
        primerNodo = new NodoOrtogonal();
        NodoOrtogonal<T>* actualLayer = primerNodo;        
        NodoOrtogonal<T>* previousLayer = null;
        NodoOrtogonal<T>* previousRowLayer = null;
        NodoOrtogonal<T>* previousNodeLayer = null;
        int filasCreadas = 0;
        NodoOrtogonal<T>* actualRow = actualLayer;
        NodoOrtogonal<T>* actualNode = actualRow;       
        NodoOrtogonal<T>* previousRow = null;//no se nece tener un previousNOde, puesto que este se actualiza con los datos de la fila que era la actual xD, entonces no hay probllema porque al tener que insertar cols a una nueva columna, este estará en el inicio xD porque esa fila actual siempre se quedó apuntando al primero de sus nodos uwu xD, de todos modos ahí le echas otra revisadita xD xD         

        do{//do porque al menos habrá una capa
            do{//es un do pues al menos habrán 2 filas        
                for (int columnaActual = 0; columnaActual < ancho; columnaActual++){
                    if(previousRow != null){//nec que se exe == #cols [ancho]; otra forma de poner la condi es filasCreadas >0
                        previousRow->setNodoAbajo(actualNode);
                        actualNode->setNodoArriba(previousRow);

                        previousRow = previousRow->getSiguiente();
                    }    
                    if(capasCreadas>0){
                        previousNodeLayer->setNodoEntrante(actualNode);
                        actualNode->setNodoSaliente(previousNodeLayer);

                        previousNodeLayer = previousNodeLayer->getSiguiente();
                    }

                    if(columnaActual < (ancho-1)){//pues se deben crear las c-1 cols restantes
                        NodoOrtogonal<T>* siguiente = new NodoOrtogonal(actualNode);//se cre el sig, se setea el ant del sig
                        actualNode->setNodoSiguiente(siguiente);                

                        actualNode = actualNode->getSiguiente();
                    }                
                }            

                if(capasCreadas>0){
                    previousRowLayer = previousRowLayer->getAbajo();
                    previousNodeLayer = previousRowLayer;
                }                   

                previousRow = actualRow;
                actualRow = new NodoOrtogonal();//aquí se crea la primer columna
                actualNode = actualRow;
                filasCreadas++;
            }while(filasCreadas < alto);

            previousLayer = actualLayer;
            previousRowLayer = previousLayer;            
            previousNodeLayer = previousRowLayer;
            capasCreadas++;

            actualLayer = new NodoOrtogonal();
            actualRow = actualLayer;
            actualNode = actualRow;
        }while(capasCreadas < niveles);        
    }//NICE


    template <class T>
    void MatrizOrtogonal<T>::shift(NodoOrtogonal<T>* nodoFoco, string ubicacionSustituto){

    }

    template <class T>
    void MatrizOrtogonal<T>:: mostrarDatos(){        
        int capaActual = 0;//lo inicializo en 1, para que no se entre al ciclo, en caso de que solo se req 1 capa...
        NodoOrtogonal<T>* layer = primerNodo;//este nodo se utilizará para accedere a todo de la capa
        NodoOrtogonal<T>* row ;
        NodoOrtogonal<T>* node;//con este se accederá a las filas                        
        
        do{
            row = layer;
            node = row;
            cout<<"Nivel "<<(capaActual+1)<<"\n";
            borderExactly();

            do{//para recorrer cada fila            
                borderExactly();
                do{
                    //se hace lo nec para establecer la 3er dimensión [de izq a der]                    
                    cout<<"|  "<<node->getContenido();
                    node = node->getSiguiente();
                }while(node!=null);//podríamos colocar que se detenga cuando siguiente sea == null, así al salir se podrá imprimir la útlima fila con | al ini y al final xD

                borderExactly();
                row = row->getAbajo();
                node = row;
            }while(row!=null);//con revisar uno basta por el hecho de tener =# de elementos
            
            borderExactly();
            cout<<"\n";
            layer = layer->getEntrante();//[v]            
            capaActual++;
        }while(capaActual<niveles);
    }//nice

    template <class T>
    void MatrizOrtogonal<T>::borderExactly(){
        for (int columnas = 0; columnas < ancho; columnas++)
        {
            cout<<"......."
        }
        cout<<"\n";        
    }

    template <class T>
    void MatrizOrtogonal<T>::clean(){

    }

    template <class T>
    int MatrizOrtogonal<T>::getAncho(){
        return ancho;
    }

    template <class T>
    int MatrizOrtogonal<T>::getAlto(){
        return alto;
    }

    template <class T>
    int MatrizOrtogonal<T>::getNumeroNiveles(){
        return niveles;
    }
    
    template <class T>
    NodoOrtogonal<T>* MatrizOrtogonal<T>::getPrimerNodo(){
        return primerNodo;
    }

    template <class T>
    NodoOrtogonal<T>* MatrizOrtogonal<T>::getUltimoNodo(){
        return ultimoNodo;        
    }
#endif
//Estaba pensando que después de crear cada mariz ortognonal con solo datos bidi, que se encarga de la dim 2D,
//retorne la matriz, para que ya en otro for, se pueda hacer el establecimiento de lo que hace falta y así
//éste método que se encargará de la 3er dimensión, solo tenga que devolver la primer matriz que recibió, puesto
//que esta tiene las referencias completas como para acceder a las demás 2dimensiiones, xD, de las demás matrices
//que no fueron acabadas en 2D
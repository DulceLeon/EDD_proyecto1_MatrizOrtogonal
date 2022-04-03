//métodos
//crearMatriz2D [primera parte, retorna la instancia que creó]
//crearMatriz3D [recibe todas las instancias que se creen en 2D, y hace el set de los Z respectivos y devuelve la primer matriz que recibió]
#ifndef MATRIZORTOGONAL_H
#define MATRIZORTOGONAL_H

#include <cstdlib>
#include <iostream>
#include <string>
#include "NodoOrtogonal.cpp"
#include "ShiftOrtogonal.cpp"

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
        NodoOrtogonal<T>* capaActual;
        NodoOrtogonal<T>* filaActual;
        NodoOrtogonal<T>* nodoActual;
        ShiftOrtogonal<T>* shiftOrtogonal;

    public:
        MatrizOrtogonal(int, int, int);//ancho, alto, #niveles
        MatrizOrtogonal<T>* crearMatriz2d();//add el asterisco, puesto que un objeto en realidad es un ptro
        void crearMatriz3d();//no debe devolver nada puesto que este modificará directamente los atrib de esta clase...
        void crearMatrizCompleta();
        void agregarContenido(T);
        NodoOrtogonal<T>* buscarNodo(T);
        NodoOrtogonal<T>* shift(NodoOrtogonal<T>*, int);//nodo con contenido X [por el contexto del juego], string-> tipo pteo: izq, der, arr, aba, sal, ent
        void mostrarDatos();
        void clean();

        int getAncho();
        int getAlto();
        int getNumeroNiveles();
        NodoOrtogonal<T>* getPrimerNodo();
        NodoOrtogonal<T>* getUltimoNodo();

        ~MatrizOrtogonal();

    private:
        void resetPrimerNodo(NodoOrtogonal<T>*, NodoOrtogonal<T>*);
        void resetUltimoNodo(NodoOrtogonal<T>*, NodoOrtogonal<T>*);
        bool resetFirstNode(NodoOrtogonal<T>*, NodoOrtogonal<T>*);
        bool resetLastNode(NodoOrtogonal<T>*, NodoOrtogonal<T>*);
};

    template <class T>
    MatrizOrtogonal<T>::MatrizOrtogonal(int width, int height, int levels){
        this-> ancho = width;
        this-> alto = height;
        this-> niveles = levels;//cuando ya funcione, simplificaremos esto asignando justo después de la delcaración de los parám...
        crearMatrizCompleta();//pero también podría invocarse a crearMatriz3d xD
        //con esto no habrá problema al momento de hacer set en el contenido
        this->nodoActual = this->filaActual = this-> capaActual = primerNodo;//this-> capaActual = primerNodo; this-> filaActual = capaActual; this-> nodoActual = filaActual;
        this->shiftOrtogonal = new ShiftOrtogonal<T>();
    }

    template <class T>
    void MatrizOrtogonal<T>::crearMatriz3d(){//recuerda, con estos métodos solo estás creando los nodos, a parte tendrás un método para add el contenido, a menos que cbes de opinión debido a favorecimiento
        int capaActual = 1;//lo inicializo en 1, para que no se entre al ciclo, en caso de que solo se req 1 capa...
        primerNodo = crearMatriz2d()->getPrimerNodo();
        NodoOrtogonal<T> *previousNode = primerNodo;//este nodo se utilizará para accedere a todo de la capa
        NodoOrtogonal<T> *actualPreviousRow, *actualPreviusNode;//con este se accderá a las columnas
        NodoOrtogonal<T> *laterNode, *actualLaterRow, *actualLaterNode;

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
                    actualPreviusNode->setNodoEntrante(actualLaterNode);//z2 [v]
                    actualLaterNode->setNodoSaliente(actualPreviusNode);//z1 [^]

                    actualPreviusNode = actualPreviusNode->getSiguiente();
                    actualLaterNode = actualLaterNode->getSiguiente();
                }while(actualPreviusNode!=NULL);

                actualPreviousRow = actualPreviousRow->getAbajo();//para así ir a la siguiente fila...
                actualLaterRow = actualLaterRow->getAbajo();//para así ir a la siguiente fila...
            }while(actualPreviousRow!=NULL);//con revisar uno basta por el hecho de tener =# de elementos

            previousNode = laterNode;//para obtener el primer nodo de la siguiente capa y así repetir el ciclo con él
            capaActual++;
        }
    }//NICE

    template <class T>
    MatrizOrtogonal<T>* MatrizOrtogonal<T>::crearMatriz2d(){
        int filasCreadas = 0;
        NodoOrtogonal<T> *actualRow, *actualNode;
        NodoOrtogonal<T> *previousRow = NULL;

        do{//pues al menos habrán 2 filas
            actualRow = new NodoOrtogonal<T>();//aquí se crea la primer columna
            actualNode = actualRow;

            for (int columnaActual = 0; columnaActual < ancho; columnaActual++)
            {
                if(previousRow != NULL){//nec que se exe == #cols [ancho]; otra forma de poner la condi es filasCreadas >0
                    previousRow->setNodoAbajo(actualNode);
                    actualNode->setNodoArriba(previousRow);

                    previousRow = previousRow->getSiguiente();
                }

                if(columnaActual < (ancho-1)){//pues se deben crear las c-1 cols restantes
                    NodoOrtogonal<T>* siguiente = new NodoOrtogonal<T>(actualNode);//se cre el sig, se setea el ant del sig
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
        primerNodo = new NodoOrtogonal<T>();
        cout<<"actual creado [1]: "<<primerNodo<<" ";
        NodoOrtogonal<T> *actualLayer = primerNodo;
        NodoOrtogonal<T> *previousLayer, *previousRowLayer, *previousNodeLayer;//estos son previos de la capa de arriba, es decir, están como superpuestos...
        int filasCreadas = 0;
        NodoOrtogonal<T> *actualRow = actualLayer;
        NodoOrtogonal<T> *actualNode = actualRow;
        NodoOrtogonal<T> *previousRow = NULL;//no se nece tener un previousNOde, puesto que este se actualiza con los datos de la fila que era la actual xD, entonces no hay probllema porque al tener que insertar cols a una nueva columna, este estará en el inicio xD porque esa fila actual siempre se quedó apuntando al primero de sus nodos uwu xD, de todos modos ahí le echas otra revisadita xD xD
        int numeroNodoCreado = 1;//este solo es para hacer pruebas

        do{//do porque al menos habrá una capa
            do{//es un do pues al menos habrán 2 filas
                for (int columnaActual = 0; columnaActual < ancho; columnaActual++){
                    if(previousRow != NULL){//nec que se exe == #cols [ancho]; otra forma de poner la condi es filasCreadas >0
                        previousRow->setNodoAbajo(actualNode);
                        actualNode->setNodoArriba(previousRow);
                        cout<<"set y's: [y1,y2] "<<(numeroNodoCreado)<<endl;

                        previousRow = previousRow->getSiguiente();
                    }
                    if(capasCreadas>0){
                        previousNodeLayer->setNodoEntrante(actualNode);//z2 [v]
                        actualNode->setNodoSaliente(previousNodeLayer);//z1 [^]
                        cout<<"set z's: [z1,z2] "<<(numeroNodoCreado)<<endl;

                        previousNodeLayer = previousNodeLayer->getSiguiente();
                    }

                    if(columnaActual < (ancho-1)){//pues se deben crear las c-1 cols restantes
                        //NodoOrtogonal<T>* siguiente = new NodoOrtogonal<T>(actualNode);//se cre el sig, se setea el ant del sig
                        NodoOrtogonal<T>* siguiente = new NodoOrtogonal<T>();
                        siguiente->setNodoAnterior(actualNode);
                        actualNode->setNodoSiguiente(siguiente);
                        cout<<"set x's: [x1,x2] "<<(numeroNodoCreado)<<endl;

                        actualNode = actualNode->getSiguiente();
                        cout<<"nodo anterior: "<<actualNode->getAnterior()<<endl;
                        cout<<"actual = sig ["<<(++numeroNodoCreado)<<"]"<<endl;//se empezará a mostrar en el 2, por el nodo que se crea desde el inicio
                        cout<<"actual creado: "<<actualNode<<" ";
                    }
                }
                if(capasCreadas>0){
                    previousRowLayer = previousRowLayer->getAbajo();
                    previousNodeLayer = previousRowLayer;
                }//con esta condición, se hacen null cuando el número de filas se ha alcanzado...

                filasCreadas++;
                if(filasCreadas<alto){
                    previousRow = actualRow;//cuando se alance el #filas solicitadas, este seguirá siendo NULL, por el get que hizo una col más allá de las existentes
                    actualRow = new NodoOrtogonal<T>();//aquí se crea la primer columna
                    actualNode = actualRow;

                    cout<<"Nodo creado: "<<(++numeroNodoCreado)<<" sig fila ["<<filasCreadas<<"]"<<endl;//se empezará a mostrar en el 2, por el nodo que se crea desde el inicio
                }
            }while(filasCreadas < alto);

            capasCreadas++;
            if(capasCreadas < niveles){
                previousNodeLayer = previousRowLayer = previousLayer = actualLayer;//previousLayer = actualLayer; previousRowLayer = previousLayer;  previousNodeLayer = previousRowLayer;
                actualLayer = new NodoOrtogonal<T>();
                actualNode = actualRow = actualLayer;//actualNode = actualRow;
                filasCreadas = 0;//puesto que sino no se avisará que las filas a crear son de la nueva capa xD

                cout<<"Nodo creado: "<<(++numeroNodoCreado)<<" sig capa ["<<capasCreadas<<"]"<<endl;//se empezará a mostrar en el 2, por el nodo que se crea desde el inicio
            }
        }while(capasCreadas < niveles);

        ultimoNodo = actualNode;//puesto que ese es el que tiene la  isntancia del último nodo creado...
    }//NICE

    template <class T>
    void MatrizOrtogonal<T>::agregarContenido(T contenido){
        if(capaActual != NULL || filaActual != NULL || nodoActual != NULL){//yo diría que con la condición que capa != null es más que suficiente... puesto que va a ser null cuando el de la fila y el nodo, sean null
            //cout<<"nodoActual: "<<this->nodoActual<<" ";
            this->nodoActual->setContenido(contenido);//se establece el contenido
            //cout<<"SC: set content";
            nodoActual = nodoActual->getSiguiente();//se actualiza el nodo al que debe addse el contenido
            //cout<<"SC: actual = next()";
            //cout<<"nodoA == null? "<<(nodoActual == NULL)<<endl;

            if(nodoActual == NULL){//se acabaron las col
               // cout<<"se acabaron las columnas";
                filaActual = filaActual->getAbajo();
               // cout<<"SC: next row [abajo()]";

                if(filaActual != NULL){
                    nodoActual = filaActual;
                //    cout<<"SC: update first ROW node";
                }else{//Se acabaron las filas
                //    cout<<"se acabaron las filas";
                    capaActual = capaActual->getEntrante();
                //    cout<<"SC: next layer [into()]";

                    if(capaActual != NULL){//aun hay capas
                        filaActual = capaActual;
                        nodoActual = filaActual;
                //        cout<<"SC: update first LAYER node";
                    }//no pongo un else, puesto que no hay alguien más a quien buscar para que deje de ser NULL, media vez se hace NULL no hay nada más por hacer xD, porque este es el nodo determinante...
                }
            }
            cout<<endl;
        }
        //cout<<"fin add elemento\n";
    }//cuando todos lleguen a null quiere decir que está llena, entonces no tendrían por qué hacer que dejen de ser null...

    template <class T>
    NodoOrtogonal<T>* MatrizOrtogonal<T>::buscarNodo(T criterioBusqueda){//deprecated, al menos para este porque los strings DEBEN compararse con cmpstring xD
        int capaActual = 0;//lo inicializo en 1, para que no se entre al ciclo, en caso de que solo se req 1 capa...
        NodoOrtogonal<T> *layer = primerNodo;//este nodo se utilizará para accedere a todo de la capa
        NodoOrtogonal<T> *row, *node;//con este se accederá a las filas

        do{
            node = row = layer;//row = layer; node = row;
            do{//para recorrer cada fila
                do{//para recorrer cada columna
                    if(node->getContenido() == criterioBusqueda){//yo pensaría que aquí no se comparan las direcciones...
                        cout<<"compracion [busqueda nodo]: contenido nodo-> "<<node->getContenido()<<"criterio búsqueda-> "<<criterioBusqueda;
                        return node;
                    }
                    node = node->getSiguiente();
                }while(node!=NULL);//podríamos colocar que se detenga cuando siguiente sea == NULL, así al salir se podrá imprimir la útlima fila con | al ini y al final xD

                row = row->getAbajo();
                node = row;
            }while(row!=NULL);//con revisar uno basta por el hecho de tener =# de elementos

            layer = layer->getEntrante();//[v]
            capaActual++;
        }while(capaActual<niveles);

        return NULL;//si es que no encuentra algo
    }

    template <class T>
    NodoOrtogonal<T>* MatrizOrtogonal<T>::shift(NodoOrtogonal<T> *nodoFoco, int ubicacionSustituto){//esta ubic es a la que se pasará el nodo vacío
        //cout<<"MatrizOrto"<<nodoFoco<< " =? "<<&(*nodoFoco);

        switch (ubicacionSustituto){
            case 0://izq: x1
                this->resetPrimerNodo(nodoFoco,((nodoFoco)->getAnterior()));
                this->shiftOrtogonal->shiftNodes((nodoFoco), ((nodoFoco)->getAnterior()), ubicacionSustituto);
            break;
            case 1://Der: x2
                this->resetPrimerNodo(nodoFoco,((nodoFoco)->getSiguiente()));
                this->shiftOrtogonal->shiftNodes(nodoFoco, (nodoFoco)->getSiguiente(), ubicacionSustituto);
            break;
            case 2://haz los equivalentes xD, luego haz el método de búsuqeda, pero antes revisa si está bien esto, apurébalo y si puedes simplificarlo, hazlo, después de eso tendrías que hacer los métodos del tablero, para los diferentes tipos de entrada de datos [aletorio, pasas todo a string y cuando sea 0 lo vuelves x, por entrada user, especificarás que el cout recibirá strings e idnicarás que el signo de vacío es una x, y el otro recibirás puros strings, ya tienes el signo de vacío, después de eso debes exe le método para buscar el vacío [con T busqueda = "X", ojo que puse comillas xD, luego creas la matriz, muestras los datos, y con eso pasas a imple el algoritmo para... ah no ese ya lo tengo iba a decir el shift xD, entonces lo pruebas, luego ves lo demás y al terminar todo lo codificable miras lo del algoritmo de resolución a base de lo que te responda el inge...]]
                this->resetPrimerNodo(nodoFoco,((nodoFoco)->getArriba()));
                this->shiftOrtogonal->shiftNodes(nodoFoco, (nodoFoco)->getArriba(), ubicacionSustituto);
            break;
            case 3://abajo: y2
                this->resetPrimerNodo(nodoFoco,((nodoFoco)->getAbajo()));
                this->shiftOrtogonal->shiftNodes(nodoFoco, (nodoFoco)->getAbajo(), ubicacionSustituto);
            break;
            case 4://saliente: z1
                this->resetPrimerNodo(nodoFoco,((nodoFoco)->getSaliente()));
                this->shiftOrtogonal->shiftNodes(nodoFoco, (nodoFoco)->getSaliente(), ubicacionSustituto);
            break;
            case 5://entrante: z2
                this->resetPrimerNodo(nodoFoco,((nodoFoco)->getEntrante()));
                this->shiftOrtogonal->shiftNodes(nodoFoco, (nodoFoco)->getEntrante(), ubicacionSustituto);
            break;
            default://aunque en realidad de no ingresar un dato correcto el usuario, se solicitará que ingrese de nuevo xD, así que no hay pena xD
                cout<<"direccion inexistente";
            break;
        }
        return nodoFoco;
    }//Listo xD, en caso no funcione, fue por una confusión no por la lógica xD

    template <class T>
    void MatrizOrtogonal<T>::mostrarDatos(){
        int capaActual = 0;//lo inicializo en 1, para que no se entre al ciclo, en caso de que solo se req 1 capa...
        NodoOrtogonal<T> *layer = primerNodo;//este nodo se utilizará para accedere a todo de la capa
        NodoOrtogonal<T> *row, *node;//con este se accederá a las filas

        do{
            node = row = layer;//row = layer; node = row;
            cout<<"Nivel "<<(capaActual+1)<<"\n"<<endl;
            do{//para recorrer cada fila

                do{
                    cout<<"|  "<<node->getContenido()<<"  ";
                    node = node->getSiguiente();
                }while(node!=NULL);//podríamos colocar que se detenga cuando siguiente sea == NULL, así al salir se podrá imprimir la útlima fila con | al ini y al final xD

                cout<<"|"<<endl;

                row = row->getAbajo();
                node = row;
            }while(row!=NULL);//con revisar uno basta por el hecho de tener =# de elementos

            cout<<"\n";
            layer = layer->getEntrante();//[v]
            capaActual++;
        }while(capaActual<niveles);
    }//nice

    template <class T>
    void MatrizOrtogonal<T>::borderExactly(){
        for (int columnas = 0; columnas < ancho; columnas++){
            cout<<".......";
        }
        cout<<"\n";
    }

    template <class T>
    void MatrizOrtogonal<T>::clean(){
        int capaActual = 0;//lo inicializo en 1, para que no se entre al ciclo, en caso de que solo se req 1 capa...
        NodoOrtogonal<T> *layer = primerNodo;//este nodo se utilizará para accedere a todo de la capa
        NodoOrtogonal<T> *row, *node;//con este se accederá a las filas

        do{
            node = row = layer;//row = layer; node = row;
            layer = layer->getEntrante();//para que no se pierda la referencia al nivel que toca, para iniciar todo desde 0, y trabajar de forma similar a como se hizo en el primer nivel...

            do{//para recorrer cada fila
                row = row->getAbajo();
                do{//para recorrer cada columna
                    NodoOrtogonal<T>* auxiliar = node->getSiguiente();
                    node->~NodoOrtogonal();
                    delete node;//al exe esto, se exe automáticamente el destructor de node? yo diría que si xD, pero si no da error, probaremos invocarlo manuualmente xD
                    node = auxiliar;
                }while(node!=NULL);//podríamos colocar que se detenga cuando siguiente sea == NULL, así al salir se podrá imprimir la útlima fila con | al ini y al final xD

                node = row;
            }while(row!=NULL);//con revisar uno basta por el hecho de tener =# de elementos

            capaActual++;
        }while(capaActual<niveles);
    }//solo que cambia un poquito...

    template <class T>
    void MatrizOrtogonal<T>::resetPrimerNodo(NodoOrtogonal<T>* nodo1, NodoOrtogonal<T>* nodo2){
        if(!this->resetFirstNode(nodo1, nodo2)){
            this->resetFirstNode(nodo2, nodo1);
        }
    }

    template <class T>
    void MatrizOrtogonal<T>::resetUltimoNodo(NodoOrtogonal<T>* nodo1, NodoOrtogonal<T>* nodo2){//este no es obligatorio utilizarlo puesto que el ultimo nodo solo se pide 1 vez en el juego, es decir cuando no se tiene aún el ptro a él para así saber dónde se encuentra el Blank xD
        if(!this->resetLastNode(nodo1, nodo2)){
            this->resetLastNode(nodo2, nodo1);
        }
    }

    template <class T>
    bool MatrizOrtogonal<T>::resetFirstNode(NodoOrtogonal<T>* posibleOldFirst, NodoOrtogonal<T>* posibleNewFirst){
        if(posibleOldFirst == primerNodo){
            primerNodo = posibleNewFirst;//hago esto específicamente por el shift
            return true;
        }
        return false;
    }

    template <class T>
    bool MatrizOrtogonal<T>::resetLastNode(NodoOrtogonal<T>* posibleOldLast, NodoOrtogonal<T>* posibleNewLast){
        if(posibleOldLast == primerNodo){
            primerNodo = posibleNewLast;//hago esto específicamente por el shift
            return true;
        }
        return false;
    }

    template <class T>
    int MatrizOrtogonal<T>::getAncho(){return ancho;}
    template <class T>
    int MatrizOrtogonal<T>::getAlto(){return alto;}
    template <class T>
    int MatrizOrtogonal<T>::getNumeroNiveles(){return niveles;}
    template <class T>
    NodoOrtogonal<T>* MatrizOrtogonal<T>::getPrimerNodo(){return primerNodo;}
    template <class T>
    NodoOrtogonal<T>* MatrizOrtogonal<T>::getUltimoNodo(){return ultimoNodo;}
    template <class T>
    MatrizOrtogonal<T>::~MatrizOrtogonal(){clean();}
#endif
//Estaba pensando que después de crear cada mariz ortognonal con solo datos bidi, que se encarga de la dim 2D,
//retorne la matriz, para que ya en otro for, se pueda hacer el establecimiento de lo que hace falta y así
//éste método que se encargará de la 3er dimensión, solo tenga que devolver la primer matriz que recibió, puesto
//que esta tiene las referencias completas como para acceder a las demás 2dimensiiones, xD, de las demás matrices
//que no fueron acabadas en 2D

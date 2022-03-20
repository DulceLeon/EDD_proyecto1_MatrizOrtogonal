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
        NodoOrtogonal<T>* capaActual;
        NodoOrtogonal<T>* filaActual;
        NodoOrtogonal<T>* nodoActual;

    public:        
        MatrizOrtogonal(int, int, int);//ancho, alto, #niveles        
        ~MatrizOrtogonal();

        MatrizOrtogonal<T>* crearMatriz2d();//add el asterisco, puesto que un objeto en realidad es un ptro        
        void crearMatriz3d();//no debe devolver nada puesto que este modificará directamente los atrib de esta clase...        
        void crearMatrizCompleta();
        void agregarContenido(T*);
        NodoOrtogonal<T>* buscarNodo(T*);
        NodoOrtogonal<T>* shift(NodoOrtogonal<T>*, string);//nodo con contenido X [por el contexto del juego], string-> tipo pteo: izq, der, arr, aba, sal, ent        
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

        //con esto no habrá problema al momento de hacer set en el contenido
        this-> capaActual = primerNodo;
        this-> filaActual = capaActual;
        this-> nodoActual = filaActual;
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
                    actualPreviusNode->setNodoEntrante(actualLaterNode);//z2 [v]
                    actualLaterNode->setNodoSaliente(actualPreviusNode);//z1 [^]

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
                        previousNodeLayer->setNodoEntrante(actualNode);//z2 [v]
                        actualNode->setNodoSaliente(previousNodeLayer);//z1 [^]

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
    void MatrizOrtogonal<T>::agregarContenido(T* contenido){
        if(capaActual != null || filaActual != null || nodoActual != null){
            this-> nodoActual->setContenido(contenido);//se establece el contenido
            
            nodoActual = nodoActual->getSiguiente();//se actualiza el nodo al que debe addse el contenido
            if(nodoActual == null){//se acabaron las col
                filaActual = filaActual->getAbajo();

                if(filaActual != null){
                    nodoActual = filaActual;                    
                }else{//Se acabaron las filas
                    capaActual = capaActual->getEntrante();
                    if(capaActual != null){//aun hay capas
                        filaActual = capaActual;
                        nodoActual = filaActual;
                    }//no pongo un else, puesto que no hay alguien más a quien buscar para que deje de ser null, media vez se hace null no hay nada más por hacer xD, porque este es el nodo determinante...
                }
            }
        }
    }

    template <class T>
    NodoOrtogonal<T>* MatrizOrtogonal<T>::buscarNodo(T* criterioBusqueda){
        int capaActual = 0;//lo inicializo en 1, para que no se entre al ciclo, en caso de que solo se req 1 capa...
        NodoOrtogonal<T>* layer = primerNodo;//este nodo se utilizará para accedere a todo de la capa
        NodoOrtogonal<T>* row;
        NodoOrtogonal<T>* node;//con este se accederá a las filas                        
        
        do{
            row = layer;
            node = row;
            do{//para recorrer cada fila                            
                do{//para recorrer cada columna
                    if(node->getContenido() == criterioBusqueda){//según busqué, si se puede comaparar strings con ==...
                        return node;
                    }
                    node = node->getSiguiente();
                }while(node!=null);//podríamos colocar que se detenga cuando siguiente sea == null, así al salir se podrá imprimir la útlima fila con | al ini y al final xD

                row = row->getAbajo();
                node = row;
            }while(row!=null);//con revisar uno basta por el hecho de tener =# de elementos
            
            layer = layer->getEntrante();//[v]            
            capaActual++;
        }while(capaActual<niveles);
    }

    template <class T>
    NodoOrtogonal<T>* MatrizOrtogonal<T>::shift(NodoOrtogonal<T>* nodoFoco, string ubicacionSustituto){//esta ubic es a la que se pasará el nodo vacío
        NodoOrtogonal<T>* auxiliar = nodoFoco;
        
        switch (ubicacionSustituto){
        case "izquierda":            
            nodoFoco->setNodoSiguiente(nodoFoco->getAnterior());
            nodoFoco->setNodoArriba(nodoFoco->getAnterior()->getArriba());//puede seguir usándose el getAnterior o emplear el getSiguiente, puesto que ya se actualizó...
            nodoFoco->setNodoAbajo(nodoFoco->getAnterior()->getAbajo());
            nodoFoco->setNodoSaliente(nodoFoco->getAnterior()->getSaliente());
            nodoFoco->setNodoEntrante(nodoFoco->getAnterior()->getEntrante());      

            //lo separo puesto que aquí es donde se pierde toda realción antigua xD, aunque en realidad no es nec, porque a partir del seteo del opuesto, puedo seguir obteniendo los datos, así como da a entener las notas de "puede seguir usándose..."
            nodoFoco->setNodoAnterior(nodoFoco->getAnterior()->getAnterior());//puede seguir usándose el getAnterior o emplear el getSiguiente, puesto que ya se actualizó...

            nodoFoco->getSiguiente()->setNodoSiguiente(auxiliar->getSiguiente());
            nodoFoco->getSiguiente()->setNodoAnterior(nodoFoco);//debe ser este, pues ya tiene las referencias actuaalizadas a todos los punteros
            nodoFoco->getSiguiente()->setNodoArriba(auxiliar->getArriba());
            nodoFoco->getSiguiente()->setNodoAbajo(auxiliar->getAbajo());
            nodoFoco->getSiguiente()->setNodoSaliente(auxiliar->getSaliente());
            nodoFoco->getSiguiente()->setNodoEntrante(auxiliar->getEntrante());
            break;
        case "derecha":
            nodoFoco->setNodoAnterior(nodoFoco->getSiguiente());
            nodoFoco->setNodoArriba(nodoFoco->getSiguiente()->getArriba());//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...
            nodoFoco->setNodoAbajo(nodoFoco->getSiguiente()->getAbajo());
            nodoFoco->setNodoSaliente(nodoFoco->getSiguiente()->getSaliente());
            nodoFoco->setNodoEntrante(nodoFoco->getSiguiente()->getEntrante());           

            nodoFoco->setNodoSiguiente(nodoFoco->getSiguiente()->getSiguiente());//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...            

            nodoFoco->getAnterior()->setNodoSiguiente(nodoFoco);
            nodoFoco->getAnterior()->setNodoAnterior(auxiliar->getAnterior());
            nodoFoco->getAnterior()->setNodoArriba(auxiliar->getArriba());
            nodoFoco->getAnterior()->setNodoAbajo(auxiliar->getAbajo());
            nodoFoco->getAnterior()->setNodoSaliente(auxiliar->getSaliente());
            nodoFoco->getAnterior()->setNodoEntrante(auxiliar->getEntrante());
            break;
        case "arriba"://haz los equivalentes xD, luego haz el método de búsuqeda, pero antes revisa si está bien esto, apurébalo y si puedes simplificarlo, hazlo, después de eso tendrías que hacer los métodos del tablero, para los diferentes tipos de entrada de datos [aletorio, pasas todo a string y cuando sea 0 lo vuelves x, por entrada user, especificarás que el cout recibirá strings e idnicarás que el signo de vacío es una x, y el otro recibirás puros strings, ya tienes el signo de vacío, después de eso debes exe le método para buscar el vacío [con T busqueda = "X", ojo que puse comillas xD, luego creas la matriz, muestras los datos, y con eso pasas a imple el algoritmo para... ah no ese ya lo tengo iba a decir el shift xD, entonces lo pruebas, luego ves lo demás y al terminar todo lo codificable miras lo del algoritmo de resolución a base de lo que te responda el inge...]]
            nodoFoco->setNodoAbajo(nodoFoco->getArriba());
            nodoFoco->setNodoAnterior(nodoFoco->getArriba()->getAnterior);
            nodoFoco->setNodoSiguiente(nodoFoco->getArriba()->getSiguiente());//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...                        
            nodoFoco->setNodoSaliente(nodoFoco->getArriba()->getSaliente());
            nodoFoco->setNodoEntrante(nodoFoco->getArriba()->getEntrante());

            nodoFoco->setNodoArriba(nodoFoco->getArriba()->getArriba());//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...

            nodoFoco->getAbajo()->setNodoSiguiente(auxiliar->getSiguiente());
            nodoFoco->getAbajo()->setNodoAnterior(auxiliar->getAnterior());
            nodoFoco->getAbajo()->setNodoArriba(nodoFoco);
            nodoFoco->getAbajo()->setNodoAbajo(auxiliar->getAbajo());
            nodoFoco->getAbajo()->setNodoSaliente(auxiliar->getSaliente());
            nodoFoco->getAbajo()->setNodoEntrante(auxiliar->getEntrante());
            break;
        case "abajo":
            nodoFoco->setNodoArriba(nodoFoco->getAbajo());//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...            
            nodoFoco->setNodoAnterior(nodoFoco->getAbajo()->getAnterior);
            nodoFoco->setNodoSiguiente(nodoFoco->getAbajo()->getSiguiente());//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...                        
            nodoFoco->setNodoSaliente(nodoFoco->getAbajo()->getSaliente());
            nodoFoco->setNodoEntrante(nodoFoco->getAbajo()->getEntrante());

            nodoFoco->setNodoAbajo(nodoFoco->getAbajo()->getAbajo());

            nodoFoco->getArriba()->setNodoSiguiente(auxiliar->getSiguiente());
            nodoFoco->getArriba()->setNodoAnterior(auxiliar->getAnterior());
            nodoFoco->getArriba()->setNodoArriba(auxiliar->getArriba());
            nodoFoco->getArriba()->setNodoAbajo(nodoFoco);
            nodoFoco->getArriba()->setNodoSaliente(auxiliar->getSaliente());
            nodoFoco->getArriba()->setNodoEntrante(auxiliar->getEntrante());
            break;
        case "saliente"://z1
            nodoFoco->setNodoEntrante(nodoFoco->getSaliente());
            nodoFoco->setNodoAnterior(nodoFoco->getSaliente()->getAnterior);
            nodoFoco->setNodoSiguiente(nodoFoco->getSaliente()->getSiguiente());//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...                        
            nodoFoco->setNodoArriba(nodoFoco->getSaliente()->getArriba);//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...            
            nodoFoco->setNodoAbajo(nodoFoco->getSaliente()->getAbajo());

            nodoFoco->setNodoSaliente(nodoFoco->getSaliente()->getSaliente());

            nodoFoco->getEntrante()->setNodoSiguiente(auxiliar->getSiguiente());
            nodoFoco->getEntrante()->setNodoAnterior(auxiliar->getAnterior());
            nodoFoco->getEntrante()->setNodoArriba(auxiliar->getArriba());
            nodoFoco->getEntrante()->setNodoAbajo(auxiliar->getAbajo());
            nodoFoco->getEntrante()->setNodoSaliente(nodoFoco);
            nodoFoco->getEntrante()->setNodoEntrante(auxiliar->getEntrante());            
            break;
        case "entrante"://z2
            nodoFoco->setNodoSaliente(nodoFoco->getEntrante());            
            nodoFoco->setNodoAnterior(nodoFoco->getEntrante()->getAnterior);
            nodoFoco->setNodoSiguiente(nodoFoco->getEntrante()->getSiguiente());//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...                        
            nodoFoco->setNodoArriba(nodoFoco->getEntrante()->getArriba);//puede seguir usándose el getSig o emplear el getAnt, puesto que ya se actualizó...            
            nodoFoco->setNodoAbajo(nodoFoco->getEntrante()->getAbajo());

            nodoFoco->setNodoEntrante(nodoFoco->getEntrante()->getEntrante());

            nodoFoco->getSaliente()->setNodoSiguiente(auxiliar->getSiguiente());
            nodoFoco->getSaliente()->setNodoAnterior(auxiliar->getAnterior());
            nodoFoco->getSaliente()->setNodoArriba(auxiliar->getArriba());
            nodoFoco->getSaliente()->setNodoAbajo(auxiliar->getAbajo());
            nodoFoco->getSaliente()->setNodoSaliente(auxiliar->getSaliente());
            nodoFoco->getSaliente()->setNodoEntrante(nodoFoco); 
            break;        
        default://aunque en realidad de no ingresar un dato correcto el usuario, se solicitará que ingrese de nuevo xD, así que no hay pena xD            
        }

        return nodoFoco;//puesto que este es el nodo vacío con los puteros actualizados debido a los movimientos que se hizo... así no perderá la ref al nodo vacío, aunque ahora que lo pienso no es nec... :v xD
    }//Listo xD, en caso no funcione, fue por una confusión no por la lógica xD

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
        for (int columnas = 0; columnas < ancho; columnas++){
            cout<<"......."
        }
        cout<<"\n";        
    }

    template <class T>
    void MatrizOrtogonal<T>::clean(){

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
#endif
//Estaba pensando que después de crear cada mariz ortognonal con solo datos bidi, que se encarga de la dim 2D,
//retorne la matriz, para que ya en otro for, se pueda hacer el establecimiento de lo que hace falta y así
//éste método que se encargará de la 3er dimensión, solo tenga que devolver la primer matriz que recibió, puesto
//que esta tiene las referencias completas como para acceder a las demás 2dimensiiones, xD, de las demás matrices
//que no fueron acabadas en 2D
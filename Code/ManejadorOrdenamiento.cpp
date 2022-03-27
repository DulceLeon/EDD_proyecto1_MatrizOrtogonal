#include "ManejadorOrdenamiento.h"

using namespace std;

void ManejadorOrdenamiento::ordenarMatriz(MatrizOrtogonal<string>* matriz, string* simboloVacio){//este nodo lo obtendrá de tablero, puesto que éste es quien lo posee...
    this->matrizOrdenada = matriz;
    //con esto se procede  a poner hasta el final el nodo vacío, para así evitar tener posibles problemas debido al intento de convertir este a un número xD xD
    this->matrizOrdenada->buscarNodo(simboloVacio)->setContenido(this->matrizOrdenada->getUltimoNodo()->getContenido());//para así modificar de una vez el contenido al de la matriz que se va a ordenar xD xD    
    this->matrizOrdenada->getUltimoNodo()->setContenido(simboloVacio);
    
    NodoOrtogonal<string> *layer = this->matrizOrdenada->getPrimerNodo();//este nodo se utilizará para accedere a todo de la capa
    NodoOrtogonal<string> *row, *node, *previousNode;//con este se accederá a las filas 
    row = layer;
    node = row->getSiguiente();//puesto que mínimo serán de 2x2 y poprque de esta forma puedo revisar el anterior sin tanta dificultad xD
        
    do{        
        do{//para recorrer cada fila                            
            do{//para recorrer cada columna
                string* contenido = this->getMenorDato(matriz, layer, row, node, stoi(((node->getAnterior()!= NULL)?(*(node->getAnterior()->getContenido())):(*(previousNode->getContenido())))));
                if(contenido != NULL){
                    if(node->getAnterior()!= NULL){
                        node->getAnterior()->setContenido(contenido);
                    }else{
                        previousNode->setContenido(contenido);//ya me dio duda de si esto si va a actualizar el contenido del nodo de la matriz... si no cambia el contenido ya sabes por qué es, y en ese caso si no dieras cómo arreglarlo si tendrás que hacer la revisión de si el índice+1 es = al contenido, haciendo la suposición de que aumenta en 1...
                        //si no cambia, creo que lo que tendrías que hacer es usa el &, recuerdo haberlo visto en la práctica del año pasado, quizá haya sido por eso mismo... sino tb puedes buscar xD, solo recuerda que tienes este finde nada más...
                    }                    
                }

                previousNode = node;//para que así pueda hacerse la commparación del contenido del último nodo de la fila|capa anterior                
                node = node->getSiguiente();
            }while(node!=NULL);//podríamos colocar que se detenga cuando siguiente sea == NULL, así al salir se podrá imprimir la útlima fila con | al ini y al final xD

            row = row->getAbajo();
            node = row;
        }while(row!=NULL);//con revisar uno basta por el hecho de tener =# de elementos
            
        node = row = layer = (layer->getEntrante());//[v]                            
    }while(layer != NULL);
}

string* ManejadorOrdenamiento::getMenorDato(MatrizOrtogonal<string>* matriz, NodoOrtogonal<string>* capaInicial,
    NodoOrtogonal<string>* filaInicial, NodoOrtogonal<string>* nodoInicial, int posibleMenorDato){
    
    NodoOrtogonal<string> *layer = capaInicial;//este nodo se utilizará para accedere a todo de la capa
    NodoOrtogonal<string> *row = filaInicial;
    NodoOrtogonal<string> *node = nodoInicial;//con este se accederá a las filas      
    NodoOrtogonal<string> *smallerNode = NULL;                  

    do{                 
        do{//para recorrer cada fila                            
            do{//para recorrer cada columna
                if(stoi(*(node->getContenido())) < posibleMenorDato){//yo pensaría que aquí no se comparan las direcciones...
                    cout<<"compracion [busqueda nodo]: contenido nodo-> "<<node->getContenido()<<"criterio búsqueda-> "<<posibleMenorDato;
                    smallerNode = node;                    
                }
                node = node->getSiguiente();
            }while(node!=NULL);//podríamos colocar que se detenga cuando siguiente sea == NULL, así al salir se podrá imprimir la útlima fila con | al ini y al final xD

            row = row->getAbajo();
            node = row;
        }while(row!=NULL);//con revisar uno basta por el hecho de tener =# de elementos
            
        layer = layer->getEntrante();//[v]                    
        node = row = layer;//row = layer; node = row;   
    }while(layer != NULL);

    if(smallerNode!= NULL){
        string* contenido = smallerNode->getContenido();
        smallerNode->setContenido(new string(to_string(posibleMenorDato)));
        return contenido;
    }
    return NULL;
}



/*bool ManejadorOrdenamiento::esMatrizOrdenada(MatrizOrtogonal<string>* matriz){
//Se compara la matriz que está modif el usuario, con la ordenada...
}*/

MatrizOrtogonal<string>* ManejadorOrdenamiento::getMatrizOrdenada(){return this->matrizOrdenada;}
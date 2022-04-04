#include "ManejadorOrdenamiento.h"

using namespace std;

void ManejadorOrdenamiento::ordenarMatriz(MatrizOrtogonal<string>* matriz){//este nodo lo obtendrá de tablero, puesto que éste es quien lo posee...
    this->matrizOrdenada = new MatrizOrtogonal<string>(matriz->getAncho(), matriz->getAlto(), matriz->getNumeroNiveles());
    this->matrizOrdenada->copyMatrix(matriz);
    //puesto que iniciarás a partir de la matriz original, no será nec ubicar al nodo vacío al final, porque ese es su lugar por defecto...
    int nodosRevisados = 1;//aunque tb podría llamárserles ordenados... xD

    NodoOrtogonal<string> *layer = this->matrizOrdenada->getPrimerNodo();//este nodo se utilizará para accedere a todo de la capa
    NodoOrtogonal<string> *row, *node, *previousNode;//con este se accederá a las filas
    row = layer;
    node = row->getSiguiente();//puesto que mínimo serán de 2x2 y poprque de esta forma puedo revisar el anterior sin tanta dificultad xD

    do{
        do{//para recorrer cada fila
            do{//para recorrer cada columna
                string contenido = getMenorDato(matriz, layer, row, node, nodosRevisados, stoi(((node->getAnterior()!= NULL)?(node->getAnterior()->getContenido()):(previousNode->getContenido()))));
                if(contenido.compare("NULL") != 0){
                    if(node->getAnterior()!= NULL){
                        node->getAnterior()->setContenido(contenido);
                    }else{
                        previousNode->setContenido(contenido);//ya me dio duda de si esto si va a actualizar el contenido del nodo de la matriz... si no cambia el contenido ya sabes por qué es, y en ese caso si no dieras cómo arreglarlo si tendrás que hacer la revisión de si el índice+1 es = al contenido, haciendo la suposición de que aumenta en 1...
                        //si no cambia, creo que lo que tendrías que hacer es usa el &, recuerdo haberlo visto en la práctica del año pasado, quizá haya sido por eso mismo... sino tb puedes buscar xD, solo recuerda que tienes este finde nada más...
                    }
                }

                nodosRevisados++;

                previousNode = node;//para que así pueda hacerse la commparación del contenido del último nodo de la fila|capa anterior
                node = node->getSiguiente();
            }while(node!=NULL && (nodosRevisados < ((matriz->getAlto()*matriz->getAncho()*matriz->getNumeroNiveles())-1)));//podríamos colocar que se detenga cuando siguiente sea == NULL, así al salir se podrá imprimir la útlima fila con | al ini y al final xD

            row = row->getAbajo();
            node = row;
        }while(row!=NULL);//con revisar uno basta por el hecho de tener =# de elementos

        node = row = layer = (layer->getEntrante());//[v]
    }while(layer != NULL);
}

string ManejadorOrdenamiento::getMenorDato(MatrizOrtogonal<string>* matriz, NodoOrtogonal<string>* capaInicial,
    NodoOrtogonal<string>* filaInicial, NodoOrtogonal<string>* nodoInicial, int numeroRevisados, int posibleMenorDato){

    int nodosRevisados = numeroRevisados;

    NodoOrtogonal<string> *layer = capaInicial;//este nodo se utilizará para accedere a todo de la capa
    NodoOrtogonal<string> *row = filaInicial;
    NodoOrtogonal<string> *node = nodoInicial;//con este se accederá a las filas
    NodoOrtogonal<string> *smallerNode = NULL;

    do{
        do{//para recorrer cada fila
            do{//para recorrer cada columna
                    cout<<"contenido previo comp en SN: "<<node->getContenido();
                if(stoi(node->getContenido()) < posibleMenorDato){
                    cout<<"compracion [busqueda nodo]: contenido nodo-> "<<node->getContenido()<<"criterio búsqueda-> "<<posibleMenorDato;
                    smallerNode = node;//si están mal las referencias, quizá lo que deberías hacer aquí es una copia, bueno aunque en realidad si nec que éste smaller posea las ref orig, para hacer la reasignación...
                    cout<<"MOrd: "<<smallerNode;
                }
                node = node->getSiguiente();
                cout<<"MOrd: "<<node;
                nodosRevisados++;
            }while(node!=NULL && nodosRevisados < ((matriz->getAlto()*matriz->getAncho()*matriz->getNumeroNiveles())-1));//debe ser la multi-1 puesto que así no se revisará el último nodo que contiene el blankSimb, evitando así errores por el stoi xD

            row = row->getAbajo();
            node = row;
        }while(row!=NULL);//con revisar uno basta por el hecho de tener =# de elementos

        layer = layer->getEntrante();//[v]
        node = row = layer;//row = layer; node = row;
    }while(layer != NULL);

    if(smallerNode!= NULL){
        string contenido = smallerNode->getContenido();
        smallerNode->setContenido(to_string(posibleMenorDato));
        return contenido;
    }
    return "NULL";
}

bool ManejadorOrdenamiento::esMatrizOrdenada(MatrizOrtogonal<string>* matrizActual){
    NodoOrtogonal<string> *layer = this->matrizOrdenada->getPrimerNodo();//este nodo se utilizará para accedere a todo de la capa
    NodoOrtogonal<string> *row, *node;//con este se accederá a las filas

    NodoOrtogonal<string> *layerMatrtix2 = matrizActual->getPrimerNodo();//este nodo se utilizará para accedere a todo de la capa
    NodoOrtogonal<string> *rowMatrix2, *nodeMatrix2;

    do{
       node = row = layer;
       nodeMatrix2 = rowMatrix2 = layerMatrtix2;

       do{//para recorrer cada fila
           do{
              if(node->getContenido().compare(nodeMatrix2->getContenido()) != 0){
                  return false;
              }
              node = node->getSiguiente();
              nodeMatrix2 = nodeMatrix2->getSiguiente();
           }while(node!=NULL);//puesto que ambas matrices son iguales en dimensiones, aunque posiblemente no en el orden del contenido...

           row = row->getAbajo();
           node = row;
           rowMatrix2 = rowMatrix2->getAbajo();
           nodeMatrix2 = rowMatrix2;
       }while(row!=NULL);//con revisar uno basta por el hecho de tener =# de elementos

       layer = layer->getEntrante();//[v]
       layerMatrtix2 = layerMatrtix2->getEntrante();//[v]

    }while(layer != NULL);//quité lo de niveles, para tener vars menos xD

    return true;
}



MatrizOrtogonal<string>* ManejadorOrdenamiento::getMatrizOrdenada(){return this->matrizOrdenada;}

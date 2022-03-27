#include "ManejadorTablero.h"

using namespace std;

char ManejadorTablero::crearTableroManual(Tablero* tablero){
    string niveles, ancho, alto;
    
    cout<<"\t\t\t\t::::CREACIÓN DE TABLERO::::\n";
    cout<<"\n1. Ingresa tu nombre: ";
    cin>>nombreJugador;
    cout<<"\n2. Ingresa el #niveles:  ";//minimo debería ser de 1
    cin>>niveles;
    cout<<"\n3. Ingresa el ancho: ";//min de 2, esto por la lógica el juego...
    cin>>ancho;
    cout<<"\n4. Ingresa el alto: ";//min de 2
    cin>>alto;

    tablero = new Tablero(stoi(niveles), stoi(ancho), stoi(alto));//se crea el tablero y por tanto la matriz...    

    if(solicitarDatos(tablero) == '7'){
        return '7';
    }    
    return '0';
}

char ManejadorTablero::solicitarDatos(Tablero* tablero){
    int niveles = 1, filas = 1, columnas = 1;
    string dato;    
    
    cout<<"\nIngresa los datos de la casilla en [nivel, fila, columna] solicitada :)\n";
    cout<<"[presiona ENTER para continuar]\n";
    system("pause");

    while((niveles*filas*columnas) < (tablero->getLevels()*tablero->getHeight()*tablero->getWidth())){
        tablero->getMatrizOrtogonal()->mostrarDatos();//aunque se volverá más complejo, pero sino no se podrá verificar... y también mostrar esto en el juego xD xD

        printf("\n\n%-25s", "[S] salir\n");
        cout<<"\nIngresa valor de casilla ["<<niveles<<", "<<filas<<", "<<columnas<<"]: ";
        cin>>dato;

        if(dato != "S"){
            tablero->agregarElementos(dato);//este es el que llena los datos sin recurrir a un solo ciclo xD            

            if(columnas < tablero->getWidth()){//este bloque de condiciones anidadas está renice xD, en si todo lo que está dentro del while xD
                columnas++;
            }else{
                if(filas < tablero->getHeight()){
                    filas++;
                    columnas = 1;
                }else{
                    if(niveles < tablero->getLevels()){
                        niveles++;
                        columnas = filas = 1;//columnas = 1;
                    }//sino, no se hace nada porque el while se encarga de frenar la solicitud...
                }
            }
            system("clear");
        }else{
            char decision = this->confirmarAccion('S');
             if(decision == '7'){
                return decision;
            }//con esto se tendría que salir al home
        }        
    }

    this->tableroOriginal = tablero;
    return '0';//puesto que no se tiene una axn diferente cuando se retorna este 0, lo que pasará es que se iniciará la siguiente fase [jugar xD]...
}//nice

char ManejadorTablero::confirmarAccion(char opcion){
    string mensaje = "De verdad deseas ";
    char decision;
    
    mensaje += ((opcion == 'R')?"reiniciar":((opcion== 'T')?"terminar":"salir"));
    mensaje += " el juego?\n\t[S/N]";

    cout<<mensaje;//printf("%15s",mensaje);//debe ser con cout, porque el printf no tiene la capacidad de leer variables strings [cadenas literales si, pero en vars no], solo si están en el tipo de C [char[]/char*], lo cual se puede obtener con c_str() que pertenece a la librería <stdio.h>
    cin>>decision;     
    
    return ((decision=='S' && opcion == 'R')?'6':((decision=='S' && opcion == 'T')?'8':
    ((decision=='S' && opcion == 'S')?'7':'0')));//si en vía 0, es porque nada pasará...
}

string ManejadorTablero::getNombreJugador(){return this->nombreJugador;}
Tablero* ManejadorTablero::getMatrizOriginal(){return this->tableroOriginal;}
#include "ManejadorTablero.h"

using namespace std;

ManejadorTablero::ManejadorTablero(){
    /*this->jugador = new char[30];//por el caracter de fin
    /*strcpy(jugador, "cadena");
    cout<<jugador;*/
}

char ManejadorTablero::crearTableroManual(Tablero* tablero){    
    //char *nombreJugador = new char[25];
    string niveles, ancho, alto;
    
    cout<<"\t\t\t\t::::CREACIÓN DE TABLERO::::\n";
    cout<<"\n1. Ingresa tu nombre: ";
    cin.get();
    getline(cin, jugador);
    cout<<"\n2. Ingresa el #niveles:  ";//minimo debería ser de 1
    cin>>niveles;
    cout<<"\n3. Ingresa el ancho: ";//min de 2, esto por la lógica el juego...
    cin>>ancho;
    cout<<"\n4. Ingresa el alto: ";//min de 2
    cin>>alto;

    //this->jugador = (char*) malloc((nombreJugador).length()+1);
    //this->setNombre(nombreJugador);
    cout<<jugador;
    /*this->jugador = nombreJugador.c_str();*/

    tablero = new Tablero(stoi(ancho), stoi(alto), stoi(niveles));//se crea el tablero y por tanto la matriz...    

    if(solicitarDatos(tablero) == '7'){
        return '7';
    }    
    return '0';
}

char ManejadorTablero::solicitarDatos(Tablero* tablero){
    int niveles = 1, filas = 1, columnas = 1;
    string dato;    
    
    system("clear");
    cout<<"\nIngresa los datos de la casilla en [nivel, fila, columna] solicitada :)\n";
    cout<<"[presiona ENTER para continuar]\n";
    cin.get();
    cin.get();

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

/*void ManejadorTablero::setNombre(char* cadena){
    delete[] jugador;
    cout<<"error antes de crear?";
    jugador = new char[26];
    cout<<"error al crear?";
    strcpy(jugador, cadena);
    cout<<"error al asignar?";
}*/

string ManejadorTablero::getNombreJugador(){return jugador;}
Tablero* ManejadorTablero::getMatrizOriginal(){return this->tableroOriginal;}
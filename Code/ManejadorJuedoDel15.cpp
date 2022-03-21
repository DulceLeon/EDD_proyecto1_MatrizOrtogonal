#include "ManejadorJuegoDel15.h"

using namespace std;

ManejadorJuegoDel15::ManejadorJuegoDel15(){
    this->iniciarJuego();
}

void ManejadorJuegoDel15::iniciarJuego(){
    char opcion = '0';//home

    do{
        switch (opcion){
        case '0':
            opcion = this->mostrarHome();
            break;
        case '1':
            opcion = this->crearTableroManual();//es decir que de estos casos de creación, no se saldrá hasta que se termine el juego, se reinicie o resuleva el tablero xD xD
            break;
        case '2':
            opcion = this->crearTableroAletorio();
            break;
        case '3':
            opcion = this->cargarTablero();
            break;
        case '4':
            opcion = this->verHistorial();
            break;
        case '5':
            opcion = this->verDetalle();
            break;//reiniciar no debe estar aquí... puesto que es invocado dentro de jugar...
        default://creo que no es necesario... xD            
        }
        system("cls");//no creo que borre info que no debería xD, porque cuando se sale del caso, es porque resulta nec cb de él...
    }while(opcion != '7');//iba a poner -3, pero me da cosita que de error con eso xD

    cout<<"Hasta pronto :')\n";
}

char ManejadorJuegoDel15::mostrarHome(){    
    printf("%15s\n","1. Crear tablero");
    printf("%15s\n","2. Cargar tablero");
    printf("%15s\n","3. Crear tablero aleatorio");
    printf("%15s\n","4. Ver historial");
    printf("%15s\n","7. Salir");
    printf("\n\n\n");    
    printf("%11s\n\t%10s", "  ||||||", "|||||||||");
    printf("%11s\n\t%10s", " |||||||", "||||");
    printf("%11s\n\t%10s", "////||||", "||||||||");
    printf("%11s\n\t%10s", "    ||||", "     |||");
    printf("%11s\n\t%10s", "    ||||", "     |||");
    printf("%11s\n\t%10s", "|||||||||||","||||||||");
    cout<<endl<<endl<<endl<<"opcion: ";
    cin>>opcion;//aquí se pide el dato
    return opcion;    
}

char ManejadorJuegoDel15::crearTableroManual(){
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

    this->tablero = new Tablero(stoi(niveles), stoi(ancho), stoi(alto));//se crea el tablero y por tanto la matriz...

    if(solicitarDatos() == '7'){
        return '7';
    }
    return jugar();//puesto que es el ultimo paso, el valor a retornar, debe ser el de éste método xD
}

char ManejadorJuegoDel15::solicitarDatos(){
    int niveles = 1, filas = 1, columnas = 1;
    string dato;    
    
    cout<<"\nIngresa los datos de la casilla en [nivel, fila, columna] solicitada :)\n";
    cout<<"[presiona ENTER para continuar]\n";
    system("pause");

    while((niveles*filas*columnas) < this->tablero->getLevels()){
        this->tablero->getMatrizOrtogonal()->mostrarDatos();//aunque se volverá más complejo, pero sino no se podrá verificar... y también mostrar esto en el juego xD xD

        printf("\n\n%-25s", "[S] salir\n");
        cout<<"\nIngresa valor de casilla ["<<niveles<<", "<<filas<<", "<<columnas<<"]: ";
        cin>>dato;

        if(dato != "S"){
            this->tablero->agregarElementos(dato);//este es el que llena los datos sin recurrir a un solo ciclo xD            

            if(columnas < this->tablero->getWidth()){//este bloque de condiciones anidadas está renice xD, en si todo lo que está dentro del while xD
                columnas++;
            }else{
                if(filas < this->tablero->getHeight()){
                    filas++;
                    columnas = 1;
                }else{
                    if(niveles < this->tablero->getLevels()){
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
    return '0';//no sucede nada con esto...
}//nice

char ManejadorJuegoDel15::crearTableroAletorio(){

}

char ManejadorJuegoDel15::cargarTablero(){

}

char ManejadorJuegoDel15::jugar(){    
    char opcion = NULL;
    string* movimientosPosibles;//para recibir un arreglo, se debe hacer con un ptro, puesto que lo que se retorna es un apuntador a la primer posición...    
    this->tablero->setEspacioVacio();//solo se req invocar 1 vez, para establecer el nodo inicial xD xD, aunque por el hecho de seguir siendo el mismo, porque se cb las ref de los apuntadores de las demás direcciones, creo que no es nec recuperarlo xD xD, pero por si xD

    cout<<"\nPor favor ingresa el número correspondiente al tipo de movimiento a realizar :)\n";
    cout<<"[presiona ENTER para continuar]\n";
    system("pause");

    while(false && (opcion != 'T')){
        if(opcion != NULL){
            string posicion(1,opcion);
            this->tablero->getMatrizOrtogonal()->shift(this->tablero->getNodoVacio(), movimientosPosibles[stoi(posicion)-1]);//puesto que de no seleccionar un comodín para dejar de jugar, este tiene la ubic+1 xD
            //se revisa si la matriz está ordenada [quizá podría ponerse un criterio para que no se esté revisando a cada ratito]
        }

        system("clear");
        this->tablero->getMatrizOrtogonal()->mostrarDatos();//se muestran los datos de la matriz
        movimientosPosibles = this->tablero->getMovimientosPosibles();        

        printf("\n\n%-65s", "[R] Reiniciar  |  [T] Terminar|  [S] Salir\n");
        cout<<endl<<"Posibles Movimientos: "<<((movimientosPosibles[0]!= "")?("(1) "+movimientosPosibles[0]+","):"")<<((movimientosPosibles[1]!= "")?("(2) "+movimientosPosibles[1]+","):"")
        <<((movimientosPosibles[2]!= "")?("(3) "+movimientosPosibles[2]+","):"")<<((movimientosPosibles[3]!= "")?("(4) "+movimientosPosibles[3]+","):"")
        <<((movimientosPosibles[4]!= "")?("(5) "+movimientosPosibles[4]+","):"")<<((movimientosPosibles[5]!= "")?("(6) "+movimientosPosibles[5]+","):"");
        cin>>opcion;        
        
        if((opcion == 'R') || (opcion == 'T') || (opcion == 'S')){        
            char decision = confirmarAccion(opcion);
            if(decision!='8'){//si es 8, no se hará algo, porque debe seguir su transcurso natural solo que antes de tiempo... esto se logra con la condi en el while de "opcion == 'T'"          
                if(decision == '6'){
                    this->reiniciar();
                }else if(decision == '7'){
                    return decision;//para que se vaya al método del switch y se muestre así el home...
                }
                opcion = NULL;//para que así no exe el método para el shift, puesto que no escogió una opción corresp a un movimiento...            
            }
        }
    }

    //se invoca al método para calcular el total: si terminó a la fuerza, si opcion == T, hará la búsqueda del total, sino hará una simple multiplicación... por eso para saber que hacer recibirá un argu indicando si fue a la fuerza [true] o no [false]
    this->mostrarResumen();
    return '0';//para así mostrar el home en cualquiera de los 2 casos...
}

char ManejadorJuegoDel15::confirmarAccion(char opcion){
    string mensaje = "De verdad deseas ";
    char decision;
    
    mensaje += ((opcion == 'R')?"reiniciar":((opcion== 'T')?"terminar":"salir"));
    mensaje += " el juego?\n\t[S/N]";

    printf("%15s",mensaje);
    cin>>decision;     
    
    return ((decision=='S' && opcion == 'R')?'6':((decision=='S' && opcion == 'T')?'8':
    ((decision=='S' && opcion == 'S')?'7':'0')));//si en vía 0, es porque nada pasará...
}

void ManejadorJuegoDel15::mostrarResumen(){//esto se completa con el manejador de resultados, para este punto ya se ha registrado los datos en el archivo y se ha ordenado el arreglo

}

char ManejadorJuegoDel15::verHistorial(){

}

char ManejadorJuegoDel15::verDetalle(){
    
}

void ManejadorJuegoDel15::reiniciar(){
    
}   
#include "ManejadorJuegoDel15.h"

using namespace std;

ManejadorJuegoDel15::ManejadorJuegoDel15(){
    this->iniciarJuego();    
    this->manejadorOrdenamiento = new ManejadorOrdenamiento();
}//aunque el compilador genere el constructor por defecto, si vas a implementarlo, entonces deberás declararlo en el .h

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
           // opcion = this->crearTableroAletorio();
            break;
        case '3':
            //opcion = this->cargarTablero();
            break;
        case '4':
            //opcion = this->verHistorial();
            break;
        case '5':
            //opcion = this->verDetalle();
            break;//reiniciar no debe estar aquí... puesto que es invocado dentro de jugar...
        default:
            cout<<"Opción invalida, puedes ingresar cualquiera de las opciones del menú";
            opcion = 0;//para que así regrese en caso se equivoque...
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
    if(this->manejadorTablero->crearTableroManual(this->tablero) == '7'){
        return '7';
    }
    return jugar();//puesto que es el ultimo paso, el valor a retornar, debe ser el de éste método xD
}

/*char ManejadorJuegoDel15::crearTableroAletorio(){

}*/

/*char ManejadorJuegoDel15::cargarTablero(){

}*/

char ManejadorJuegoDel15::jugar(){    
    char *opcion = NULL;
    string* movimientosPosibles;//para recibir un arreglo, se debe hacer con un ptro, puesto que lo que se retorna es un apuntador a la primer posición...    
    bool juegoGanado = false;
    this->tablero->setEspacioVacio();//solo se req invocar 1 vez, para establecer el nodo inicial xD xD, aunque por el hecho de seguir siendo el mismo, porque se cb las ref de los apuntadores de las demás direcciones, creo que no es nec recuperarlo xD xD, pero por si xD

    cout<<"\nPor favor ingresa el número correspondiente al tipo de movimiento a realizar :)\n";
    cout<<"[presiona ENTER para continuar]\n";
    system("pause");

    while(juegoGanado && (*opcion != 'T')){//no dejé una comp con el new, puesto que creo que al hacer eso lo que estaría comparando es si las posiciones en memo son iguales...
        if(opcion != NULL){
            string posicion(1,*opcion);//esto lo hiciste para que tome el número literal y no la rep ASCII que daría si usas directamente la var opción...
            this->tablero->getMatrizOrtogonal()->shift(this->tablero->getNodoVacio(), (stoi(posicion)-1));//puesto que de no seleccionar un comodín para dejar de jugar, este tiene la ubic+1 xD
         //   juegoGanado = this->manejadorOrdenamiento->esMatrizOrdenada(this->tablero->getMatrizOrtogonal());//se revisa si la matriz está ordenada [quizá podría ponerse un criterio para que no se esté revisando a cada ratito]
        }

        system("clear");
        this->tablero->getMatrizOrtogonal()->mostrarDatos();//se muestran los datos de la matriz
        movimientosPosibles = this->tablero->getMovimientosPosibles();        

        printf("\n\n%-65s", "[R] Reiniciar  |  [T] Terminar|  [S] Salir\n");
        cout<<endl<<"Posibles Movimientos: "<<((movimientosPosibles[0]!= "")?("(1) "+movimientosPosibles[0]+","):"")<<((movimientosPosibles[1]!= "")?("(2) "+movimientosPosibles[1]+","):"")
        <<((movimientosPosibles[2]!= "")?("(3) "+movimientosPosibles[2]+","):"")<<((movimientosPosibles[3]!= "")?("(4) "+movimientosPosibles[3]+","):"")
        <<((movimientosPosibles[4]!= "")?("(5) "+movimientosPosibles[4]+","):"")<<((movimientosPosibles[5]!= "")?("(6) "+movimientosPosibles[5]+","):"");
        cin>>*opcion;//imagino que debo colocar eso, o será la dirección? para que sepa DÓNDE debe almacenar??? así como el scanf??? 
        
        if((*opcion == 'R') || (*opcion == 'T') || (*opcion == 'S')){        
            char decision = this->manejadorTablero->confirmarAccion(*opcion);
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

 //   this->mostrarResumen(((*opcion == 'T')?true:false));
    return '0';//para así mostrar el home en cualquiera de los 2 casos...
}

/*void ManejadorJuegoDel15::mostrarResumen(bool termandoALaFuerza){//esto se completa con el manejador de resultados, para este punto ya se ha registrado los datos en el archivo y se ha ordenado el arreglo
    //se invoca al método para calcular el total: si terminó a la fuerza, si opcion == T, hará la búsqueda del total, sino hará una simple multiplicación... por eso para saber que hacer recibirá un argu indicando si fue a la fuerza [true] o no [false]
}*/

/*char ManejadorJuegoDel15::verHistorial(){

}

char ManejadorJuegoDel15::verDetalle(){
    
}*/

void ManejadorJuegoDel15::reiniciar(){
    this->tablero = this->manejadorTablero->getMatrizOriginal();
}   

ManejadorJuegoDel15::~ManejadorJuegoDel15(){
    this->tablero->~Tablero();//esto por si acaso no se invoca de forma automática a la instancia que tiene el delete implementado xD
    delete this->tablero;
    delete this->manejadorTablero;
    delete this->manejadorOrdenamiento;
}
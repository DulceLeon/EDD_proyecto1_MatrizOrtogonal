#include "ManejadorJuegoDel15.h"

using namespace std;

ManejadorJuegoDel15::ManejadorJuegoDel15(void){
    this->manejadorOrdenamiento = new ManejadorOrdenamiento();
    this->manejadorTablero = new ManejadorTablero();
    this->tablero = new Tablero();
}//aunque el compilador genere el constructor por defecto, si vas a implementarlo, entonces deberás declararlo en el .h

void ManejadorJuegoDel15::iniciarJuego(){
    char opcion = '0';//home

    do{
        switch (opcion){
        case '0':
            opcion = this->mostrarHome();
            break;
        case '1': case '2': case '3':
            opcion = this->crearElTablero(opcion);
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
        system("clear");//no creo que borre info que no debería xD, porque cuando se sale del caso, es porque resulta nec cb de él...
    }while(opcion != '7');//iba a poner -3, pero me da cosita que de error con eso xD

    cout<<"Hasta pronto :')\n";
}

char ManejadorJuegoDel15::mostrarHome(){
    printf("\t%15s\n\t","1. Crear tablero");
    printf("%15s\n\t","2. Cargar tablero");
    printf("%15s\n\t","3. Crear tablero aleatorio");
    printf("%15s\n\t","4. Ver historial");
    printf("%15s\n\t","7. Salir");
    printf("\n\n\n");
    printf("%21s%10s\n", "  ||||||", "|||||||||");
    printf("%21s%5s\n", " |||||||", "||||");
    printf("%21s%9s\n", "////||||", "||||||||");
    printf("%21s%10s\n", "    ||||", "     |||");
    printf("%21s%10s\n", "    ||||", "     |||");
    printf("%23s%5s\n", "|||||||||||","||||||||");
    cout<<endl<<endl<<endl<<"opcion: ";
    cin>>opcion;//aquí se pide el dato
    return opcion;
}

char ManejadorJuegoDel15::crearElTablero(char tipoCreacion){
    if(this->manejadorTablero->crearTablero((&(tablero)), tipoCreacion) == '7'){
        return '7';
    }

     // this->manejadorOrdenamiento->ordenarMatriz(this->manejadorTablero->getTableroOriginal()->getMatrizOrtogonal(), tablero->getSymbBlank());//sino pues con el tablero original y si ninguna no, entonces que se envíe el valor... creo que eso hacía antes al enviar tablero para crearlo manualmente...
    cout<<endl<<"Es hora de jugar :)";
    return jugar();
}

char ManejadorJuegoDel15::jugar(){
    char opcion = '$';
    string* movimientosPosibles;//para recibir un arreglo, se debe hacer con un ptro, puesto que lo que se retorna es un apuntador a la primer posición...
    bool juegoGanado = false;

    cout<<"instancia tablero-J15: "<<tablero;
    cout<<"instancia matriz-tablero: "<<tablero->getMatrizOrtogonal();
    this->tablero->setEspacioVacio();//puesto que por defecto se add siempre en el último que se haya creado...

    cout<<"\nPor favor ingresa el número correspondiente al tipo de movimiento a realizar :)\n";
    cout<<"[presiona ENTER para continuar]\n";
    cin.get();//eqq de system("pause");
    cin.get();

    while(!juegoGanado && (opcion != 'T')){//no dejé una comp con el new, puesto que creo que al hacer eso lo que estaría comparando es si las posiciones en memo son iguales...
        if(opcion != '$'){
            string posicion(1,opcion);//esto lo hiciste para que tome el número literal y no la rep ASCII que daría si usas directamente la var opción...
            cout<<"Manejador15 "<<tablero->getNodoVacio();
            cout<<" contenido? "<<*(tablero->getNodoVacio())<<endl;
            this->tablero->getMatrizOrtogonal()->shift(tablero->getElNodoVacio(), (stoi(posicion)-1));//puesto que de no seleccionar un comodín para dejar de jugar, este tiene la ubic+1 xD
     //       juegoGanado = this->manejadorOrdenamiento->esMatrizOrdenada(this->tablero->getMatrizOrtogonal());//se revisa si la matriz está ordenada [quizá podría ponerse un criterio para que no se esté revisando a cada ratito]
        }

        //system("clear");
        this->tablero->getMatrizOrtogonal()->mostrarDatos();//se muestran los datos de la matriz
        movimientosPosibles = this->tablero->getMovimientosPosibles();

        printf("\n\n%-65s", "[R] Reiniciar  |  [T] Terminar|  [S] Salir\n");
        cout<<endl<<"Posibles Movimientos: "<<((movimientosPosibles[0]!= "")?("(1) "+movimientosPosibles[0]+","):"")<<((movimientosPosibles[1]!= "")?("(2) "+movimientosPosibles[1]+","):"")
        <<((movimientosPosibles[2]!= "")?("(3) "+movimientosPosibles[2]+","):"")<<((movimientosPosibles[3]!= "")?("(4) "+movimientosPosibles[3]+","):"")
        <<((movimientosPosibles[4]!= "")?("(5) "+movimientosPosibles[4]+","):"")<<((movimientosPosibles[5]!= "")?("(6) "+movimientosPosibles[5]+","):"");
        cin>>opcion;//imagino que debo colocar eso, o será la dirección? para que sepa DÓNDE debe almacenar??? así como el scanf???

        if((opcion == 'R') || (opcion == 'T') || (opcion == 'S')){
            char decision = this->manejadorTablero->confirmarAccion(opcion);
            if(decision!='8'){//si es 8, no se hará algo, porque debe seguir su transcurso natural solo que antes de tiempo... esto se logra con la condi en el while de "opcion == 'T'"
                if(decision == '6'){
                    this->reiniciar();
                }else if(decision == '7'){
                    return decision;//para que se vaya al método del switch y se muestre así el home...
                }
                opcion = '$';//para que así no exe el método para el shift, puesto que no escogió una opción corresp a un movimiento...
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
    //this->tablero = this->manejadorTablero->getTableroOriginal();
    this->tablero->getMatrizOrtogonal()->copyMatrix(this->manejadorTablero->getTableroOriginal()->getMatrizOrtogonal());//debe ser la copia, sino todos los punterios y ref que contenía ya no serían válidas y con eso habría un error[NullPointer] o incongruencia
    this->tablero->setEspacioVacio();//puesto que por defecto se add siempre en el último espacio y como se reseteó entonces hay que volver a "localizarlo"
}

ManejadorJuegoDel15::~ManejadorJuegoDel15(){
    this->tablero->~Tablero();//esto por si acaso no se invoca de forma automática a la instancia que tiene el delete implementado xD
    delete this->tablero;
    delete this->manejadorTablero;
    delete this->manejadorOrdenamiento;
}

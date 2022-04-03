#include "ManejadorTablero.h"

using namespace std;

ManejadorTablero::ManejadorTablero(){
    this->tableroOriginal = new Tablero();
    this->manejadorCargaDatos = new ManejadorCargaDatos();
    this->herramientas = new Herramientas();
}

char ManejadorTablero::crearTableroManual(Tablero** tablero){
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

    cout<<jugador;
    /*this->jugador = nombreJugador.c_str();*/

    (*tablero) = new Tablero(stoi(ancho), stoi(alto), stoi(niveles));//se crea el tablero y por tanto la matriz...
    cout<<"instancia tablero-addDatos"<<(*tablero);//pues si agregabas *, estarías obteneiendo el content del segundo puntero, que sería la dir al ptro de la instancia de tablero, entonces para acceder a la dir de esa instancia se lograría accediendo al contenido del puntero que es contenido del 2do puntero xD

    if(solicitarDatos(tablero) == '7'){
        return '7';
    }
    return '0';
}

char ManejadorTablero::solicitarDatos(Tablero** tablero){
    int niveles = 1, filas = 1, columnas = 1;
    string dato;

   // system("clear");//recuerda, si comentas esta línea, podrás ver cómo se creo la matriz...
    cout<<"\nIngresa los datos de la casilla en [nivel, fila, columna] solicitada :)\n";
    cout<<"[presiona ENTER para continuar]\n";
    cin.get();
    cin.get();

    while((niveles*filas*columnas) < ((*tablero)->getLevels()*(*tablero)->getHeight()*(*tablero)->getWidth())){//El hacer así la multiplicación hace que el último de los nodos no pueda llenarse, lo cual es justo lo que req para así establecer el espacio vacío xD
        (*tablero)->getMatrizOrtogonal()->mostrarDatos();//aunque se volverá más complejo, pero sino no se podrá verificar... y también mostrar esto en el juego xD xD

        printf("\n\n%-25s", "[S] salir\n");
        cout<<"\nIngresa valor de casilla ["<<niveles<<", "<<filas<<", "<<columnas<<"]: ";
        cin>>dato;
        //cout<<"n*f*c = "<<(niveles*filas*columnas);

        if(dato != "S"){
            (*tablero)->agregarElementos(dato);//este es el que llena los datos sin recurrir a un solo ciclo xD
            //cout<<"elemento agregado";

            if(columnas < (*tablero)->getWidth()){//este bloque de condiciones anidadas está renice xD, en si todo lo que está dentro del while xD
                columnas++;
            }else{
                if(filas < (*tablero)->getHeight()){
                    filas++;
                    columnas = 1;
                }else{
                    if(niveles < (*tablero)->getLevels()){
                        niveles++;
                        columnas = filas = 1;//columnas = 1;
                    }//sino, no se hace nada porque el while se encarga de frenar la solicitud...
                }
            }
            system("clear");//a mi pensar si se exe este aquí, provocará errores... bueno, ahora que lo veo quizá no xD
        }else{
            char decision = this->confirmarAccion('S');
             if(decision == '7'){
                return decision;
            }//con esto se tendría que salir al home
        }
    }

    (*tablero)->agregarElementos(((*tablero)->getSymbBlank()));//se setea el símbolo que representa el espacio vacío
    this->tableroOriginal = (*tablero);
    return '0';//puesto que no se tiene una axn diferente cuando se retorna este 0, lo que pasará es que se iniciará la siguiente fase [jugar xD]...
}//nice

bool ManejadorTablero::cargarTablero(Tablero** tablero){
    return (this->manejadorCargaDatos->cargarDatos(tablero, &jugador));
}

void ManejadorTablero::crearTableroAleatorio(Tablero** tablero){//no tendría por qué devolver algo, puesto que es un proceso automático y no deberían haber fallos técnicos [es decir no provocados por el usuario]
    cout<<"\t\t\t  ::::CREACION TABLERO ALEATORIO::::\n";
    int alto, ancho, niveles;
    int datosAgregados = 0, indice;

    alto = 2+rand()%14;//me daba curiosidad ver de 20, pero quizá sea mucho, mejor dejo como límite al 15 xD :v
    ancho = 2+rand()%14;
    niveles = 1+rand()%15;

    (*tablero) = new Tablero((ancho), (alto), (niveles));//se crea el tablero y por tanto la matriz...

    string numerosBase[((alto*ancho*niveles)-1)];
    this->herramientas->crearArregloOrdenado(numerosBase, ((alto*ancho*niveles)-1));//Debido al espacio vacío...

    do{
        indice = rand()%(((alto*ancho*niveles)-1));

        if(numerosBase[indice].compare("null") != 0){
            (*tablero)->agregarElementos(numerosBase[indice]);
            numerosBase[indice] = "null";
            datosAgregados++;
        }

    }while(datosAgregados < ((ancho*alto*niveles)-1));

    (*tablero)->agregarElementos(((*tablero)->getSymbBlank()));
    (*tablero)->getMatrizOrtogonal()->mostrarDatos();
    cout<<endl<<"\n\nsolo hace falta que ingreses tu nombre, justo aqui xD: ";
    cin.get();
    getline(cin, (this->jugador));
}

char ManejadorTablero::confirmarAccion(char opcion){
    string mensaje = "De verdad deseas ";
    char decision;

    mensaje += ((opcion == 'R')?"reiniciar":((opcion== 'T')?"terminar":"salir"));
    mensaje += " el juego?\n\t[S/N]";

    system("clear");
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
Tablero* ManejadorTablero::getTableroOriginal(){return this->tableroOriginal;}

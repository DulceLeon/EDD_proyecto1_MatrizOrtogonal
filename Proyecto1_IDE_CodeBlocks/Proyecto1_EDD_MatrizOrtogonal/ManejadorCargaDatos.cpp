#include "ManejadorCargaDatos.h"

using namespace std;

ManejadorCargaDatos::ManejadorCargaDatos(){
    this->delimitador = ',';
}

bool ManejadorCargaDatos::cargarDatos(Tablero** tablero, string *nombreJugador){
    string filename;
    char decision, delimitador = ',';
    string ancho, alto, niveles;
    string linea, dato;
    int datosLeidos = 0;

    system("clear");
    cout<<"\t\t\t\t::::CARGA DE TABLERO::::\n"<<endl<<endl;
    cout<<"La carga de datos está por empezar, pero antes de ello\n";
    cout<<"verifica si tu archivo cumple con la siguiente sintaxis\n\n";

    cout<<"1er linea: <niveles> , <ancho> , <alto>\n";
    cout<<"2da linea: <n_datos>     [donde n = ancho]\n";
    cout<<"#lineas totales = alto*niveles\n";
    cout<<"#datos totales = ancho*alto*niveles -1\n";
    cout<<"[esto ultimo porque el vacio ocupara la celda restante]";
    cout<<"\n\nTu archivo cumple con los requisitos? [S/N]";
    cout<<"\nSi no es asi mejor no continues :)\n\n";
    cin>>decision;

    if(decision == 'S' || decision == 's'){
        system("clear");
        cout<<"\nPor poco olvidaba preguntar tu nombre xD, escribelo, por favor: ";
        cin>>(*nombreJugador);
        cout << "\nIngresa el nombre del archivo: ";
        cin.get();
        getline(cin, filename);

        ifstream archivo(filename);

        if (!archivo.is_open()){
            cout << "\n\n\n**Error: archivo (" + filename + ") no encontrado.**" << endl;
        }else{
            getline(archivo, linea);
            stringstream stream(linea);

            getline(stream, niveles, delimitador);
            getline(stream, ancho, delimitador);
            getline(stream, alto, delimitador);
            cout<<ancho;cout<<"-"<<alto;cout<<"-"<<niveles<<endl;

            (*tablero) = new Tablero(stoi(ancho), stoi(alto), stoi(niveles));

            while (getline(archivo, linea))//datosLeidos < (((*tablero)->getAncho()*(*tablero)->getAlto()*(*tablero)->getAncho())-1), puesto que ya sabemos cuántos datos debemos leer xD
            {
                stringstream stream(linea);

                do{
                       /* cout<<"ancho: "(*tablero)->getWidth();
                        cout<<"alto: "<<(*tablero)->getHeight();
                        cout<<"niveles: "getHeight()*(*tablero)->getLevels();*/
                    if(datosLeidos < (((*tablero)->getWidth()*(*tablero)->getHeight()*(*tablero)->getLevels())-1)){
                        getline(stream, dato, delimitador);
                        (*tablero)->agregarElementos(dato);
                        cout<<"dato: "<<dato<<endl;
                    }//Es mejor poner el if para revisar los datos leidos y no en el while, pues suponiendo que no tenga todos los datos, se provocaría una excepción al intentar acceder a un espacio que no existe en el archivo...

                    datosLeidos++;//Debe estar aqupi fuera, no dentro del if, sino se crearía un bucle infinito por nunca descumplirse la condición de exe del doWhile... xD
                }while((datosLeidos % ((*tablero)->getWidth())) != 0);
            }
        }

        (*tablero)->agregarElementos(((*tablero)->getSymbBlank()));

       /* this->tableroOriginal = new Tablero((*tablero)->getWidth(), (*tablero)->getHeight(), (*tablero)->getLevels());
        this->tableroOriginal->getMatrizOrtogonal()->copyMatrix(((*tablero)->getMatrizOrtogonal()));*/
        return true;
    }
    return false;
}


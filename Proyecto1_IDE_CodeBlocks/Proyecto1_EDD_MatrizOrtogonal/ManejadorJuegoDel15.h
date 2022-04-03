#ifndef MANEJADORJUEGODEL15_H
#define MANEJADORJUEGODEL15_H

#include <cstdlib>
#include <iostream>
#include <string>
#include "Tablero.h"
#include "ManejadorTablero.h"
//#include "Tiempo.h"
//#include "ManejadorRegistros.h"//para las clases que están separadas, al importar debes hacerlo para el .h, a dif de las que en un solo archivo tienen ambas partes...
//#include "ManejadorResultadosPartida.h"
#include "ManejadorOrdenamiento.h"

using namespace std;
class ManejadorJuegoDel15{
    private:
        char opcion;
        Tablero* tablero;
        ManejadorTablero* manejadorTablero;
        int pasosEmpleados;
       // Tiempo* manejadorTiempo;
        //ManejadorResultadosPartida* manejadorResultadosPartida;
        //ManejadorRegistros* manejadorRegistros;//si este invocará al manejador de R//, entonces no debe existir instancia de él aquí sino solo en MReg, si no es así entonces si deben estar ambos, creo, o la sit eqq xD
        ManejadorOrdenamiento* manejadorOrdenamiento;
        //si vas a implementar el objeto que solucione automáticamente, entonces tb la instancia de él xD

        char mostrarHome();//op: 0
        char crearTableroManual();//op: 1
        char cargarTablero();
        char jugar();//se exe después que se haya especificado si después de cual de las formas de creación del tablero [imagino que se invocará dentro de los métodos de creación...]
        //void mostrarResumen(bool);//se invoacará internamente en el método confirmarAcción, dep de la respuesta xD
        //char verHistorial();//op: 4
        //char verDetalle();//op: 5, creo que tb se podría haber llamado internamente en historial, pero por la forma de las pantallas a mostrar mejor no xD
        void reiniciar();//limpia la matriz e invoca nuevamente a jugar...

    public:
        ManejadorJuegoDel15(void);
        void iniciarJuego();
        ~ManejadorJuegoDel15();
};
#endif
//aquí tendrá una instancia de tablero
//tb los demás atributos para formar los reportes, como
    //#pasos [usuario],
    //el obj que se encargará de llevar el conteo del tiempo y
    //si vas a implementar el objeto que solucione automáticamente, entonces tb la instancia de él xD
    //lo de la posición se obtendrá a partir del manejador de resultados, porque ese tednrá el listado o arreglo de los registros resumidos anteriores [posicion, nombre y punteo] para aśi no perder la info anterior a ésta...

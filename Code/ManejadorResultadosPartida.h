#ifndef MANEJADORRESULTADOSPARTIDA_H
#define MANEJADORRESULTADOSPARTIDA_H

#include <cstdlib>
#include <iostream>
#include <string>
#include "MatrizOrtogonal.cpp"

class ManejadorResultadosPartida{//qué vas a hacer, vas a hacer que este invoque al manejador de registros o que ese invoque a éste, indep de que decidas, debes hacer que cuando se envie un restultado de posicion, se muestre en pantalla
    //quizá suena más lógico que este invoque al otro, pero para que no se haga por secciones pienso que es mejor al revés...
    private:
        ManejadorResultadosPartida(MatrizOrtogonal<string>*);

        //ManejadorRegistros* manejadorRegistros;
        void calcularResultados();//este se invocará dentro del constructor, por eso es privado
        //OJO: lo de la posición se obtendrá a partir del manejador de resultados, porque ese tednrá el listado o arreglo de los registros resumidos anteriores [posicion, nombre y punteo] para aśi no perder la info anterior a ésta...
    public:
        int getTotal(bool);//dependiendo de la situación en la que se solicita esto [terminado a la fuerza o no], depende la forma de calcular lso R//
        //no pongo un getResultados, porque estos se escirbirán directamente al archivo y ahí se mostrará a detalle... y en todo caso si voy a mostrar en pantalla el detalle, lo haré al mismo momento que escribo el dato en el archivo...
};
#endif
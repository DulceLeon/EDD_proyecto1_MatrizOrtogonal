#include "Herramientas.h"

void Herramientas::crearArregloOrdenado(string arreglo[], int totalElementos){
    for(int actual = 1; actual <= totalElementos; actual++){
        arreglo[(actual-1)] = to_string(actual);
    }
}

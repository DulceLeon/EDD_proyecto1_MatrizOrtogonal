#ifndef MANEJADOR_TIEMPO_H
#define MANEJADOR_TIEMPO_H

#include <stdio.h>
#include <string>
#include <time.h>
//#include <ctime>

using namespace std;

class ManejadorTiempo{
    private:
        time_t tiempo1;
        time_t tiempo2;

        struct tm tiempoInicial;
        struct tm tiempoFinal;

        char formatoFecha1[70];
        char formatoFecha2[70];

        char formato[9] = "%H:%M:%S";//

        int bytesEscritos1;
        int bytesEscritos2;

    public:
        ManejadorTiempo();
        void setTiempoInicial();
        void setTiempoFinal();

        char* getTiempoInicial();
        char* getTiempoFinal();
        string getIntervaloTiempo();
};
#endif // MANEJADOR_TIEMPO_H

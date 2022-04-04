#include "ManejadorTiempo.h"

ManejadorTiempo::ManejadorTiempo(){
    /*string formatoHora = "%H:%M:%S";

    this->formato = formatoHora.c_str();*/
}

void ManejadorTiempo::setTiempoInicial(){
    //formatoFecha1 = new char();

    tiempo1 = time(NULL);
    tiempoInicial = *localtime(&tiempo1);
    bytesEscritos1 = strftime(formatoFecha1, sizeof formatoFecha1, formato, &tiempoInicial);
}

void ManejadorTiempo::setTiempoFinal(){
    //formatoFecha1 = new char();

    tiempo2 = time(NULL);
    tiempoFinal = *localtime(&tiempo2);
    bytesEscritos2 = strftime(formatoFecha2, sizeof formatoFecha2, formato, &tiempoFinal);
}


char* ManejadorTiempo::getTiempoInicial(){
    return formatoFecha1;//sin importar que bytesEscritors == 0, puesto que ya estará inicializado el ptro...
}

char* ManejadorTiempo::getTiempoFinal(){
    return formatoFecha2;
}

string ManejadorTiempo::getIntervaloTiempo(){
    int intervalo =  static_cast<int>(tiempo2 - tiempo1);

    int horas = intervalo / 3600;
    int minutos = (intervalo % 3600) / 60;
    int segundos = intervalo % 60;
    string tiempo = to_string(horas) + " " + to_string(minutos) + " " + to_string(segundos);

    return tiempo;
}

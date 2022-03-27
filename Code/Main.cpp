#ifndef MAIN_H
#define MAIN_H

#include <cstdlib>
#include <iostream>
#include <string>
#include "ManejadorJuegoDel15.h"

using namespace std;

int main(int args, char** argv){
    ManejadorJuegoDel15* manejadorJuegoDel15 = new ManejadorJuegoDel15();    

    manejadorJuegoDel15->iniciarJuego();
    return 0;
}
#endif
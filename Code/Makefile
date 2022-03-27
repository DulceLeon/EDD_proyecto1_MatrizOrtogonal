#Seccion:1, exe, el orden debe ser desde la clase más interna hasta la que engloba la exe de todos
output: NodoOrtogonal.o MatrizOrtogonal.o ManejadorTablero.o ManejadorOrdenamiento.o Tablero.o ManejadorJuegoDel15.o Main.o 
	g++ -o output NodoOrtogonal.o MatrizOrtogonal.o ManejadorTablero.o ManejadorOrdenamiento.o Tablero.o ManejadorJuegoDel15.o Main.o 
	
#Seccion:2, compilacion [build]
Main.o: Main.cpp
	g++ -c Main.cpp

ManejadorJuegoDel15.o: ManejadorJuegoDel15.cpp
	g++ -c ManejadorJuegoDel15.cpp

Tablero.o: Tablero.cpp Tablero.h
	g++ -c Tablero.cpp

ManejadorOrdenamiento.o: ManejadorOrdenamiento.cpp
	g++ -c ManejadorOrdenamiento.cpp

ManejadorTablero.o: ManejadorTablero.cpp
	g++ -c ManejadorTablero.cpp

MatrizOrtogonal.o: MatrizOrtogonal.cpp
	g++ -c MatrizOrtogonal.cpp

NodoOrtogonal.o: NodoOrtogonal.cpp
	g++ -c NodoOrtogonal.cpp

#Seccion:3, otros
#clean, esto resulta útil cuando los archivo nec exe en diferentes OS,
#puesto que los archivos que se generan son para el sistema específico
#en el que se compiló
clean: 
	-rm *.o output


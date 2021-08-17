//En  este archivo van las cabeceras de las funciones.
#ifndef funciones_h_
#define funciones_h_

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

//Cabeceras
int leerArchivo(char * pathname , int filas, int columnas,float * buffer,int N,int flag);
void suavizado1(int filas, int columnas,float * buffer , float ** suavizados, int N);
void suavizado2(int filas, int columnas,float * buffer , float ** suavizados, int N);
void printBuffer(int filas, int columnas, float * buffer);
int escribirImagen(char * salidaName , int filas, int columnas,float * buffer,int N,int flag);


//fin de directivas
#endif // funciones_h_
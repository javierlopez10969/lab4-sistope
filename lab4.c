//Autores: Javier López - Felipe Sepulveda
/*
• -I filename : especifica el nombre de la imagen de entrada
• -F filename : especifica el nombre de la imagen final con el metodo 1
• -S filename : especifica el nombre de la imagen final con el metodo 2
• -M numero : especifica el numero de filas de la imagen
• -N numero : especifica el numero de columnas de la imagen
• -b: bandera que indica si se entregan resultados por consola. Si se utiliza este flag debe imprimir los
tiempos de ejecucion para cada metodo.
./lab4 -I cameraman_256x256.raw -F imagen1F.raw -S imagen1S.raw -M 256 -N 256 -b
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "funciones.h"
#include "funciones.c"


// ### SECCIÓN DE MAIN ###
int main(int argc, char **argv){
    //variables que se utilizaran para almacenar datos
    char *nombreImagen = NULL;
    char *imagenSalida1 = NULL;
    char *imagenSalida2 = NULL;
    int filas, columnas, bandera, opterr;
    float *buffer,*bufferZoom, *bufferSuavizado,*bufferDelineado;
    char c;
    filas, columnas, bandera, opterr= 0;
    opterr += 1;
    //el siguiente ciclo se utiliza para recibir los parametros de entrada usando getopt
    while ((c = getopt(argc, argv, "I:F:S:M:N:b")) != -1)
        switch (c){
        case 'I':
            nombreImagen = optarg;
            break;
        case 'F':
            imagenSalida1 = optarg;
            break;
        case 'S':
            imagenSalida2 = optarg;
            break;
        case 'M':
            sscanf(optarg, "%d", &filas);
            break;
        case 'N':
            sscanf(optarg, "%d", &columnas);
            break;
        case 'b':
            bandera = 1;
            break;
        case '?':
            if (optopt == 'b'){
                bandera = 1;
                break;}
            if (optopt == 'c'){
                fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);}

            else if (isprint(optopt))
                fprintf(stderr, "Opcion desconocida `-%c'.\n", optopt);
            else
                fprintf(stderr,
                        "Opcion con caracter desconocido `\\x%x'.\n",
                        optopt);
            return 1;

        default:
            abort();
        }
    //notificar fallos en los parametros de entrada
    if (nombreImagen == NULL || imagenSalida1 == NULL || imagenSalida2 == NULL ||
        filas == 0 || columnas == 0){
        printf("Faltan entradas para poder ejecutar el programa \n");
    }
    else if (columnas != filas){
        printf("Cantidad de filas y columnas es distinto \n");
    }
    else{
        //Correcto camino
        if (bandera != 0)
            printf("Nombre imagen de entrada : %s \n Imagen salida  1: %s \n Imagen salida  2: %s \n   filas : %d \n columnas : %d \n bandera : %d",
            nombreImagen, imagenSalida1,imagenSalida2, filas, columnas, bandera);
    }
    return 0;
}

// EJEMPLO DE USO : la
//./lab4 -I cameraman_256x256.raw -F imagen1F.raw -S imagen1S.raw -M 256 -N 256 -b

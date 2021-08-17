#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <pthread.h>
#include "funciones.h"

//Entradas: recibe el nombre de la imagen a leer (char puntero), el numero de filas, columnas, un buffer para almacenar el contenido de la imagen,
//y la cantidad de bytes necesarios para la imagen.
//Funcionamiento: abre la imagen y comprueba si esto se hizo correctamente, en caso contrario se muestra un error en pantalla, poosteriormente, se lee el contenido de la imagen y
//si la cantidad de bits difiere,significa que hubo un error en la entrega de filas y columnas, se cierra el archivo y termina la funcion
//Salidas: un entero que muestra el termino de la funcion.
int leerArchivo(char * pathname , int filas, int columnas,float * buffer,int N,int flag){
    int f1;
    if ((f1 = open(pathname,O_RDONLY)) == -1) {
        printf("Error al abrir archivo\n");
        exit(-1);
    }

    int nbytes;
    if ((nbytes = read(f1, buffer, N)) != N) {
        printf("Tamaño incorrercto de filas y columnas\n");
        exit(-1);
    }
    close(f1);
    return 1;
}

//Entradas: Numero de filas, columnas y un buffer con el contenido de la imagen
//Funcionamiento: recorre el buffer lineal de tamaño "columnas * filas", para posteriormente mostrar el contenido de este separandolo por filas
void printBuffer(int filas, int columnas, float * buffer){
    int i = 1;
    int k = 0;
    for(int j = 0 ; j < columnas *filas; j++){
      printf("%f, ",buffer[j]);
      k++;
      if(k == columnas){
          printf("\n\n fila %d \n\n", i);
          k = 0;
          i++;
      }
    }
}

//Entradas: se indica el nombre de salida para la imagen, numero de filas y columnas, un buffer con el contenido de la imagen y la cantidad de bytes necesarias para esta.
//Funcionamiento: se abre la imagen para que esta posteriormente pueda ser escrita, en caso de que existe un error este se especifica y se muestra en pantalla.
//Salidas: retorna un entero el cual indica que la funcion termino.
int escribirImagen(char * salidaName , int filas, int columnas,float * buffer,int N,int flag){

    int f2;
    if ((f2 = open(salidaName, O_WRONLY | O_CREAT , 0644)) == -1) {
        printf("Error al abrir archivo\n");
        exit(-1);
    }
    
    else if (f2  == 1) {
        printf("Se abrio correctamente\n");
        exit(-1);
    }

    if(write(f2, buffer, N) != -1){
        if (flag==1)        
            printf("Se ha escrito corectamente el archivo : %s\n" , salidaName);
    } 
    close(f2);
    
    return 1;

}

//Entradas: Numero de filas y columnas, el buffer original con el contenido de la imagen, un buffer el cual se encuentra vacio (NULL);
//y N que corresponde a la cantidad de bytes (filas * columnas * 4)
//Funcionamiento: realiza el proceso de suavizado, el cual consiste en revisa cada posicion posible para los bytes,
//dependiendo de esta calcula la media aritmetica de su vecindario y añade esto a un nuevo buffer del mismo tamaño.
//Salidas: Nuevo buffer el cual corresponde a la imagen posterior a su proceso de suavizado.
void suavizado1(int filas, int columnas,float * buffer , float ** suavizados, int N){
    float * newBuffer = (float*)malloc(sizeof(float)*(columnas*filas*4));
    //Iterador que recorre el buffer antiguo y el nuevo
    int i = 0 ;
    //Iterador que va contando en que fila va
    int n = 0;
    float promedio = 0 ;
    while (i < filas*columnas){
        //printf(" %d -", i);
        //Si es el primer valor primera esquina superior izquierda
        if (i == 0){
            promedio = (buffer[i+1] + buffer[i+columnas] + buffer[i+columnas+1])/3;
            newBuffer [i] = promedio;
        }
        //Si el iterador es la segunda esquina, esquina superior derecha
        else if(i == columnas -1){
            promedio = (buffer[i-1] + buffer[i+ columnas] + buffer[i+ columnas -1])/3;
            newBuffer [i] = promedio;
        }
        //esquina inferior izquerda de la imagen
        else if(i == (columnas * filas) - columnas){
            promedio = (buffer[i+1] + buffer[i-columnas] + buffer[i-columnas+1]) / 3;
            newBuffer [i] = promedio;
        }
        //esquina inferior derecha de la imagen
        else if(i == ((columnas * filas) - 1)){
            promedio = (buffer[i-1] + buffer[i-columnas] + buffer[i-columnas-1]) / 3;
            newBuffer [i] = promedio;
            
        }
        //Caso orilla superior
        else if (i != 0 && i < columnas-1){
            promedio = (buffer[i-1] +buffer[i+1] + buffer[i+columnas] + buffer[i+columnas-1] + buffer[i+columnas+1] ) / 5;
            newBuffer [i] = promedio;
        }
        //Caso orilla izquierda
        else if (i != 0 && i != (columnas * filas) - columnas && i%columnas == 0){
            promedio = (buffer[i+1] + buffer[i-columnas] + buffer[i-columnas+1] + buffer[i+columnas] + buffer[i+columnas+1]) / 5;
            newBuffer [i] = promedio;
        }
        //Caso orilla derecha
        else if(i != (columnas * filas)-1 && i != columnas -1 && i%(columnas-1) == 0 ){
            promedio = (buffer[i-1] + buffer[i-columnas] + buffer[i-columnas-1] + buffer[i+columnas] + buffer[i+columnas-1]) / 5;
            newBuffer [i] = promedio;
        }
        //Caso orilla inferior
        else if(i > (columnas * filas) - columnas && i < (columnas * filas) - 1 ){
            promedio = (buffer[i-1] + buffer[i+1] + buffer[i-columnas] + buffer[i-columnas-1] + buffer[i-columnas+1] ) / 5;
            newBuffer [i] = promedio;
        }
        //Caso de al medio con 6 vecinos.
        else{
            promedio = (buffer[i+1] + buffer[i-1] + buffer[i-columnas] + buffer[i-columnas-1] + buffer[i-columnas+1] + buffer[i+columnas] + buffer[i+columnas-1] + buffer[i+columnas + 1]) / 6 ; 
            newBuffer [i] = promedio;
        }
        //Casos borde para cortar el while
        //Filas par
        if (filas != 0 && columnas != 0 && filas%2 == 0 && columnas%2 == 0){
            if (i== (filas*columnas -1)-(filas-1)){
                break;
            }
            
        }else{//Filas impar
            if (i == filas*columnas-1){
                break;
            }
        }
        //Casos para iterar el i
        //Caso fila par : aumentar
        if (n==0 || n%2 ==0){
            //Caso ultima columna hacia la derecha
            if (i+1 == (2*n) + columnas -1){
                //Pasamos a la siguiente fila
                i = i +filas;
                n++;
            }else{
                i ++;
            }
        }
        //Caso fila impar : disminuir
        else{
            if (i == columnas * n){
                //Pasamos a la siguiente fila
                i = i+filas;
                n++;
            }else{
                i--;
            }
        }
    }
    *suavizados = newBuffer;
}



//Entradas: Numero de filas y columnas, el buffer original con el contenido de la imagen, un buffer el cual se encuentra vacio (NULL);
//y N que corresponde a la cantidad de bytes (filas * columnas * 4)
//Funcionamiento: realiza el proceso de suavizado, el cual consiste en revisa cada posicion posible para los bytes,
//dependiendo de esta calcula la media aritmetica de su vecindario y añade esto a un nuevo buffer del mismo tamaño.
//Salidas: Nuevo buffer el cual corresponde a la imagen posterior a su proceso de suavizado.
void suavizado2(int filas, int columnas,float * buffer , float ** suavizados, int N){
    float * newBuffer = (float*)malloc(sizeof(float)*(columnas*filas*4));
    //Iterador que recorre el buffer antiguo y el nuevo
    int i = 0 ;
    //Iterador que va contando en que columna
    int n = 0;
    //Contandor que va viendo cuantas filas llevamos
    int f = 1;
    float promedio = 0 ;
    while (i < filas*columnas || n > filas){
        //printf(" %d -", i);
        //Si es el primer valor primera esquina superior izquierda
        if (i == 0){
            promedio = (buffer[i+1] + buffer[i+columnas] + buffer[i+columnas+1])/3;
            newBuffer [i] = promedio;
        }
        //Si el iterador es la segunda esquina, esquina superior derecha
        else if(i == columnas -1){
            promedio = (buffer[i-1] + buffer[i+ columnas] + buffer[i+ columnas -1])/3;
            newBuffer [i] = promedio;
        }
        //esquina inferior izquerda de la imagen
        else if(i == (columnas * filas) - columnas){
            promedio = (buffer[i+1] + buffer[i-columnas] + buffer[i-columnas+1]) / 3;
            newBuffer [i] = promedio;
        }
        //esquina inferior derecha de la imagen
        else if(i == ((columnas * filas) - 1)){
            promedio = (buffer[i-1] + buffer[i-columnas] + buffer[i-columnas-1]) / 3;
            newBuffer [i] = promedio;
            
        }
        //Caso orilla superior
        else if (i != 0 && i < columnas-1){
            promedio = (buffer[i-1] +buffer[i+1] + buffer[i+columnas] + buffer[i+columnas-1] + buffer[i+columnas+1] ) / 5;
            newBuffer [i] = promedio;
        }
        //Caso orilla izquierda
        else if (i != 0 && i != (columnas * filas) - columnas && i%columnas == 0){
            promedio = (buffer[i+1] + buffer[i-columnas] + buffer[i-columnas+1] + buffer[i+columnas] + buffer[i+columnas+1]) / 5;
            newBuffer [i] = promedio;
        }
        //Caso orilla derecha
        else if(i != (columnas * filas)-1 && i != columnas -1 && i%(columnas-1) == 0 ){
            promedio = (buffer[i-1] + buffer[i-columnas] + buffer[i-columnas-1] + buffer[i+columnas] + buffer[i+columnas-1]) / 5;
            newBuffer [i] = promedio;
        }
        //Caso orilla inferior
        else if(i > (columnas * filas) - columnas && i < (columnas * filas) - 1 ){
            promedio = (buffer[i-1] + buffer[i+1] + buffer[i-columnas] + buffer[i-columnas-1] + buffer[i-columnas+1] ) / 5;
            newBuffer [i] = promedio;
        }
        //Caso de al medio con 6 vecinos.
        else{
            promedio = (buffer[i+1] + buffer[i-1] + buffer[i-columnas] + buffer[i-columnas-1] + buffer[i-columnas+1] + buffer[i+columnas] + buffer[i+columnas-1] + buffer[i+columnas + 1]) / 6 ; 
            newBuffer [i] = promedio;
        }

        //Casos para iterar el i
        //Cambiar la columna
        if (f == filas-1){
            f = 0;
            n++;
            i = n;
        }
        //aumentar la fila
        else{
            i = i + filas;
            f ++;
        }
    }
    *suavizados = newBuffer;
}

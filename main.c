#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "libreria.h"

#define nStruct 50
/*
Alumno: Francisco Coronel
Fecha de entrega:10/11/2022
Archivos del programa:"libreria.c","libreria.h","main.c","corredores_v1.csv","corredores.dat","competidores_bajas_<fecha>.xyz"
Resumen: El programa presenta un título orientativo y un menú de once opciones a las cuales se accede ingresando el número correspondiente, que ejecutan funciones que forman parte de la libreria del proyecto
         ciertas opciones, como las operaciones sobre los archivos binarios requieren que primero se ejecuten las funciones que crean dicho archivo.
         Obviar este paso otorgará errores o resultados incorrectos.
         No logré implementar una función para modificar los datos de un competidor.
         Tampoco que la función de alta de competidores posicione correctamente los nuevos participantes, es decir, si se ingresa una persona en el orden 32 y luego una en el orden 31, al listarlos aparece primero el 32 y luego el 31 al final del listado.
*/

int main()
{
    int opcion;
    FILE * archBinario=NULL;
    FILE * archCsv=NULL;
    FILE * archXYZ=NULL;
    time_t hora;        //Struct propio de la función time.h que contiene enteros, caracteres y cadenas relacionados al tiempo y las fechas
    struct tm *fecha;
    char nomArch[50];

    time(&hora);
    fecha=localtime(&hora);

    strftime(nomArch,sizeof(nomArch),"competidores_bajas[%d-%m-%y].dat",fecha);//Con la función propia de la libreria time.h se concatenan los contenidos del puntero a struct *fecha a la variable nomArch. Los identificadores de formato pertenecen a la libreria e indican dia,mes y año.

    do
    {
        opcion=menu();
        switch(opcion)
        {
        case 1:
            //system("clear");
            listarTxt(archCsv/*,competidores*/);
            getchar();
            system("clear");
            break;
        case 2:
            crearBin(archBinario);
            getchar();
            system("clear");
            break;
        case 3:
            migrarDatos(archBinario,archCsv/*,competidores*/);
            getchar();
            system("clear");
            break;
        case 4:
            system("clear");
            listarDat(archBinario/*,competidores*/);
            getchar();
            break;
        case 5:
            altaCompetidor(archBinario);
            break;
        case 6:
            buscarCompetidor(archBinario);
            getchar();
            break;
        case 7:
            bajaLogica(archBinario);
            getchar();
            break;
        case 8:
            bajaFisica(archBinario,archXYZ,nomArch);
            getchar();
            break;
        case 9:
            listarXYZ(archXYZ,nomArch);
            getchar();
            break;
        }
    }
    while(opcion!=0);
    printf("\nFin del programa.\n");
    return 0;
}

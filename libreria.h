#ifndef _LIBRERIA_H_
#define _LIBRERIA_H_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define nStruct 50

struct competidor
{
    int orden;
    int participante;
    int dia;
    char mes[4];
    int anio;
    int edad;
    char pais[4];
    float tiempo;
    int activo;
};


int menu();
void listarTxt(FILE * aCsv/*,struct competidor comp[]*/);
void crearBin(FILE * aBin);
void migrarDatos(FILE * aBin, FILE * aCsv);
int menuListar();
void listarDat(FILE * aBin);
void altaCompetidor(FILE * aBin);
void buscarCompetidor(FILE * aBin);
void bajaLogica(FILE * aBin);
void bajaFisica(FILE * aBin,FILE * XYZ,char * nomArch);
void listarXYZ(FILE * XYZ,char * nomArch);

#endif

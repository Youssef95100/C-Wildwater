#ifndef STRUCTURE_H 
#define STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char* id;
    long conso;
    long capa;
} Usine;


typedef struct AVL{
    Usine* data;
    struct AVL* fg;
    struct AVL* fd;
    int equilibre;
} AVL;


#endif
#ifndef STRUCTURE_H 
#define STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

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
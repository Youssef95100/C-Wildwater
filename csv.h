#ifndef CSV_H
#define CSV_H

#include "structure.h"
#include "avl.h"
#include <string.h>

#define TAILLE_LIGNE 512

static void nettoyerFinLigne(char* s);
AVL* lireCSV(const char* nomFichier);

#endif
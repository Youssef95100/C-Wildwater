#ifndef AVL_H
#define AVL_H


#include "structure.h"

Usine* creerUsine(char* id, long conso, long capa);
AVL* creerAVL(Usine* u);

void libererAVL(AVL* noeud);

AVL* rotationGauche(AVL* a);
AVL* rotationDroite(AVL* a);
AVL* doubleRotationGauche(AVL* a);
AVL* doubleRotationDroite(AVL* a);

Usine* rechercherAVL(AVL* a, char* id);
AVL* insererAVL(AVL* a, Usine* u, int* h);

#endif 

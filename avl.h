/**
 *
 * Ce module expose les primitives nécessaires à la manipulation des stations
 * stockées sous forme d'arbre AVL. Il définit les opérations d'insertion avec
 * équilibrage automatique (garantissant une complexité logarithmique), de recherche,
 * de rotation (simples et doubles) ainsi que les fonctions de parcours et de
 * libération mémoire.
 */

 #ifndef AVL_H
 #define AVL_H
 
 #include <stdio.h>
 #include "station.h"
 
 int maxInt(int a, int b);
 int hauteur(pStation a);
 int equilibre(pStation a);
 
 pStation creerStation(char* code, double cap);
 pStation inserer(pStation a, char* code, double cap, double flux);
 pStation rechercher(pStation a, char* code);
 
 pStation rotationDroite(pStation y);
 pStation rotationGauche(pStation x);
 pStation doubleRotationGD(pStation a);
 pStation doubleRotationDG(pStation a);
 
 void infixe(pStation a, FILE* fs);
 void libererAVL(pStation a);
 
 #endif
 
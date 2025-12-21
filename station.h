/*
 * Ce fichier définit les types de base utilisés par tous les modules.
 * La particularité de cette architecture est la structure `Station`, qui est hybride :
 * elle agit simultanément comme :
 * 1. Un Nœud d'Arbre AVL (pour le tri et la recherche rapide par ID).
 * 2. Un Sommet de Graphe (pour la modélisation du réseau physique via liste d'adjacence).
 */

 #ifndef STATION_H
 #define STATION_H
 
 #include <stdio.h>
 
 // Prédéclaration pour que Tuyau puisse connaître Station
 struct Station;
 
 typedef struct Tuyau {
     struct Station* destinataire;
     double fuite_percent;
     struct Tuyau* suivant;
 } Tuyau;
 
 typedef struct Station {
     char id_str[50];
     double capacite;
     double conso;
 
     Tuyau* liste_aval;
 
     int h;
     struct Station* fg;
     struct Station* fd;
 } Station;
 
 typedef Station* pStation;
 
 // Prototype manquant ajouté ici :
 void libererListeAval(Tuyau* t);
 
 #endif
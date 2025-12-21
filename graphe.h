/*
 * Ce module définit les opérations sur la structure de graphe orienté qui représente
 * le réseau de distribution d'eau. Il fournit les fonctions pour :
 * 1. Construire la topologie (création des arcs/tuyaux entre les stations).
 * 2. Effectuer les calculs hydrauliques (propagation des volumes et cumul des fuites)
 * via un parcours récursif du graphe.
 */

 #ifndef GRAPHE_H
 #define GRAPHE_H
 
 #include "station.h"
 
 // Ajoute une connexion orientée entre deux stations
 void ajouterConnexion(pStation parent, pStation enfant, double fuite);
 
 // Calcule récursivement les fuites en aval d'une station
 double calculerFuitesAval(pStation s);
 
 #endif
/*
 * Ce module implémente la structure de graphe orienté (via listes d'adjacence) 
 * pour relier les stations entre elles. Il contient également l'algorithme 
 * récursif principal qui simule le passage de l'eau et calcule les pertes 
 * cumulées sur l'ensemble du réseau aval.
 */

 #include <stdlib.h>
 #include "graphe.h"
 
 void ajouterConnexion(pStation parent, pStation enfant, double fuite) {
     if (parent == NULL || enfant == NULL) return;
 
     Tuyau* nouv = malloc(sizeof(Tuyau));
     if (nouv == NULL) exit(1);
 
     nouv->destinataire = enfant;
     nouv->fuite_percent = fuite;
     nouv->suivant = parent->liste_aval;
     parent->liste_aval = nouv;
 }
 
 double calculerFuitesAval(pStation s) {
     if (s == NULL) return 0;
     
     // Compter le nombre de sorties
     int nb_enfants = 0;
     Tuyau* t = s->liste_aval;
     while (t != NULL) {
         nb_enfants++;
         t = t->suivant;
     }
 
     if (nb_enfants == 0) return 0;
 
     // Répartition équitable du volume sortant
     double volume_par_enfant = s->conso / nb_enfants;
     double fuites_totales = 0;
     
     t = s->liste_aval;
     while (t != NULL) {
         // Fuite sur le tronçon actuel
         double perte_tuyau = volume_par_enfant * (t->fuite_percent / 100.0);
         
         if (t->destinataire != NULL) {
             // Transmission du volume restant à la station suivante
             t->destinataire->conso += (volume_par_enfant - perte_tuyau);
             
             // Appel récursif pour continuer le trajet
             fuites_totales += perte_tuyau + calculerFuitesAval(t->destinataire);
         }
         
         t = t->suivant;
     }
     
     return fuites_totales;
 }
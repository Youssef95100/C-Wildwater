/*
 * Ce module contient les fonctions utilitaires liées directement à l'entité Station,
 * en particulier la libération des ressources dynamiques associées (listes chaînées).
 */

 #include <stdlib.h>
 #include "station.h"
 
 void libererListeAval(Tuyau* t) {
     while (t != NULL) {
         Tuyau* tmp = t;
         t = t->suivant;
         free(tmp);
     }
 }
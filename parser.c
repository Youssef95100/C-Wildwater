/*
 * Ce module est responsable de la lecture du fichier CSV d'entrée. Il interprète
 * chaque ligne pour construire simultanément :
 * 1. L'index des stations (via l'AVL) pour un accès rapide.
 * 2. La topologie du réseau (via les connexions du Graphe) pour la simulation.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "parser.h"
 #include "graphe.h"
 
 void chargerDonnees(char* chemin, pStation* racine) {
     FILE* f = fopen(chemin, "r");
     if (f == NULL) exit(2);
 
     char buf1[256];
     char buf2[256];
     double val1 = 0.0;
     double val2 = 0.0;
     char ligne[1024];
 
     while (fgets(ligne, 1024, f)) {
         int n = sscanf(ligne, "%[^;];%[^;];%lf;%lf", buf1, buf2, &val1, &val2);
 
         if (n == 4) {
             *racine = inserer(*racine, buf1, 0, 0);
             pStation src = rechercher(*racine, buf1);
 
             *racine = inserer(*racine, buf2, 0, 0);
             pStation dest = rechercher(*racine, buf2);
 
             ajouterConnexion(src, dest, val2);
 
             if (val1 > 0) {
                 dest->conso += val1;
                 src->conso += val1;
             }
         } else {
             double c, k;
             if (sscanf(ligne, "%[^;];%lf;%lf", buf1, &c, &k) == 3) {
                 *racine = inserer(*racine, buf1, c, k);
             }
         }
     }
 
     fclose(f);
 }
 
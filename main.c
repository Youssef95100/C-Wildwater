/*
 * Ce module organise l'ensemble du flux de traitement :
 * 1. Analyse des arguments de la ligne de commande pour déterminer le mode (Histo ou Leaks).
 * 2. Appel au Parser pour charger les données CSV en mémoire (construction AVL + Graphe).
 * 3. Exécution de la logique métier appropriée (Calcul de fuites ou Export trié).
 * 4. Génération du rapport de sortie (stats.csv) et nettoyage mémoire.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "avl.h"
 #include "parser.h"
 #include "graphe.h"
 
 int main(int argc, char** argv) {
     // Vérification basique des arguments
     if (argc < 2) return 1;
 
     pStation arbre = NULL;
     char* fichier_in = argv[1];
     // Si un 3ème argument est présent, c'est l'ID cible (Mode Leaks)
     char* target_id = (argc >= 3) ? argv[2] : NULL;
 
     // 1. Chargement des données
     chargerDonnees(fichier_in, &arbre);
 
     FILE* f_out = fopen("stats.csv", "w");
     if (f_out == NULL) {
         libererAVL(arbre);
         return 1;
     }
 
     // 2. Traitement selon le mode
     if (target_id != NULL) {
         // --- MODE LEAKS ---
         pStation s = rechercher(arbre, target_id);
         if (s != NULL) {
             double total = calculerFuitesAval(s);
             fprintf(f_out, "%s;%.6f\n", target_id, total);
         } else {
             // Station introuvable
             fprintf(f_out, "%s;-1\n", target_id);
         }
     } else {
         // --- MODE HISTO ---
         fprintf(f_out, "Station;Capacite;Consommation\n");
         infixe(arbre, f_out);
     }
 
     // 3. Nettoyage
     fclose(f_out);
     libererAVL(arbre);
 
     return 0;
 }
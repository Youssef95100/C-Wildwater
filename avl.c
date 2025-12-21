/**
 * Ce module gère le stockage, l'insertion, la mise à jour et le tri des stations.
 * Il garantit une complexité de recherche et d'insertion en O(log n) grâce à l'équilibrage
 * dynamique via des rotations. Il inclut également la logique métier d'agrégation
 * des flux (capacité et consommation) lors de l'insertion de doublons.
 */




 #include <stdlib.h>
 #include "avl.h"
 #include "station.h"
 
 int comparerTexte(char* s1, char* s2) {
     int i = 0;
     while (s1[i] != '\0' && s2[i] != '\0') {
         if (s1[i] != s2[i]) {
             return s1[i] - s2[i];
         }
         i++;
     }
     return s1[i] - s2[i];
 }
 
 void copierTexte(char* dest, char* src) {
     int i = 0;
     while (src[i] != '\0') {
         dest[i] = src[i];
         i++;
     }
     dest[i] = '\0';
 }
 
 int maxInt(int a, int b) {
     return (a > b) ? a : b;
 }
 
 int hauteur(pStation a) {
     if (a == NULL) return 0;
     return a->h;
 }
 
 int equilibre(pStation a) {
     if (a == NULL) return 0;
     return hauteur(a->fg) - hauteur(a->fd);
 }
 
 pStation creerStation(char* code, double cap) {
     pStation nouv = malloc(sizeof(Station));
     if (nouv == NULL) exit(1);
 
     copierTexte(nouv->id_str, code);
     nouv->capacite = cap;
     nouv->conso = 0;
     nouv->liste_aval = NULL;
     nouv->h = 1;
     nouv->fg = NULL;
     nouv->fd = NULL;
 
     return nouv;
 }
 
 pStation inserer(pStation a, char* code, double cap, double flux) {
     if (a == NULL) {
         pStation n = creerStation(code, cap);
         n->conso = flux;
         return n;
     }
 
     int cmp = comparerTexte(code, a->id_str);
 
     if (cmp < 0) {
         a->fg = inserer(a->fg, code, cap, flux);
     } else if (cmp > 0) {
         a->fd = inserer(a->fd, code, cap, flux);
     } else {
         if (cap > 0) a->capacite += cap;
         a->conso += flux;
         return a;
     }
 
     a->h = 1 + maxInt(hauteur(a->fg), hauteur(a->fd));
     int eq = equilibre(a);
 
     if (eq > 1 && comparerTexte(code, a->fg->id_str) < 0)
         return rotationDroite(a);
 
     if (eq < -1 && comparerTexte(code, a->fd->id_str) > 0)
         return rotationGauche(a);
 
     if (eq > 1 && comparerTexte(code, a->fg->id_str) > 0)
         return doubleRotationGD(a);
 
     if (eq < -1 && comparerTexte(code, a->fd->id_str) < 0)
         return doubleRotationDG(a);
 
     return a;
 }
 
 pStation rechercher(pStation a, char* code) {
     if (a == NULL) return NULL;
 
     int cmp = comparerTexte(code, a->id_str);
 
     if (cmp == 0) return a;
     if (cmp < 0) return rechercher(a->fg, code);
     return rechercher(a->fd, code);
 }
 
 pStation rotationDroite(pStation y) {
     pStation x = y->fg;
     pStation T2 = x->fd;
 
     x->fd = y;
     y->fg = T2;
 
     y->h = maxInt(hauteur(y->fg), hauteur(y->fd)) + 1;
     x->h = maxInt(hauteur(x->fg), hauteur(x->fd)) + 1;
 
     return x;
 }
 
 pStation rotationGauche(pStation x) {
     pStation y = x->fd;
     pStation T2 = y->fg;
 
     y->fg = x;
     x->fd = T2;
 
     x->h = maxInt(hauteur(x->fg), hauteur(x->fd)) + 1;
     y->h = maxInt(hauteur(y->fg), hauteur(y->fd)) + 1;
 
     return y;
 }
 
 pStation doubleRotationGD(pStation a) {
     a->fg = rotationGauche(a->fg);
     return rotationDroite(a);
 }
 
 pStation doubleRotationDG(pStation a) {
     a->fd = rotationDroite(a->fd);
     return rotationGauche(a);
 }
 
 void infixe(pStation a, FILE* fs) {
     if (a == NULL) return;
     infixe(a->fg, fs);
     fprintf(fs, "%s;%.6f;%.6f\n", a->id_str, a->capacite, a->conso);
     infixe(a->fd, fs);
 }
 
 void libererAVL(pStation a) {
     if (a == NULL) return;
     libererAVL(a->fg);
     libererAVL(a->fd);
     libererListeAval(a->liste_aval);
     free(a);
 }
 
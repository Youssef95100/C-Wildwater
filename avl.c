#include "structure.h"
#include <string.h>

Usine* creerUsine(char* id, long conso, long capa){
    Usine* u = malloc(sizeof(Usine));
    if (u == NULL){
        exit(1);
    }
    u->id = malloc(strlen(id) + 1); // +1 pour le caractère de fin \0
    if (u->id == NULL){
        exit(1);
    }
    strcpy(u->id, id);
    u->capa = capa;
    u->conso = conso;
    return u;
}

AVL* creerAVL(Usine* u){
    AVL* noeud = malloc(sizeof(AVL));
    if (noeud == NULL){
        exit(1);
    } 
    noeud->data = u;
    noeud->fg = NULL;
    noeud->fd = NULL;
    noeud->equilibre = 0;
    return noeud;
}

void libererAVL(AVL* noeud) {
    if (noeud == NULL) {
        return;
    }

   
    libererAVL(noeud->fg);
    libererAVL(noeud->fd);

    if (noeud->data != NULL) {

        if (noeud->data->id != NULL) {
            free(noeud->data->id);
        }
        free(noeud->data);
    }

    free(noeud);
}

AVL* rotationGauche(AVL* a) {
    AVL* pivot = a->fd;
    int eq_a = a->equilibre;
    int eq_p = pivot->equilibre;

    a->fd = pivot->fg;
    pivot->fg = a;

    a->equilibre = eq_a - 1 - max(eq_p, 0);
    pivot->equilibre = eq_p - 1 + min(a->equilibre, 0);

    return pivot;
}

AVL* rotationDroite(AVL* a) {
    AVL* pivot = a->fg;
    int eq_a = a->equilibre;
    int eq_p = pivot->equilibre;

    a->fg = pivot->fd;
    pivot->fd = a;

    a->equilibre = eq_a + 1 - min(eq_p, 0);
    pivot->equilibre = eq_p + 1 + max(a->equilibre, 0);

    return pivot;
}

AVL* doubleRotationGauche(AVL* a) {
    a->fd = rotationDroite(a->fd);
    return rotationGauche(a);
}

AVL* doubleRotationDroite(AVL* a) {
    a->fg = rotationGauche(a->fg);
    return rotationDroite(a);
}

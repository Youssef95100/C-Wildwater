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

Usine* rechercherAVL(AVL* a, char* id){
    if (a == NULL){
        return NULL;
    }

    int cmp = strcmp(id, a->data->id);

    if (cmp == 0){
        return a->data;
    }
    else if (cmp < 0){
        return rechercherAVL(a->fg, id);
    }
    else{
        return rechercherAVL(a->fd, id);
    }
}

AVL* insererAVL(AVL* a, Usine* u, int* h){
    if (a == NULL){
        *h = 1;
        return creerAVL(u);
    }

    int cmp = strcmp(u->id, a->data->id);

    if (cmp == 0){
        a->data->conso += u->conso;
        a->data->capa  += u->capa;
        *h = 0;
        return a;
    }

    if (cmp < 0){
        a->fg = insererAVL(a->fg, u, h);
        if (*h){
            a->equilibre++;
            if (a->equilibre == 0){
                *h = 0;
            }
            else if (a->equilibre == 2){
                if (a->fg->equilibre >= 0){
                    a = rotationDroite(a);
                }
                else{
                    a = doubleRotationDroite(a);
                }
                *h = 0;
            }
        }
    }
    else{
        a->fd = insererAVL(a->fd, u, h);
        if (*h){
            a->equilibre--;
            if (a->equilibre == 0){
                *h = 0;
            }
            else if (a->equilibre == -2){
                if (a->fd->equilibre <= 0){
                    a = rotationGauche(a);
                }
                else{
                    a = doubleRotationGauche(a);
                }
                *h = 0;
            }
        }
    }

    return a;
}
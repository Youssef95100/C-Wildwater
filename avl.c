#include 'structure.h'


Usine* creerUsine(char* id, long conso, long capa){
    Usine* u = malloc(sizeof(Usine));
    if (u == NULL){
        exit(-1);
    }
    u->id = malloc(strlen(id) + 1); // +1 pour le caractère de fin \0
    strcpy(u->id, id)
    u->capa = capa;
    u->conso = conso;
    return u;
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
#include "csv.h"

static void nettoyerFinLigne(char* s){
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n'){
        s[len - 1] = '\0';
    }
}

AVL* lireCSV(const char* nomFichier){
    FILE* f = fopen(nomFichier, "r");
    if (f == NULL){
        return NULL;
    }

    AVL* racine = NULL;
    char ligne[TAILLE_LIGNE];

    while (fgets(ligne, TAILLE_LIGNE, f) != NULL){
        nettoyerFinLigne(ligne);

        char* col1 = strtok(ligne, ";");
        char* col2 = strtok(NULL, ";");
        char* col3 = strtok(NULL, ";");
        char* col4 = strtok(NULL, ";");
        char* col5 = strtok(NULL, ";");

        if (col2 == NULL){
            continue;
        }


        if (col3 != NULL && strcmp(col3, "-") == 0 && col4 != NULL && strcmp(col4, "-") != 0){
            long capa = atol(col4);

            Usine* u = creerUsine(col2, 0, capa);
            int h = 0;
            racine = insererAVL(racine, u, &h);
        }

 
        else if (col3 != NULL && strstr(col2, "Spring") != NULL && strstr(col3, "Facility") != NULL){
            long volume = atol(col4);

            Usine* u = creerUsine(col3, volume, 0);
            int h = 0;
            racine = insererAVL(racine, u, &h);
        }
    }

    fclose(f);
    return racine;
}

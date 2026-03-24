#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/color.h"

#include "include/noeud.h"
#include "include/liste_noeud.h"

#include "instruction/print.h"


int main(int argc, char* argv[]){
    noeud* noeud_racine;
    noeud_racine = malloc(sizeof(noeud));
    if (noeud_racine == NULL) {
        free(noeud_racine);
        return -1;
    }
    
    noeud_racine->est_dossier = 1;

    char* param = argv[1];
    if (param == NULL) {
        printf("erreur dans les arguments...\n");
        free(noeud_racine);
        return -1;
    }

    if (strncmp(param, "print", sizeof(param)-1) == 0) {
        print();
        free(noeud_racine);
        return 0;
    } 
    else {
        printf(RED "instruction [ %s ] non-implémentée ...\n" reset, param);
        free(noeud_racine);
        return -1;
    }
}
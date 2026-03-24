#include <stdio.h>
#include <stdlib.h>

#include "include/noeud.h"
#include "include/liste_noeud.h"

#include "instruction/print.h"

int main(){
    noeud* noeud_racine;
    noeud_racine = malloc(sizeof(noeud));
    if (noeud_racine == NULL) return -1;


    noeud_racine->est_dossier = 1;

    if (noeud_racine->est_dossier == 1) {
        printf("le noeud est un dossier\n");
    }
    else {
        printf("le noeud n'est pas un dossier\n");
    }

    print();

    return 0;
}
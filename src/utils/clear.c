#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/noeud.h"
#include "include/liste_noeud.h"

int clear(noeud* noeud) {
    if (noeud == NULL) {
        return 1;
    }
    liste_noeud* fils_actuel = noeud->fils;
    while (fils_actuel != NULL) {
        liste_noeud* prochain_fils = fils_actuel->succ;
        clear(fils_actuel->no);
        free(fils_actuel);
        fils_actuel = prochain_fils;
    }
    
    free(noeud);
    return 0;
}
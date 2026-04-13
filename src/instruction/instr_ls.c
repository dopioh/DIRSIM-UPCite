#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/noeud.h"
#include "../include/liste_noeud.h"
#include "../include/color.h"

#include "instr_ls.h"

int instr_ls(contexte* ctx) {
    liste_noeud* ptr = ctx->noeud_courant->fils;

    if (ptr == NULL) printf(BLK "(vide)" reset);
    while (ptr != NULL) {
        if (ptr->no->est_dossier == 1) {
            printf(BLU "/%s\t" reset, ptr->no->nom );
        }
        else if (ptr->no->nom[0] == '.') {
            printf(BLK "%s\t" reset, ptr->no->nom);
        }
        else {
            printf("%s\t", ptr->no->nom);
        }
        
        ptr = ptr->succ;
    }
    printf("\n");
    return 0;
}
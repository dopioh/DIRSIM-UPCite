#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/noeud.h"
#include "../include/liste_noeud.h"
#include "../include/color.h"

#include "instr_ls.h"

int instr_ls(contexte* ctx) {
    if (ctx->noeud_courant == ctx->noeud_racine) {
        printf("elements de la racine : \n");
    }
    else {
        printf("elements de %s :", ctx->noeud_courant->nom);
    }

    while (ctx->noeud_courant->fils != NULL) {
        if (ctx->noeud_courant->fils->no->est_dossier == 1) {
            printf(BLU "/%s\t" reset, ctx->noeud_courant->fils->no->nom );
        }
        else if (ctx->noeud_courant->fils->no->nom[0] == '.') {
            printf(BLK "%s\t" reset, ctx->noeud_courant->fils->no->nom);
        }
        else {
            printf("%s\t", ctx->noeud_courant->fils->no->nom);
        }
        
        ctx->noeud_courant->fils = ctx->noeud_courant->fils->succ;
    }
    return 0;
}
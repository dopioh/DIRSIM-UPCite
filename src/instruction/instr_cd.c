#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/noeud.h"
#include "../include/liste_noeud.h"
#include "../include/color.h"

#include "instr_cd.h"

int instr_cd(char* chemin, contexte* ctx) {
    int i = 0;
    int count = 0;
    char* dossiers_parcourus[100]; 

    while (chemin[i]) {
        if (chemin[i] == '/') break;
        else {
            dossiers_parcourus[count] = &chemin[i];
            count++;
            while (chemin[i] && chemin[i] != '/') {
                i++;
            }
            if (chemin[i]) {
                chemin[i] = '\0';
                i++;
            }
        }
    }
    i = 0;
    dossiers_parcourus[count] = NULL;
    
    int trouve = 0;
    while (dossiers_parcourus[i] != NULL) {
        while (ctx->noeud_courant->fils != NULL) {
            if (strcmp(dossiers_parcourus[i], ctx->noeud_courant->fils->no->nom) == 0) {
                ctx->noeud_courant = ctx->noeud_courant->fils->no;
                trouve = 1;
                break;
            }
            ctx->noeud_courant->fils = ctx->noeud_courant->fils->succ;
        }
        i++;
        if (trouve == 0) {
            printf(RED "le chemin \"%s\" n'existe pas" reset, chemin);
            return 1;
        }
    }
    return 0;
}
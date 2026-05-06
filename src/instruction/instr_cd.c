#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/noeud.h"
#include "../include/liste_noeud.h"
#include "../include/color.h"
#include "../include/recherche_noeud.h"

#include "instr_cd.h"

int instr_cd(char* chemin, contexte* ctx) {
    if (ctx == NULL || chemin == NULL) return 1;

    noeud* cible = recherche_noeud(ctx, chemin);
    if (cible == NULL) return 1;
    
    ctx->noeud_courant = cible;
    return 0;
}

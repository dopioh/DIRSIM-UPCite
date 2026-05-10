#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../utils/include/noeud.h"
#include "../utils/include/liste_noeud.h"
#include "../utils/include/color.h"
#include "../utils/include/recherche_noeud.h"
#include "../utils/include/erreur.h"

#include "instr_cd.h"

int instr_cd(char* chemin, contexte* ctx) {
    if (ctx == NULL || chemin == NULL) return ERR_PARAMETRE_INVALIDE;

    noeud* cible = recherche_noeud(ctx, chemin);
    if (cible == NULL) return ERR_CHEMIN_INTROUVABLE;

    ctx->noeud_courant = cible;
    return SUCCESS;
}

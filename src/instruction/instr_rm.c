#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/include/noeud.h"
#include "../utils/include/liste_noeud.h"
#include "../utils/include/recherche_noeud.h"
#include "../utils/include/clear.h"
#include "../utils/include/erreur.h"

#include "instr_rm.h"

int noeud_dans_sous_arbre(noeud* racine, noeud* cible) {
    noeud* courant;

    if (racine == NULL || cible == NULL) return 0;

    courant = cible;
    while (courant != NULL) {
        if (courant == racine) {
            return 1;
        }
        if (courant == courant->pere) {
            break;
        }
        courant = courant->pere;
    }

    return 0;
}

int supprimer_cellule_fils(noeud* parent, noeud* cible) {
    liste_noeud* courant;
    liste_noeud* precedent;

    if (parent == NULL || cible == NULL) return 0;

    precedent = NULL;
    courant = parent->fils;
    while (courant != NULL) {
        if (courant->no == cible) {
            if (precedent == NULL) {
                parent->fils = courant->succ;
            } else {
                precedent->succ = courant->succ;
            }
            free(courant);
            return 1;
        }
        precedent = courant;
        courant = courant->succ;
    }

    return 0;
}

int instr_rm(char* chemin, contexte* ctx) {
    noeud* cible;
    noeud* parent;

    if (ctx == NULL || chemin == NULL || chemin[0] == '\0') {
        return ERR_PARAMETRE_INVALIDE;
    }

    cible = recherche_noeud(ctx, chemin);
    if (cible == NULL) {
        return ERR_CHEMIN_INTROUVABLE;
    }

    if (cible == ctx->noeud_racine) {
        return ERR_PARAMETRE_INVALIDE;
    }

    parent = cible->pere;
    if (parent == NULL) {
        return ERR_PARAMETRE_INVALIDE;
    }

    if (ctx->noeud_courant != NULL && noeud_dans_sous_arbre(cible, ctx->noeud_courant)) {
        return ERR_PARAMETRE_INVALIDE;
    }

    if (supprimer_cellule_fils(parent, cible) == 0) {
        return ERR_CHEMIN_INTROUVABLE;
    }

    clear(cible);
    return SUCCESS;
}

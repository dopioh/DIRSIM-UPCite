#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/include/noeud.h"
#include "../utils/include/liste_noeud.h"
#include "../utils/include/recherche_noeud.h"
#include "../utils/include/erreur.h"

#include "instr_mv.h"

int mv_nom_existant(noeud* parent, char* nom) {
    liste_noeud* ptr;

    if (parent == NULL || nom == NULL) {
        return 0;
    }

    ptr = parent->fils;
    while (ptr != NULL) {
        if (strcmp(ptr->no->nom, nom) == 0) {
            return 1;
        }
        ptr = ptr->succ;
    }

    return 0;
}

int mv_dans_sous_arbre(noeud* racine, noeud* cible) {
    noeud* courant;

    if (racine == NULL || cible == NULL) {
        return 0;
    }

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

int mv_supprimer_cellule_fils(noeud* parent, noeud* cible) {
    liste_noeud* courant;
    liste_noeud* precedent;

    if (parent == NULL || cible == NULL) {
        return 0;
    }

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

int mv_extraire_parent_et_nom(contexte* ctx, char* chem2, noeud** parent_out, char** nom_out) {
    char chemin_parent[512];
    char* dernier_slash;
    size_t longueur_parent;

    if (ctx == NULL || chem2 == NULL || parent_out == NULL || nom_out == NULL) {
        return 0;
    }

    dernier_slash = strrchr(chem2, '/');
    if (dernier_slash == NULL) {
        *parent_out = ctx->noeud_courant;
        *nom_out = chem2;
        return chem2[0] != '\0';
    }

    *nom_out = dernier_slash + 1;
    if ((*nom_out)[0] == '\0') {
        return 0;
    }

    if (dernier_slash == chem2) {
        *parent_out = ctx->noeud_racine;
        return 1;
    }

    longueur_parent = (size_t)(dernier_slash - chem2);
    strncpy(chemin_parent, chem2, longueur_parent);
    chemin_parent[longueur_parent] = '\0';

    *parent_out = recherche_noeud(ctx, chemin_parent);
    return *parent_out != NULL;
}

int instr_mv(char* chem1, char* chem2, contexte* ctx) {
    noeud* source;
    noeud* parent_source;
    noeud* parent_dest;
    char* nom_dest;
    liste_noeud* cellule;

    if (ctx == NULL || chem1 == NULL || chem2 == NULL) {
        return ERR_PARAMETRE_INVALIDE;
    }
    if (chem1[0] == '\0' || chem2[0] == '\0') {
        return ERR_PARAMETRE_INVALIDE;
    }

    source = recherche_noeud(ctx, chem1);
    if (source == NULL) {
        return ERR_CHEMIN_INTROUVABLE;
    }

    if (source == ctx->noeud_racine) {
        return ERR_PARAMETRE_INVALIDE;
    }

    parent_source = source->pere;
    if (parent_source == NULL) {
        return ERR_PARAMETRE_INVALIDE;
    }

    if (!mv_extraire_parent_et_nom(ctx, chem2, &parent_dest, &nom_dest)) {
        return ERR_PARAMETRE_INVALIDE;
    }

    if (parent_dest == NULL || nom_dest == NULL || nom_dest[0] == '\0') {
        return ERR_PARAMETRE_INVALIDE;
    }
    if (parent_dest->est_dossier == 0) {
        return ERR_PARAMETRE_INVALIDE;
    }
    if (mv_nom_existant(parent_dest, nom_dest)) {
        return ERR_ELEMENT_DEJA_EXISTANT;
    }
    if (mv_dans_sous_arbre(source, parent_dest)) {
        return ERR_PARAMETRE_INVALIDE;
    }
    if (ctx->noeud_courant != NULL && mv_dans_sous_arbre(source, ctx->noeud_courant)) {
        return ERR_PARAMETRE_INVALIDE;
    }

    cellule = malloc(sizeof(liste_noeud));
    if (cellule == NULL) {
        return ERR_ALLOCATION_MEMOIRE;
    }

    if (mv_supprimer_cellule_fils(parent_source, source) == 0) {
        free(cellule);
        return ERR_CHEMIN_INTROUVABLE;
    }

    strncpy(source->nom, nom_dest, sizeof(source->nom) - 1);
    source->nom[sizeof(source->nom) - 1] = '\0';
    source->pere = parent_dest;
    source->racine = ctx->noeud_racine;

    cellule->no = source;
    cellule->succ = parent_dest->fils;
    parent_dest->fils = cellule;

    return SUCCESS;
}

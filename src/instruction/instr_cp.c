#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/include/noeud.h"
#include "../utils/include/liste_noeud.h"
#include "../utils/include/recherche_noeud.h"
#include "../utils/include/clear.h"
#include "../utils/include/erreur.h"

#include "instr_cp.h"

noeud* cp_cible(contexte* ctx, char* chemin) {
    if (ctx == NULL) {
        return NULL;
    }
    if (chemin == NULL) {
        return ctx->noeud_courant;
    }
    return recherche_noeud(ctx, chemin);
}

int cp_nom_existant(noeud* parent, char* nom) {
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

int cp_dans_sous_arbre(noeud* racine, noeud* cible) {
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

noeud* cp_copier_recursif(noeud* source, noeud* pere, contexte* ctx, char* nom) {
    noeud* copie;
    liste_noeud* fils_source;
    liste_noeud* cellule;
    noeud* fils_copie;

    if (source == NULL || pere == NULL || ctx == NULL || nom == NULL) {
        return NULL;
    }

    copie = malloc(sizeof(noeud));
    if (copie == NULL) {
        return NULL;
    }

    copie->est_dossier = source->est_dossier;
    strncpy(copie->nom, nom, sizeof(copie->nom) - 1);
    copie->nom[sizeof(copie->nom) - 1] = '\0';
    copie->pere = pere;
    copie->racine = ctx->noeud_racine;
    copie->fils = NULL;

    fils_source = source->fils;
    while (fils_source != NULL) {
        fils_copie = cp_copier_recursif(fils_source->no, copie, ctx, fils_source->no->nom);
        if (fils_copie == NULL) {
            clear(copie);
            return NULL;
        }

        cellule = malloc(sizeof(liste_noeud));
        if (cellule == NULL) {
            clear(copie);
            return NULL;
        }

        cellule->no = fils_copie;
        cellule->succ = copie->fils;
        copie->fils = cellule;
        fils_source = fils_source->succ;
    }

    return copie;
}

int instr_cp(char* chem1, char* chem2, contexte* ctx) {
    noeud* source;
    noeud* parent_dest;
    noeud* copie;
    char* nom_dest;
    char chemin_parent[512];
    char* dernier_slash;
    size_t longueur_parent;
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

    dernier_slash = strrchr(chem2, '/');
    if (dernier_slash == NULL) {
        parent_dest = ctx->noeud_courant;
        nom_dest = chem2;
    }
    else if (dernier_slash == chem2) {
        parent_dest = ctx->noeud_racine;
        nom_dest = dernier_slash + 1;
    }
    else {
        longueur_parent = (size_t)(dernier_slash - chem2);
        strncpy(chemin_parent, chem2, longueur_parent);
        chemin_parent[longueur_parent] = '\0';
        parent_dest = recherche_noeud(ctx, chemin_parent);
        nom_dest = dernier_slash + 1;
    }

    if (parent_dest == NULL || nom_dest == NULL || nom_dest[0] == '\0') {
        return ERR_PARAMETRE_INVALIDE;
    }
    if (parent_dest->est_dossier == 0) {
        return ERR_PARAMETRE_INVALIDE;
    }
    if (cp_nom_existant(parent_dest, nom_dest)) {
        return ERR_ELEMENT_DEJA_EXISTANT;
    }
    if (cp_dans_sous_arbre(source, parent_dest)) {
        return ERR_PARAMETRE_INVALIDE;
    }

    copie = cp_copier_recursif(source, parent_dest, ctx, nom_dest);
    if (copie == NULL) {
        return ERR_ALLOCATION_MEMOIRE;
    }

    cellule = malloc(sizeof(liste_noeud));
    if (cellule == NULL) {
        clear(copie);
        return ERR_ALLOCATION_MEMOIRE;
    }
    cellule->no = copie;
    cellule->succ = parent_dest->fils;
    parent_dest->fils = cellule;

    return SUCCESS;
}

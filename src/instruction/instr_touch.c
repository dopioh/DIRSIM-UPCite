#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../utils/include/noeud.h"
#include "../utils/include/liste_noeud.h"
#include "../utils/include/recherche_noeud.h"
#include "../utils/include/erreur.h"

#include "instr_touch.h"

noeud* touch_cible(contexte* ctx, char* chemin) {
    if (ctx == NULL) return NULL;
    if (chemin == NULL) return ctx->noeud_courant;
    return recherche_noeud(ctx, chemin);
}

int noeud_existant_touch(noeud* parent, char* nom) {
    if (parent == NULL) return 1;
    liste_noeud* ptr = parent->fils;
    while (ptr != NULL) {
        if (strcmp(ptr->no->nom, nom) == 0) {
            return 0;
        }
        ptr = ptr->succ;
    }
    return 1;
}

int instr_touch(char* chemin, char* nom, contexte* ctx) {
    if (ctx == NULL || nom == NULL || nom[0] == '\0') return ERR_PARAMETRE_INVALIDE;

    noeud* parent = touch_cible(ctx, chemin);
    if (parent == NULL) return ERR_CHEMIN_INTROUVABLE;

    noeud* noeud_fichier;

    noeud_fichier = malloc(sizeof(noeud));
    if (noeud_fichier == NULL) {
        return ERR_ALLOCATION_MEMOIRE;
    }

    if (noeud_existant_touch(parent, nom) == 0) {
        free(noeud_fichier);
        return ERR_ELEMENT_DEJA_EXISTANT;
    }

    noeud_fichier->est_dossier = 0;
    strncpy(noeud_fichier->nom, nom, sizeof(noeud_fichier->nom) - 1);
    noeud_fichier->nom[sizeof(noeud_fichier->nom) - 1] = '\0';
    noeud_fichier->racine = ctx->noeud_racine;
    noeud_fichier->pere = parent;
    noeud_fichier->fils = NULL;

    liste_noeud* cellule = malloc(sizeof(liste_noeud));
    if (cellule == NULL) {
        free(noeud_fichier);
        return ERR_ALLOCATION_MEMOIRE;
    }
    cellule->no = noeud_fichier;
    cellule->succ = parent->fils;
    parent->fils = cellule;

    return SUCCESS;
}

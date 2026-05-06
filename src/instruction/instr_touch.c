#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/noeud.h"
#include "../include/liste_noeud.h"
#include "../include/recherche_noeud.h"

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
    if (ctx == NULL || nom == NULL || nom[0] == '\0') return 1;

    noeud* parent = touch_cible(ctx, chemin);
    if (parent == NULL) return 1;

    noeud* noeud_fichier;

    noeud_fichier = malloc(sizeof(noeud));
    if (noeud_fichier == NULL) {
        return 1;
    }

    if (noeud_existant_touch(parent, nom) == 0) {
        printf("l'element '%s' existe deja dans ce repertoire...\n", nom);
        free(noeud_fichier);
        return 1;
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
        return 1;
    }
    cellule->no = noeud_fichier;
    cellule->succ = parent->fils;
    parent->fils = cellule;

    return 0;
}

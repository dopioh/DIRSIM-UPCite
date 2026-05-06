#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/noeud.h"
#include "../include/liste_noeud.h"
#include "../include/recherche_noeud.h"

#include "instr_mkdir.h"

noeud* mkdir_cible(contexte* ctx, char* chemin) {
    if (ctx == NULL) return NULL;
    if (chemin == NULL) return ctx->noeud_courant;
    return recherche_noeud(ctx, chemin);
}

int noeud_existant_mkdir(noeud* parent, char* nom) {
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

int instr_mkdir(char* chemin, char* nom, contexte* ctx) {
    if (ctx == NULL || nom == NULL || nom[0] == '\0') return 1;

    noeud* parent = mkdir_cible(ctx, chemin);
    if (parent == NULL) return 1;

    noeud* noeud_dossier;
    noeud_dossier = malloc(sizeof(noeud));

    if (noeud_dossier == NULL) {
        return 1;
    }

    if (noeud_existant_mkdir(parent, nom) == 0) {
        printf("l'element '%s' existe deja dans ce repertoire...\n", nom);
        free(noeud_dossier);
        return 1;
    }

    noeud_dossier->est_dossier = 1;
    strncpy(noeud_dossier->nom, nom, sizeof(noeud_dossier->nom) - 1);
    noeud_dossier->nom[sizeof(noeud_dossier->nom) - 1] = '\0';
    noeud_dossier->racine = ctx->noeud_racine;
    noeud_dossier->pere = parent;
    noeud_dossier->fils = NULL;

    liste_noeud* cellule = malloc(sizeof(liste_noeud));
    if (cellule == NULL) {
        free(noeud_dossier);
        return 1;
    }
    cellule->no = noeud_dossier;
    cellule->succ = parent->fils;
    parent->fils = cellule;

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/noeud.h"
#include "../include/liste_noeud.h"

#include "instr_mkdir.h"

// même principe que l'instruction ls
int dossier_existant(contexte* ctx, char* nom) {
    liste_noeud* ptr = ctx->noeud_courant->fils;

    if (ptr == NULL) return 1;
    while (ptr != NULL) {
        if (ptr->no->est_dossier == 1 && strcmp(ptr->no->nom, nom) == 0) {
            return 0;
        }
        ptr = ptr->succ;
    }
    free(ptr);
    return 1;
}

int instr_mkdir(char* nom, contexte* ctx) {
    noeud* noeud_dossier;
    noeud_dossier = malloc(sizeof(noeud));

    if (noeud_dossier == NULL) {
        free(noeud_dossier);
        return 1;
    }

    if (dossier_existant(ctx, nom) == 0) {
        printf("dossier '%s' existe deja dans ce repertoire...\n", nom);
        return 1;
    }

    noeud_dossier->est_dossier = 1;
    strncpy(noeud_dossier->nom, nom, sizeof(noeud_dossier->nom) - 1);
    noeud_dossier->racine = ctx->noeud_racine;
    noeud_dossier->pere = ctx->noeud_courant;
    noeud_dossier->fils = NULL;

    liste_noeud* cellule = malloc(sizeof(liste_noeud));
    if (cellule == NULL) {
        free(cellule);
        return 1;
    }
    cellule->no = noeud_dossier;
    cellule->succ = ctx->noeud_courant->fils;
    ctx->noeud_courant->fils = cellule;

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/noeud.h"
#include "../include/liste_noeud.h"

#include "instr_mkdir.h"

int instr_mkdir(char* nom, contexte* ctx) {
    noeud* noeud_dossier;
    noeud_dossier = malloc(sizeof(noeud));
    if (noeud_dossier == NULL) {
        free(noeud_dossier);
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
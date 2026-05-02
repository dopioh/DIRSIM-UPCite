#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/noeud.h"
#include "../include/liste_noeud.h"

#include "instr_touch.h"
#include "instr_find.h"

// même principe que l'instruction ls
int fichier_existant(contexte* ctx, char* nom) {
    liste_noeud* ptr = ctx->noeud_courant->fils;

    if (ptr == NULL) return 1;
    while (ptr != NULL) {
        if (ptr->no->est_dossier == 0 && strcmp(ptr->no->nom, nom) == 0) {
            return 0;
        }
        ptr = ptr->succ;
    }
    free(ptr);
    return 1;
}

int instr_touch(char* nom, contexte* ctx) {
    noeud* noeud_fichier;

    noeud_fichier = malloc(sizeof(noeud));
    if (noeud_fichier == NULL) {
        free(noeud_fichier);
        return 1;
    }

    if (fichier_existant(ctx, nom) == 0) {
        printf("fichier '%s' existe deja dans ce repertoire...\n", nom);
        return 1;
    }

    noeud_fichier->est_dossier = 0;
    strncpy(noeud_fichier->nom, nom, sizeof(noeud_fichier->nom) - 1);
    noeud_fichier->racine = ctx->noeud_racine;
    noeud_fichier->pere = ctx->noeud_courant;
    noeud_fichier->fils = NULL;

    liste_noeud* cellule = malloc(sizeof(liste_noeud));
    if (cellule == NULL) {
        free(cellule);
        return 1;
    }
    cellule->no = noeud_fichier;
    cellule->succ = ctx->noeud_courant->fils;
    ctx->noeud_courant->fils = cellule;

    return 0;
}
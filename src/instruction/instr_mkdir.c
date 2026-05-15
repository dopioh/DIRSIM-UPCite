#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../utils/include/noeud.h"
#include "../utils/include/liste_noeud.h"
#include "../utils/include/recherche_noeud.h"
#include "../utils/include/erreur.h"

#include "instr_mkdir.h"

int nom_dossier_valide(char* nom) {
    int i = 0;
    if (nom == NULL || nom[0] == '\0') return 0;
    while (nom[i] != '\0') {
        char c = nom[i];
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            return 0;
        }
        i++;
    }
    return i <= 99;
}

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
    if (ctx == NULL || nom == NULL || nom[0] == '\0') return ERR_PARAMETRE_INVALIDE;
    if (!nom_dossier_valide(nom)) return ERR_PARAMETRE_INVALIDE;

    noeud* parent = mkdir_cible(ctx, chemin);
    if (parent == NULL) return ERR_CHEMIN_INTROUVABLE;

    noeud* noeud_dossier;
    noeud_dossier = malloc(sizeof(noeud));

    if (noeud_dossier == NULL) {
        return ERR_ALLOCATION_MEMOIRE;
    }

    if (noeud_existant_mkdir(parent, nom) == 0) {
        free(noeud_dossier);
        return ERR_ELEMENT_DEJA_EXISTANT;
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
        return ERR_ALLOCATION_MEMOIRE;
    }
    cellule->no = noeud_dossier;
    cellule->succ = parent->fils;
    parent->fils = cellule;

    return SUCCESS;
}

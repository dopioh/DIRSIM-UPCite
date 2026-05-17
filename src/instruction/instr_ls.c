#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../utils/include/noeud.h"
#include "../utils/include/liste_noeud.h"
#include "../utils/include/color.h"
#include "../utils/include/recherche_noeud.h"
#include "../utils/include/erreur.h"

#include "instr_ls.h"

noeud* ls_cible(contexte* ctx, char* chemin) {
    if (ctx == NULL) return NULL;
    if (chemin == NULL) return ctx->noeud_courant;
    return recherche_noeud(ctx, chemin);
}

int instr_ls(contexte* ctx, char* chemin) {
    noeud* cible = ls_cible(ctx, chemin);
    if (cible == NULL) return ERR_CHEMIN_INTROUVABLE;
    if (cible->est_dossier == 0) return ERR_PARAMETRE_INVALIDE;

    liste_noeud* ptr = cible->fils;
    if (ptr == NULL) printf(BLK "(vide)" reset);
    while (ptr != NULL) {
        if (ptr->no->nom[0] != '.') {
            if (ptr->no->est_dossier == 1) {
                printf(BLU "/%s\t" reset, ptr->no->nom );
            }
            else {
                printf("%s\t", ptr->no->nom);
            }
        }
        ptr = ptr->succ;
    }
    printf("\n");

    return SUCCESS;
}

int instr_ls_cache(contexte* ctx, char* chemin) {
    noeud* cible = ls_cible(ctx, chemin);
    if (cible == NULL) return ERR_CHEMIN_INTROUVABLE;
    if (cible->est_dossier == 0) return ERR_PARAMETRE_INVALIDE;

    liste_noeud* ptr = cible->fils;

    if (ptr == NULL) printf(BLK "(vide)" reset);
    while (ptr != NULL) {
        if (ptr->no->est_dossier == 1) {
            printf(BLU "/%s\t" reset, ptr->no->nom );
        }
        else if (ptr->no->nom[0] == '.') {
            printf(BLK "%s\t" reset, ptr->no->nom);
        }
        else {
            printf("%s\t", ptr->no->nom);
        }
        
        ptr = ptr->succ;
    }
    printf("\n");
    return SUCCESS;
}

int instr_ls_fichier(contexte* ctx, char* chemin) {
    noeud* cible = ls_cible(ctx, chemin);
    if (cible == NULL) return ERR_CHEMIN_INTROUVABLE;
    if (cible->est_dossier == 0) return ERR_PARAMETRE_INVALIDE;

    liste_noeud* ptr = cible->fils;

    if (ptr == NULL) printf(BLK "(vide)" reset);
    while (ptr != NULL) {
        if (ptr->no->est_dossier == 0 && ptr->no->nom[0] != '.') {
            printf("%s ", ptr->no->nom);
        }
        ptr = ptr->succ;
    }
    printf("\n");
    return SUCCESS;
}

int instr_ls_dossier(contexte* ctx, char* chemin) {
    noeud* cible = ls_cible(ctx, chemin);
    if (cible == NULL) return ERR_CHEMIN_INTROUVABLE;
    if (cible->est_dossier == 0) return ERR_PARAMETRE_INVALIDE;

    liste_noeud* ptr = cible->fils;

    if (ptr == NULL) printf(BLK "(vide)" reset);
    while (ptr != NULL) {
        if (ptr->no->est_dossier == 1) {
            printf(BLU "/%s\t" reset, ptr->no->nom);
        }
        ptr = ptr->succ;
    }
    printf("\n");
    return SUCCESS;
}

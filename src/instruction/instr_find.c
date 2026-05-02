#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/noeud.h"
#include "../include/liste_noeud.h"
#include "../include/color.h"

#include "instr_find.h"

int parse_type_recherche(char* type) {
    if (type == NULL) return 1;
    if (strcmp(type, "fichier") == 0) return 0;
    if (strcmp(type, "dossier") == 0) return 1;
    return -1;
}

int type_correspond(noeud* no, int type) {
    if (no == NULL) return 1;
    if (type == 0) return no->est_dossier == 0;
    if (type == 1) return no->est_dossier == 1;
    return 0;
}

void print_chemin_noeud(noeud* no) {
    if (no == NULL) return;

    if (no->pere == no) {
        printf("/");
        return;
    }

    print_chemin_noeud(no->pere);
    if (no->pere->pere != no->pere) {
        printf("/");
    }
    printf("%s", no->nom);
}

// trouver_noeud_depart verifie le chemin donné par l'utilisateur et renvoi le noeud au bout du chemin pour commencer la recherche seulement a partir de ce noeud 
noeud* trouver_noeud_depart(contexte* ctx, char* chemin) {
    size_t len;
    char* token; // token est la chaine de caractère qui stock temporairement un nom de dossier/fichier grace a strtok
    char chemin_copie[512]; // on fait une copie car strtok modifie la chaine de caractère sauf qu'on a besoin de la chaine originelle pour plus tard
    noeud* courant;

    if (ctx == NULL || chemin == NULL) return NULL;

    len = strlen(chemin);
    if (len >= sizeof(chemin_copie)) {
        printf(RED "chemin trop long\n" reset);
        return NULL;
    }

    strncpy(chemin_copie, chemin, sizeof(chemin_copie) - 1);
    chemin_copie[sizeof(chemin_copie) - 1] = '\0'; // securité qui garantit que c'est une chaine de caractere

    if (strcmp(chemin_copie, "/") == 0) {
        return ctx->noeud_racine;
    }

    if (chemin_copie[0] == '/') {
        courant = ctx->noeud_racine;
        token = strtok(chemin_copie + 1, "/"); // chemin_copie+1 fait ignorer le premier / a strtok
    }
    else {
        courant = ctx->noeud_courant;
        token = strtok(chemin_copie, "/");
    }

    // a ce moment token contient le premier dossier du chemin

    while (token != NULL) {
        int trouve = 0;
        liste_noeud* fils;

        if (strcmp(token, ".") == 0) {
            token = strtok(NULL, "/"); // strtok(NULL, "/") passe au prochain dossier (de gauche a droite)
            continue;
        }

        if (strcmp(token, "..") == 0) {
            courant = courant->pere;
            token = strtok(NULL, "/");
            continue;
        }

        if (courant->est_dossier == 0) {
            printf(RED "le chemin \"%s\" ne designe pas un dossier\n" reset, chemin);
            return NULL;
        }

        fils = courant->fils;
        while (fils != NULL) {
            if (strcmp(fils->no->nom, token) == 0) { // le dossier existe bien -> il est validé et on passe au prochain
                courant = fils->no;
                trouve = 1;
                break;
            }
            fils = fils->succ;
        }

        if (trouve == 0) {
            printf(RED "le chemin \"%s\" n'existe pas\n" reset, chemin);
            return NULL;
        }

        token = strtok(NULL, "/"); // on passe au prochain dossier
    }

    if (courant->est_dossier == 0) {
        printf(RED "le chemin \"%s\" ne designe pas un dossier\n" reset, chemin);
        return NULL;
    }

    return courant;
}

void rechercher_recursif(noeud* courant, char* nom, int type, int* nb_resultats) {
    liste_noeud* fils;

    if (courant == NULL || nom == NULL || nb_resultats == NULL) return;

    if (type_correspond(courant, type) && strcmp(courant->nom, nom) == 0) {
        print_chemin_noeud(courant);
        printf("\n");
        (*nb_resultats)++;
    }

    fils = courant->fils;
    while (fils != NULL) {
        rechercher_recursif(fils->no, nom, type, nb_resultats);
        fils = fils->succ;
    }
}

int instr_find(contexte* ctx, char* chemin, char* type, char* nom) {
    noeud* noeud_depart = NULL;
    int nb_resultats = 0;
    int type_recherche;

    if (ctx == NULL || chemin == NULL || type == NULL || nom == NULL) {
        return 1;
    }

    type_recherche = parse_type_recherche(type);
    if (type_recherche == -1) {
        printf(RED "type \"%s\" invalide (attendu: fichier ou dossier)\n" reset, type);
        return 1;
    }

    noeud_depart = trouver_noeud_depart(ctx, chemin);
    if (noeud_depart == NULL) {
        return 1;
    }

    rechercher_recursif(noeud_depart, nom, type_recherche, &nb_resultats);

    if (nb_resultats == 0) {
        printf(BLK "(aucun resultat)\n" reset);
        return 1;
    }

    return 0;
}

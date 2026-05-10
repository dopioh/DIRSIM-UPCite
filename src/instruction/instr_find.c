#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/include/noeud.h"
#include "../utils/include/liste_noeud.h"
#include "../utils/include/color.h"
#include "../utils/include/recherche_noeud.h"

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

    noeud_depart = recherche_noeud(ctx, chemin);
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

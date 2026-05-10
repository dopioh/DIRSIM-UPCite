#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#include "include/noeud.h"
#include "include/liste_noeud.h"
#include "include/execute.h"
#include "include/recherche_noeud.h"

// verifie le chemin donné par l'utilisateur et renvoi le noeud du dossier le plus profond
noeud* recherche_noeud(contexte* ctx, char* chemin) {
    size_t len;
    char* token; // token est la chaine de caractère qui stock temporairement un nom de dossier/fichier grace a strtok
    char chemin_copie[512]; // on fait une copie car strtok modifie la chaine de caractère sauf qu'on a besoin de la chaine originelle pour plus tard
    noeud* courant;

    if (ctx == NULL || chemin == NULL) return NULL;

    len = strlen(chemin);
    if (len >= sizeof(chemin_copie)) {
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
            return NULL;
        }

        token = strtok(NULL, "/"); // on passe au prochain dossier
    }

    if (courant->est_dossier == 0) {
        return NULL;
    }

    return courant;
}

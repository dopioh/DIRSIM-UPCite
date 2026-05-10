#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/include/noeud.h"
#include "utils/include/liste_noeud.h"
#include "utils/include/erreur.h"

#include "utils/include/execute.h"
#include "utils/include/clear.h"
#include "utils/include/color.h"

#define INSTRUCTION_MAX_LEN_STRING 256

int nom_correct(char* nom) { // sert a choisir un nom valide pour la sauvegarde
    int i = 0;
    if (nom[0] == '\0') return 1;
    while (nom[i] != '\0') {
        char c = nom[i];
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            return 1;
        }
        i++;
    }
    return 0;
}

int executer_fichier(contexte* ctx, char* chemin, FILE* journal) {
    FILE* fichier_instr = fopen(chemin, "r");
    if (fichier_instr == NULL) {
        printf(RED "erreur: impossible d'ouvrir '%s'\n" reset, chemin);
        return 1;
    }

    char instruction[INSTRUCTION_MAX_LEN_STRING];
    while (fgets(instruction, INSTRUCTION_MAX_LEN_STRING, fichier_instr) != NULL) {
        execute(instruction, ctx, journal);
    }

    fclose(fichier_instr);
    return 0;
}

int main(int argc, char* argv[]) {
    noeud* noeud_racine = malloc(sizeof(noeud));
    if (noeud_racine == NULL) {
        free(noeud_racine);
        return 1;
    }

    // creation racine
    noeud_racine->est_dossier = 1;
    strncpy(noeud_racine->nom, "", sizeof(noeud_racine->nom) - 1);
    noeud_racine->pere = noeud_racine;
    noeud_racine->racine = noeud_racine;
    noeud_racine->fils = NULL;

    // creation du contexte (voir execute.h)
    contexte* ctx = malloc(sizeof(contexte));
    if (ctx == NULL) {
        free(ctx);
        return 1;
    }
    ctx->noeud_racine = noeud_racine;
    ctx->noeud_courant = noeud_racine;

    // creation du fichier logs.txt
    FILE* fichier_journal;
    fichier_journal = fopen("journaux.txt", "r");
    
    if (fichier_journal == NULL) {
        fichier_journal = fopen("journaux.txt", "w");
    }
    else { // on supprime les anciens journaux
        fclose(fichier_journal); // valgrind pas content si on re ouvre sans close
        fichier_journal = fopen("journaux.txt", "w");
    }

    if (argc == 2) {
        executer_fichier(ctx, argv[1], fichier_journal);
    }
    else if (argc == 3 && (strcmp(argv[1], "-S") == 0)) {
        char nom_sauvegarde[256];
        do {
            printf("entrer un nom de sauvegarde (alphanumerique): ");
            scanf("%s", nom_sauvegarde);
        }
        while (nom_correct(nom_sauvegarde) != 0);
        
        FILE* fichier_instr = fopen(argv[2], "r");
        if (fichier_instr == NULL) return 1;

        FILE* sauvegarde = fopen(nom_sauvegarde, "w");
        if (sauvegarde == NULL) {
            fclose(fichier_instr);
            return 1;
        }

        char ligne[INSTRUCTION_MAX_LEN_STRING];
        while (fgets(ligne, sizeof(ligne), fichier_instr) != NULL) {
            if (strncmp(ligne, "cd", 2) == 0 || strncmp(ligne, "touch", 5) == 0 || strncmp(ligne, "mkdir", 5) == 0 || strncmp(ligne, "cp", 2) == 0 || strncmp(ligne, "rm", 1) == 0) { // la sauvegarde ne save que les instructions cd, mkdir, touch, cp et rm
                fputs(ligne, sauvegarde);
            }
        }

        fclose(fichier_instr);
        fclose(sauvegarde);

        executer_fichier(ctx, argv[2], fichier_journal);
    }
    else if (argc == 4 && (strcmp(argv[1], "-L") == 0)) {
        executer_fichier(ctx, argv[2], fichier_journal); // exec du fichier sauvegarde
        executer_fichier(ctx, argv[3], fichier_journal); // exec du fichier courant
    }
    else {
        printf(RED "mauvais arguments...\n" reset);
        return 1;
    }


    printf("\n");
    
    free(ctx);
    clear(noeud_racine);
    fclose(fichier_journal);
    return 0;
}
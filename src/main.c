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

    // creation du fichier journaux.txt
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
    else if (argc == 1) {
        char instruction[INSTRUCTION_MAX_LEN_STRING];
        printf("Tapez 'exit' pour quitter.\n");
        while (1) {
            printf("> ");
            fflush(stdout);
            if (fgets(instruction, INSTRUCTION_MAX_LEN_STRING, stdin) == NULL) {
                break;
            }
            if (strncmp(instruction, "exit", 4) == 0 && (instruction[4] == '\0' || instruction[4] == '\n' || instruction[4] == ' ')) {
                break;
            }
            execute(instruction, ctx, fichier_journal);
        }
    }
    else {
        printf(RED "usage: ./programme [instructions.txt]\n" reset);
        if (ctx != NULL) {
            free(ctx);
        }
        if (noeud_racine != NULL) {
            clear(noeud_racine);
        }
        if (fichier_journal) {
            fclose(fichier_journal);
        }
        return 1;
    }


    printf("\n");
    
    if (ctx != NULL) {
        free(ctx);
    }
    if (noeud_racine != NULL) {
        clear(noeud_racine);
    }
    if (fichier_journal) {
        fclose(fichier_journal);
    }
    return 0;
}

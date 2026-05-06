#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#include "include/noeud.h"
#include "include/color.h"
#include "include/execute.h"
#include "include/parseur.h"

#include "instruction/print.h"
#include "instruction/instr_touch.h"
#include "instruction/instr_mkdir.h"
#include "instruction/instr_ls.h"
#include "instruction/instr_cd.h"
#include "instruction/instr_pwd.h"
#include "instruction/instr_find.h"

#define MAX_ARGS 5

int execute(char* instruction, contexte* ctx, FILE* fichier_journal) {
    if (instruction == NULL) return 1;

    // creation de la copie du string instruction pour le fichier journal
    char instruction_log[256];
    strncpy(instruction_log, instruction, sizeof(instruction_log) - 1);
    instruction_log[sizeof(instruction_log) - 1] = '\0';
    instruction_log[strcspn(instruction_log, "\n")] = '\0'; // strcspn renvoi l'indice du premier \n ce qui permet de le remplacer par \0 pour finir la ligne

    char* args[MAX_ARGS];
    int arg_count = parseur(instruction, args, MAX_ARGS);
    int erreur = 0;

    // setup du temps d'execution
    clock_t debut, fin; 
    double duree;
    debut = clock();

    if (arg_count <= 0) {
        erreur = 1;
    } else if (strcmp(args[0], "print") == 0) {
        if (arg_count == 1) print();
        else erreur = 1;
    } else if (strcmp(args[0], "pwd") == 0) {
        if (arg_count == 1) instr_pwd(ctx);
        else erreur = 1;
    } else if (strcmp(args[0], "touch") == 0) {
        if (arg_count == 2) instr_touch(args[1], ctx);
        else erreur = 1;
    } else if (strcmp(args[0], "mkdir") == 0) {
        if (arg_count == 2) instr_mkdir(args[1], ctx);
        else erreur = 1;
    } else if (strcmp(args[0], "cd") == 0) {
        if (arg_count == 2) instr_cd(args[1], ctx);
        else erreur = 1;
    } else if (strcmp(args[0], "ls") == 0) {
        if (arg_count == 1) {
            instr_ls(ctx);
        } else if (arg_count == 2 && strcmp(args[1], "-a") == 0) {
            instr_ls_cache(ctx);
        } else if (arg_count == 2 && (strcmp(args[1], "-f") == 0 || strcmp(args[1], "-fichier") == 0)) {
            instr_ls_fichier(ctx);
        } else if (arg_count == 2 && (strcmp(args[1], "-d") == 0 || strcmp(args[1], "-dossier") == 0)) {
            instr_ls_dossier(ctx);
        } else {
            erreur = 1;
        }
    } else if (strcmp(args[0], "find") == 0) {
        if (arg_count == 4) instr_find(ctx, args[1], args[2], args[3]);
        else erreur = 1;
    } else {
        erreur = 1;
    }

    if (erreur) {
        printf(RED "/!\\ '%s' SYNTAXE INCORRECTE /!\\\n" reset, instruction_log);
    }

    fin = clock();
    duree = ((double)fin - debut) / CLOCKS_PER_SEC;

    if (fichier_journal != NULL) {
        if (erreur == 0) {
            fprintf(fichier_journal, "%s | succes | %.6f\n", instruction_log, duree);
        }
        else {
            fprintf(fichier_journal, "%s | echec erreur syntaxe | ...\n", instruction_log);
        }
        fflush(fichier_journal); // force l'ecriture immediatement dans le fichier journal
    }

    return 0;
}

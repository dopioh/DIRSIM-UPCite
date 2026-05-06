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

    // creation de la copie du string instruction pour le fichier journal sans \n
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

    if (arg_count <= 0 || arg_count >= MAX_ARGS) {
        erreur = 1;
    } else {
        switch (args[0][0]) {
            case 'p':
                if (strcmp(args[0], "print") == 0) {
                    if (arg_count == 1) print();
                    else erreur = 1;
                } else if (strcmp(args[0], "pwd") == 0) {
                    if (arg_count == 1) instr_pwd(ctx);
                    else erreur = 1;
                } else {
                    erreur = 1;
                }
                break;
            case 't':
                if (strcmp(args[0], "touch") == 0) {
                    if (arg_count == 2) {
                        if (instr_touch(NULL, args[1], ctx) != 0) erreur = 1;
                    } else if (arg_count == 3) {
                        if (instr_touch(args[1], args[2], ctx) != 0) erreur = 1;
                    } else erreur = 1;
                } else {
                    erreur = 1;
                }
                break;
            case 'm':
                if (strcmp(args[0], "mkdir") == 0) {
                    if (arg_count == 2) {
                        if (instr_mkdir(NULL, args[1], ctx) != 0) erreur = 1;
                    } else if (arg_count == 3) {
                        if (instr_mkdir(args[1], args[2], ctx) != 0) erreur = 1;
                    } else erreur = 1;
                } else {
                    erreur = 1;
                }
                break;
            case 'c':
                if (strcmp(args[0], "cd") == 0) {
                    if (arg_count == 2) instr_cd(args[1], ctx);
                    else erreur = 1;
                } else {
                    erreur = 1;
                }
                break;
            case 'l':
                if (strcmp(args[0], "ls") != 0) {
                    erreur = 1;
                    break;
                }
                if (arg_count == 1) {
                    if (instr_ls(ctx, NULL) != 0) erreur = 1;
                } else if (arg_count == 2 && strcmp(args[1], "-a") == 0) {
                    if (instr_ls_cache(ctx, NULL) != 0) erreur = 1;
                } else if (arg_count == 2 && (strcmp(args[1], "-f") == 0 || strcmp(args[1], "-fichier") == 0)) {
                    if (instr_ls_fichier(ctx, NULL) != 0) erreur = 1;
                } else if (arg_count == 2 && (strcmp(args[1], "-d") == 0 || strcmp(args[1], "-dossier") == 0)) {
                    if (instr_ls_dossier(ctx, NULL) != 0) erreur = 1;
                } else if (arg_count == 2 &&
                           strcmp(args[1], "-a") != 0 &&
                           strcmp(args[1], "-f") != 0 &&
                           strcmp(args[1], "-fichier") != 0 &&
                           strcmp(args[1], "-d") != 0 &&
                           strcmp(args[1], "-dossier") != 0) {
                    if (instr_ls(ctx, args[1]) != 0) erreur = 1;
                } else if (arg_count == 3 && strcmp(args[1], "-a") == 0) {
                    if (instr_ls_cache(ctx, args[2]) != 0) erreur = 1;
                } else if (arg_count == 3 && (strcmp(args[1], "-f") == 0 || strcmp(args[1], "-fichier") == 0)) {
                    if (instr_ls_fichier(ctx, args[2]) != 0) erreur = 1;
                } else if (arg_count == 3 && (strcmp(args[1], "-d") == 0 || strcmp(args[1], "-dossier") == 0)) {
                    if (instr_ls_dossier(ctx, args[2]) != 0) erreur = 1;
                } else {
                    erreur = 1;
                }
                break;
            case 'f':
                if (strcmp(args[0], "find") == 0) {
                    if (arg_count == 4) instr_find(ctx, args[1], args[2], args[3]);
                    else erreur = 1;
                } else {
                    erreur = 1;
                }
                break;
            default:
                erreur = 1;
                break;
        }
    }

    // if (erreur) {
    //     printf(RED "/!\\ une erreur s'est produite avec l'instruction '%s' /!\\\n" reset, instruction_log);
    // }

    fin = clock();
    duree = ((double)fin - debut) / CLOCKS_PER_SEC;

    if (fichier_journal != NULL) {
        if (erreur == 0) {
            fprintf(fichier_journal, "%s | succes | %.6f\n", instruction_log, duree);
        }
        else {
            fprintf(fichier_journal, "%s | echec | ...\n", instruction_log);
        }
        fflush(fichier_journal); // force l'ecriture immediatement dans le fichier journal
    }

    return 0;
}

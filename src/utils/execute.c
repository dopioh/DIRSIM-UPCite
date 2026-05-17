#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#include "include/noeud.h"
#include "include/color.h"
#include "include/execute.h"
#include "include/parseur.h"
#include "include/erreur.h"

#include "../instruction/instr_print.h"
#include "../instruction/instr_touch.h"
#include "../instruction/instr_mkdir.h"
#include "../instruction/instr_cp.h"
#include "../instruction/instr_ls.h"
#include "../instruction/instr_cd.h"
#include "../instruction/instr_pwd.h"
#include "../instruction/instr_find.h"
#include "../instruction/instr_rm.h"
#include "../instruction/instr_cp.h"
#include "../instruction/instr_mv.h"
#include "../instruction/instr_man.h"
#include "../instruction/instr_history.h"

#define MAX_ARGS 5

char* message_erreur(int erreur) {
    switch (erreur) {
        case SUCCESS:
            return "succes";
        case ERR_CHEMIN_INTROUVABLE:
            return "chemin introuvable";
        case ERR_ELEMENT_DEJA_EXISTANT:
            return "element deja existant";
        case ERR_INSTRUCTION_NULL:
            return "instruction nulle";
        case ERR_INSTRUCTION_VIDE:
            return "instruction vide";
        case ERR_TROP_ARGUMENTS:
            return "trop d'arguments";
        case ERR_COMMANDE_INCONNUE:
            return "commande inconnue";
        case ERR_SYNTAXE_COMMANDE:
            return "syntaxe de commande invalide";
        case ERR_PARAMETRE_INVALIDE:
            return "parametre invalide";
        case ERR_ALLOCATION_MEMOIRE:
            return "erreur d'allocation memoire";
        case ERR_TYPE_FIND_INVALIDE:
            return "type find invalide";
        case ERR_AUCUN_RESULTAT:
            return "aucun resultat";
        default:
            return "erreur inconnue";
    }
}

int execute(char* instruction, contexte* ctx, FILE* fichier_journal) {
    if (instruction == NULL) return ERR_INSTRUCTION_NULL;

    // creation de la copie du string instruction pour le fichier journal sans \n
    char instruction_log[256];
    strncpy(instruction_log, instruction, sizeof(instruction_log) - 1);
    instruction_log[sizeof(instruction_log) - 1] = '\0';
    instruction_log[strcspn(instruction_log, "\n")] = '\0'; // strcspn renvoi l'indice du premier \n ce qui permet de le remplacer par \0 pour finir la ligne

    instruction[strcspn(instruction, "\r\n")] = '\0';

    char* args[MAX_ARGS];
    int arg_count = parseur(instruction, args, MAX_ARGS);
    int erreur = SUCCESS;

    // setup du temps d'execution
    clock_t debut, fin; 
    double duree;
    debut = clock();

    if (arg_count <= 0) {
        erreur = ERR_INSTRUCTION_VIDE;
    } else if (arg_count >= MAX_ARGS) {
        erreur = ERR_TROP_ARGUMENTS;
    } else {
        switch (args[0][0]) { // on peut pas switch avec un string
            case 'p':
                if (strcmp(args[0], "print") == 0) {
                    if (arg_count == 1) erreur = instr_print(ctx);
                    else erreur = ERR_SYNTAXE_COMMANDE;
                } else if (strcmp(args[0], "pwd") == 0) {
                    if (arg_count == 1) erreur = instr_pwd(ctx);
                    else erreur = ERR_SYNTAXE_COMMANDE;
                } else {
                    erreur = ERR_COMMANDE_INCONNUE;
                }
                break;
            case 't':
                if (strcmp(args[0], "touch") == 0) {
                    if (arg_count == 2) {
                        erreur = instr_touch(NULL, args[1], ctx);
                    } else if (arg_count == 3) {
                        erreur = instr_touch(args[1], args[2], ctx);
                    } else erreur = ERR_SYNTAXE_COMMANDE;
                } else {
                    erreur = ERR_COMMANDE_INCONNUE;
                }
                break;
            case 'm':
                if (strcmp(args[0], "mkdir") == 0) {
                    if (arg_count == 2) {
                        erreur = instr_mkdir(NULL, args[1], ctx);
                    } else if (arg_count == 3) {
                        erreur = instr_mkdir(args[1], args[2], ctx);
                    } else erreur = ERR_SYNTAXE_COMMANDE;
                } else if (strcmp(args[0], "man") == 0) {
                    if (arg_count == 2) {
                        erreur = instr_man(args[1], ctx);
                    } else erreur = ERR_SYNTAXE_COMMANDE;
                } else if (strcmp(args[0], "mv") == 0) {
                    if (arg_count == 3) {
                        erreur = instr_mv(args[1], args[2], ctx);
                    } else erreur = ERR_SYNTAXE_COMMANDE;
                } else {
                    erreur = ERR_COMMANDE_INCONNUE;
                }
                break;
            case 'c':
                if (strcmp(args[0], "cd") == 0) {
                    if (arg_count == 1) erreur = instr_cd(NULL, ctx);
                    else if (arg_count == 2) erreur = instr_cd(args[1], ctx);
                    else erreur = ERR_SYNTAXE_COMMANDE;
                } else if (strcmp(args[0], "cp") == 0) {
                    if (arg_count == 3) erreur = instr_cp(args[1], args[2], ctx);
                    else erreur = ERR_SYNTAXE_COMMANDE;
                } else {
                    erreur = ERR_COMMANDE_INCONNUE;
                }
                break;
            case 'l':
                if (strcmp(args[0], "ls") != 0) {
                    erreur = ERR_COMMANDE_INCONNUE;
                    break;
                }
                if (arg_count == 1) {
                    erreur = instr_ls(ctx, NULL);
                } else if (arg_count == 2 && strcmp(args[1], "-a") == 0) {
                    erreur = instr_ls_cache(ctx, NULL);
                } else if (arg_count == 2 && (strcmp(args[1], "-f") == 0 || strcmp(args[1], "-fichier") == 0)) {
                    erreur = instr_ls_fichier(ctx, NULL);
                } else if (arg_count == 2 && (strcmp(args[1], "-d") == 0 || strcmp(args[1], "-dossier") == 0)) {
                    erreur = instr_ls_dossier(ctx, NULL);
                } else if (arg_count == 2 &&
                           strcmp(args[1], "-a") != 0 &&
                           strcmp(args[1], "-f") != 0 &&
                           strcmp(args[1], "-fichier") != 0 &&
                           strcmp(args[1], "-d") != 0 &&
                           strcmp(args[1], "-dossier") != 0) {
                    erreur = instr_ls(ctx, args[1]);
                } else if (arg_count == 3 && strcmp(args[1], "-a") == 0) {
                    erreur = instr_ls_cache(ctx, args[2]);
                } else if (arg_count == 3 && (strcmp(args[1], "-f") == 0 || strcmp(args[1], "-fichier") == 0)) {
                    erreur = instr_ls_fichier(ctx, args[2]);
                } else if (arg_count == 3 && (strcmp(args[1], "-d") == 0 || strcmp(args[1], "-dossier") == 0)) {
                    erreur = instr_ls_dossier(ctx, args[2]);
                } else {
                    erreur = ERR_SYNTAXE_COMMANDE;
                }
                break;
            case 'f':
                if (strcmp(args[0], "find") == 0) {
                    if (arg_count == 4) erreur = instr_find(ctx, args[1], args[2], args[3]);
                    else erreur = ERR_SYNTAXE_COMMANDE;
                } else {
                    erreur = ERR_COMMANDE_INCONNUE;
                }
                break;
            case 'h':
                if (strcmp(args[0], "history") == 0) {
                    if (arg_count == 1) erreur = instr_history(ctx);
                    else erreur = ERR_SYNTAXE_COMMANDE;
                } else {
                    erreur = ERR_COMMANDE_INCONNUE;
                }
                break;
            case 'r':
                if (strcmp(args[0], "rm") == 0) {
                    if (arg_count == 2) erreur = instr_rm(args[1], ctx);
                    else erreur = ERR_SYNTAXE_COMMANDE;
                } else {
                    erreur = ERR_COMMANDE_INCONNUE;
                }
                break;
            default:
                erreur = ERR_COMMANDE_INCONNUE;
                break;
        }
    }

    fin = clock();
    duree = ((double)fin - debut) / CLOCKS_PER_SEC;

    if (erreur != SUCCESS) {
        char* message = message_erreur(erreur);
        printf(RED "(%s | echec | code=%d | %s)\n" reset, instruction_log, erreur, message);
    }

    if (fichier_journal != NULL) {
        if (erreur == SUCCESS) {
            fprintf(fichier_journal, "%s | succes | %.6f\n", instruction_log, duree);
        }
        else {
            char* message = message_erreur(erreur);
            fprintf(fichier_journal, "%s | echec | code=%d | %s\n", instruction_log, erreur, message);
        }
        fflush(fichier_journal); // force l'ecriture immediatement dans le fichier journal
    }

    if (instruction_log[0] != '\0') {
        history_ajouter(instruction_log);
    }

    return 0;
}

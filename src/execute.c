#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int execute(char* instruction, contexte* ctx) {
    char* args[MAX_ARGS];
    int arg_count = parseur(instruction, args);

    if (arg_count == 1) {
        if (strcmp(args[0], "print") == 0) {
            print();
        }
        if (strcmp(args[0], "ls") == 0) {
            instr_ls(ctx);
        }
        if (strcmp(args[0], "pwd") == 0) {
            instr_pwd(ctx);
        }
    }

    if (arg_count == 2) {
        if (strcmp(args[0], "touch") == 0) {
            /**
             * XXX: faire une fonction qui verifie si l'argument est un nom ou une option
             */
            instr_touch(args[1], ctx); 
        }
        if (strcmp(args[0], "mkdir") == 0) {
            /**
             * XXX: faire une fonction qui verifie si l'argument est un nom ou une option
             */
            instr_mkdir(args[1], ctx);
        }
        if (strcmp(args[0], "cd") == 0) {
            /**
             * XXX: faire une fonction qui verifie si l'argument est un nom ou une option
             */
            instr_cd(args[1], ctx);
        }
    }

    if (arg_count == 4) {
        if (strcmp(args[0], "find") == 0) {
            instr_find(ctx, args[1], args[2], args[3]);
        }
    }

    return 0;
}

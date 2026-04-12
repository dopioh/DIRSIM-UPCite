#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/noeud.h"
#include "include/color.h"
#include "include/execute.h"
#include "include/parseur.h"

#include "instruction/print.h"
#include "instruction/instr_touch.h"

#define MAX_ARGS 5

int execute(char* instruction, contexte* ctx) {
    char* args[MAX_ARGS];
    int arg_count = parseur(instruction, args);

    if (arg_count == 1) {
        if (strcmp(args[0], "print") == 0) {
            print();
        }
    }
    if (arg_count == 2) {
        if (strcmp(args[0], "touch") == 0) {
            /**
             * XXX: faire une fonction qui verifie si l'argument est un nom ou une option
             */
            instr_touch(args[1], ctx); 
        }
    }

    return 0;
}
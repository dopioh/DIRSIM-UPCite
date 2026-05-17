#ifndef INSTR_LOAD
#define INSTR_LOAD

#include <stdio.h>

#include "../utils/include/noeud.h"
#include "../utils/include/execute.h"

int instr_load(char* chemin, contexte* ctx, FILE* fichier_journal);

#endif

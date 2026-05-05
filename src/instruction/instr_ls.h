#ifndef INSTR_LS
#define INSTR_LS

#include "../include/execute.h"

int instr_ls(contexte* ctx);
int instr_ls_cache(contexte* ctx);
int instr_ls_dossier(contexte* ctx);
int instr_ls_fichier(contexte* ctx);

#endif
#ifndef INSTR_LS
#define INSTR_LS

#include "../include/execute.h"

int instr_ls(contexte* ctx, char* chemin);
int instr_ls_cache(contexte* ctx, char* chemin);
int instr_ls_dossier(contexte* ctx, char* chemin);
int instr_ls_fichier(contexte* ctx, char* chemin);

#endif

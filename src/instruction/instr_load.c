#include <stdio.h>
#include <string.h>

#include "../utils/include/erreur.h"
#include "instr_load.h"

#define INSTRUCTION_MAX_LEN_STRING 256
#define LOAD_MAX_DEPTH 16 // secu pour eviter les recursions infinies, au maximum 16 loads imbriqués

static int load_profondeur = 0;

int instr_load(char* chemin, contexte* ctx, FILE* fichier_journal) {
    char instruction[INSTRUCTION_MAX_LEN_STRING];
    FILE* fichier_instr;

    if (ctx == NULL || chemin == NULL || chemin[0] == '\0') return ERR_PARAMETRE_INVALIDE;

    if (load_profondeur >= LOAD_MAX_DEPTH) {
        return ERR_PARAMETRE_INVALIDE;
    }

    fichier_instr = fopen(chemin, "r");
    if (fichier_instr == NULL) {
        return ERR_CHEMIN_INTROUVABLE;
    }

    load_profondeur++;
    while (fgets(instruction, INSTRUCTION_MAX_LEN_STRING, fichier_instr) != NULL) {
        execute(instruction, ctx, fichier_journal);
    }
    load_profondeur--;

    fclose(fichier_instr);
    return SUCCESS;
}

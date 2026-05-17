#include <stdio.h>
#include <string.h>

#include "../utils/include/erreur.h"
#include "instr_history.h"
#include "instr_save.h"

int instr_save(char* chemin, contexte* ctx) {
    (void)ctx;

    if (chemin == NULL || chemin[0] == '\0') return ERR_PARAMETRE_INVALIDE;
    return history_sauvegarder(chemin);
}

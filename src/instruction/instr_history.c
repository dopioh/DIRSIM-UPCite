#include <stdio.h>
#include <string.h>

#include "../utils/include/erreur.h"
#include "instr_history.h"

#define HISTORY_MAX 50
#define HISTORY_LINE_MAX 256

static char historique[HISTORY_MAX][HISTORY_LINE_MAX];
static int historique_debut = 0;
static int historique_taille = 0;

void history_ajouter(char* commande) {
    int index;

    if (commande == NULL || commande[0] == '\0') return;

    index = (historique_debut + historique_taille) % HISTORY_MAX;
    strncpy(historique[index], commande, HISTORY_LINE_MAX - 1);
    historique[index][HISTORY_LINE_MAX - 1] = '\0';

    if (historique_taille < HISTORY_MAX) {
        historique_taille++;
    } else {
        historique_debut = (historique_debut + 1) % HISTORY_MAX;
    }
}

int instr_history(contexte* ctx) {
    int i;

    (void)ctx;

    for (i = 0; i < historique_taille; i++) {
        int index = (historique_debut + i) % HISTORY_MAX;
        printf("%d %s\n", i + 1, historique[index]);
    }

    return SUCCESS;
}

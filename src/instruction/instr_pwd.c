#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../utils/include/noeud.h"
#include "../utils/include/liste_noeud.h"
#include "../utils/include/color.h"

#include "instr_pwd.h"

// meme principe que print_chemin_noeud de l'instruction find
void print_chemin(noeud* no) {
    if (no == NULL) return;

    if (no->pere == no) {
        printf("/");
        return;
    }

    print_chemin(no->pere);
    if (no->pere->pere != no->pere) {
        printf("/");
    }
    printf("%s", no->nom);
}

int instr_pwd(contexte* ctx) {
    if (ctx == NULL) return 1;
    noeud* no = ctx->noeud_courant;
    print_chemin(no);
    printf("\n");
    return 0;
}
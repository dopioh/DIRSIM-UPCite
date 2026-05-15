#ifndef EXECUTE_H
#define EXECUTE_H

struct contexte {
    noeud* noeud_racine;
    noeud* noeud_courant;
};
typedef struct contexte contexte;

int execute(char* instruction, contexte* ctx, FILE* fichier_journal);

#endif
#ifndef INSTR_HISTORY
#define INSTR_HISTORY

typedef struct contexte contexte;

int instr_history(contexte* ctx);
void history_ajouter(char* commande);
int history_sauvegarder(char* chemin);

#endif

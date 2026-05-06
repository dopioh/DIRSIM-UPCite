#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/noeud.h"
#include "include/liste_noeud.h"

#include "include/execute.h"
#include "include/clear.h"
#include "include/color.h"

#define INSTRUCTION_MAX_LEN_STRING 256

int main(int argc, char* argv[]) {
    noeud* noeud_racine = malloc(sizeof(noeud));
    if (noeud_racine == NULL) {
        free(noeud_racine);
        return 1;
    }

    noeud_racine->est_dossier = 1;
    strncpy(noeud_racine->nom, "", sizeof(noeud_racine->nom) - 1);;
    noeud_racine->pere = noeud_racine;
    noeud_racine->racine = noeud_racine;
    noeud_racine->fils = NULL;

    contexte* ctx = malloc(sizeof(contexte));
    if (ctx == NULL) {
        free(ctx);
        return 1;
    }
    ctx->noeud_racine = noeud_racine;
    ctx->noeud_courant = noeud_racine;


    if (argc < 2) {
        printf(RED "./programme instructions.txt\n" reset);
        return 1;
    }
    
    FILE* fichier_instructions;
    fichier_instructions = fopen(argv[1], "r");
    if (fichier_instructions == NULL) {
        printf(RED "erreur lors de l'ouverture du fichier...\n" reset);
        return 1;
    }

    // creation du fichier logs.txt
    FILE* fichier_journal;
    fichier_journal = fopen("logs.txt", "r");
    if (fichier_journal == NULL) {
        printf("Le programme a besoin de créer le fichier 'logs.txt' pour inscrire ses journaux.\nAutoriser la création du fichier ? (O/N) : ");
        char choix;
        do {
            scanf(" %c", &choix);
        }
        while (choix != 'O' && choix != 'N' && choix != 'o' && choix != 'n');
        if (choix == 'O' || choix == 'o') {
            fichier_journal = fopen("logs.txt", "w");
        }
    }
    else { // on supprime les anciens journaux
        fclose(fichier_journal); // valgrind pas content si on re ouvre sans close
        fichier_journal = fopen("logs.txt", "w");
    }

    char* instruction_courante = malloc(INSTRUCTION_MAX_LEN_STRING*sizeof(char));
    if (instruction_courante == NULL) return 1;

    while(fgets(instruction_courante, INSTRUCTION_MAX_LEN_STRING, fichier_instructions) != NULL) {
        execute(instruction_courante, ctx, fichier_journal);
    }

    printf("\n");
    
    free(instruction_courante);
    free(ctx);
    clear(noeud_racine);
    fclose(fichier_instructions);
    fclose(fichier_journal);
    return 0;
}
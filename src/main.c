#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/color.h"

#include "include/noeud.h"
#include "include/liste_noeud.h"
#include "include/execute.h"

#define INSTRUCTION_MAX_LEN_STRING 100


int main(int argc, char* argv[]){
    if (argc < 2) {
        printf(RED "./programme instructions.txt\n" reset);
        return -1;
    }
    
    FILE* fichier_instructions;
    fichier_instructions = fopen(argv[1], "r");
    if (fichier_instructions == NULL) {
        printf(RED "erreur lors de l'ouverture du fichier...\n" reset);
        return -1;
    }

    char* instruction_courante = malloc(INSTRUCTION_MAX_LEN_STRING*sizeof(char));
    if (instruction_courante == NULL) return -1;

    while((instruction_courante = fgets(instruction_courante, INSTRUCTION_MAX_LEN_STRING, fichier_instructions)) != NULL) {
        execute(instruction_courante);
    }

    printf("\n");
    free(instruction_courante);
    fclose(fichier_instructions);
    return 0;
}
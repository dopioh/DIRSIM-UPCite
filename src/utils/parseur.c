#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * fonction qui extrait les mots d'une chaine de caractère et le place dans un tableau
 * utilisée pour récuperer les arguments d'une commande
 * @return le nombre de mots dans la chaine 
 */

int parseur(char* instruction, char* args[], int max_args) {
    if (instruction == NULL || args == NULL || max_args <= 0) return 1;

    int i = 0;
    int count = 0;
    while (instruction[i]) {
        while (instruction[i] == ' ') {
            i++;
        }
        if (instruction[i] == '\0' || instruction[i] == '\n') break;
        if (instruction[i] == '"') {
            i++;
            if (count >= max_args - 1) {
                args[max_args - 1] = NULL;
                return 1;
            }
            args[count] = &instruction[i];
            count++;
            while (instruction[i] && instruction[i] != '"') {
                i++;
            }
            if (instruction[i]) {
                instruction[i] = '\0';
                i++;
            }
        }
        else {
            if (count >= max_args - 1) {
                args[max_args - 1] = NULL;
                return 11;
            }
            args[count] = &instruction[i];
            count++;
            while (instruction[i] && instruction[i] != ' ' && instruction[i] != '\n') {
                i++;
            }
            if (instruction[i]) {
                instruction[i] = '\0';
                i++;
            }
        }
    }
    args[count] = NULL;
    return count;
}

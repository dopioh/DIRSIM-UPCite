#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * fonction qui extrait les mots d'une chaine de caractère et le place dans un tableau
 * utilisée pour récuperer les arguments d'une commande
 * @return le nombre de mots dans la chaine 
 */

int parseur(char* instruction, char* args[]) {
    int i = 0;
    int count = 0;
    while (instruction[i]) {
        while (instruction[i] == ' ') {
            i++;
        }
        if (instruction[i] == '\0') break;
        if (instruction[i] == '"') {
            i++;
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
            args[count] = &instruction[i];
            count++;
            while (instruction[i] && instruction[i] != ' ') {
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

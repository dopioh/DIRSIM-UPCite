#include <stdio.h>
#include <string.h>

#include "../utils/include/erreur.h"
#include "instr_man.h"

static int afficher_man(char* commande) {
    if (commande == NULL) return ERR_PARAMETRE_INVALIDE;

    if (strcmp(commande, "cd") == 0) {
        printf("cd  : descend a la racine.\ncd 'nom_dossier': descend dans le dossier.\ncd .. : remonte d'un niveau.\n");
    } else if (strcmp(commande, "cp") == 0) {
        printf("cp 'chem1' 'chem2': copie un fichier/dossier avec son contenu, dans le chemin souhaité.\n");
    } else if (strcmp(commande, "find") == 0) {
        printf("find / 'type' 'nom': cherche un element et donne son chemin.\n");
    } else if (strcmp(commande, "ls") == 0) {
        printf("ls : affiche les fichiers et les dossiers du dossier courant.\n");
    } else if (strcmp(commande, "mkdir") == 0) {
        printf("mkdir 'nom_dossier': cree un dossier.\n");
    } else if (strcmp(commande, "mv") == 0) {
        printf("mv 'chem1' 'chem2': deplace ou renomme un element.\n");
    } else if (strcmp(commande, "print") == 0) {
        printf("print : affiche toute l'arborescence du systeme.\n");
    } else if (strcmp(commande, "pwd") == 0) {
        printf("pwd : affiche le chemin du dossier courant.\n");
    } else if (strcmp(commande, "rm") == 0) {
        printf("rm 'nom': supprime un fichier ou un dossier et tous ses descendants.\n");
    } else if (strcmp(commande, "touch") == 0) {
        printf("touch 'nom_fichier': cree un fichier texte.\n");
    } else {
        printf("commande inconnue\n");
        return ERR_COMMANDE_INCONNUE;
    }

    return SUCCESS;
}

int instr_man(char* commande, contexte* ctx) {
    (void)ctx;
    if (commande == NULL || commande[0] == '\0') return ERR_PARAMETRE_INVALIDE;

    return afficher_man(commande);
}
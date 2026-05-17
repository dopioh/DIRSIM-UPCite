#include <stdio.h>
#include <string.h>

#include "../utils/include/erreur.h"
#include "../utils/include/color.h"
#include "instr_man.h"

void afficher_liste_commandes() {
    printf("========== MANUEL DES COMMANDES ==========\n");
    printf("Utilisation: man <commande>\n");
    printf("Commandes disponibles:\n");
    printf("  print, pwd, cd, touch, mkdir, ls, find, cp, mv, rm, history, load, save, man\n");
}

void afficher_man_cd() {
    printf("cd - changer de dossier courant\n");
    printf("Syntaxes:\n");
    printf("  cd\n");
    printf("  cd <chemin>\n");
    printf("Details:\n");
    printf("  - sans argument, va a la racine '/'.\n");
    printf("  - <chemin> accepte les chemins absolus et relatifs (., ..).\n");
}

void afficher_man_cp() {
    printf("cp - copier un noeud (fichier ou dossier)\n");
    printf("Syntaxe:\n");
    printf("  cp <source> <destination>\n");
    printf("Details:\n");
    printf("  - copie recursive si la source est un dossier.\n");
    printf("  - destination peut renommer la copie (ex: /a/fichier2).\n");
    printf("  - echec si le nom existe deja dans le dossier cible.\n");
}

void afficher_man_find() {
    printf("find - rechercher par nom dans un sous-arbre\n");
    printf("Syntaxes:\n");
    printf("  find <nom>\n");
    printf("  find <chemin_depart> <fichier|dossier> <nom>\n");
    printf("Details:\n");
    printf("  - find <nom>: cherche depuis le dossier courant, dans ses fichiers et ses dossiers.\n");
    printf("  - type obligatoire: 'fichier' ou 'dossier'.\n");
    printf("  - affiche chaque chemin trouve, un par ligne.\n");
}

void afficher_man_ls() {
    printf("ls - lister le contenu d'un dossier\n");
    printf("Syntaxes:\n");
    printf("  ls\n");
    printf("  ls <chemin>\n");
    printf("  ls -f [<chemin>]\n");
    printf("  ls -d [<chemin>]\n");
    printf("Details:\n");
    printf("  - ls: masque les elements caches (nom commencant par '.').\n");
    printf("  - -f / -fichier: affiche seulement les fichiers non caches.\n");
    printf("  - -d / -dossier: affiche seulement les dossiers.\n");
}

void afficher_man_mkdir() {
    printf("mkdir - creer un dossier\n");
    printf("Syntaxes:\n");
    printf("  mkdir <nom>\n");
    printf("  mkdir <chemin_parent> <nom>\n");
    printf("Details:\n");
    printf("  - <nom> alphanumerique uniquement (a-z, A-Z, 0-9).\n");
    printf("  - longueur max du nom: 99 caracteres.\n");
}

void afficher_man_mv() {
    printf("mv - deplacer ou renommer un noeud\n");
    printf("Syntaxe:\n");
    printf("  mv <source> <destination>\n");
    printf("Details:\n");
    printf("  - peut deplacer et/ou renommer.\n");
    printf("  - echec si destination existe deja.\n");
    printf("  - impossible de deplacer la racine.\n");
}

void afficher_man_print() {
    printf("print - afficher l'arborescence\n");
    printf("Syntaxe:\n");
    printf("  print\n");
}

void afficher_man_pwd() {
    printf("pwd - afficher le chemin du dossier courant\n");
    printf("Syntaxe:\n");
    printf("  pwd\n");
}

void afficher_man_rm() {
    printf("rm - supprimer un noeud\n");
    printf("Syntaxe:\n");
    printf("  rm <chemin>\n");
    printf("Details:\n");
    printf("  - supprime recursivement si c'est un dossier.\n");
    printf("  - impossible de supprimer la racine.\n");
}

void afficher_man_touch() {
    printf("touch - creer un fichier\n");
    printf("Syntaxes:\n");
    printf("  touch <nom>\n");
    printf("  touch <chemin_parent> <nom>\n");
    printf("Details:\n");
    printf("  - <nom> alphanumerique uniquement (a-z, A-Z, 0-9).\n");
    printf("  - longueur max du nom: 99 caracteres.\n");
}

void afficher_man_history() {
    printf("history - afficher l'historique des commandes\n");
    printf("Syntaxe:\n");
    printf("  history\n");
}

void afficher_man_load() {
    printf("load - executer des commandes depuis un fichier externe\n");
    printf("Syntaxe:\n");
    printf("  load <fichier>\n");
    printf("Details:\n");
    printf("  - execute chaque ligne du fichier.\n");
}

void afficher_man_save() {
    printf("save - sauvegarder les commandes tappées dans un fichier\n");
    printf("Syntaxe:\n");
    printf("  save <fichier>\n");
    printf("Details:\n");
    printf("  - ecrit les commandes qui impactent l'arborescence, une par ligne.\n");
}

void afficher_man_man() {
    printf("man - manuel des commandes\n");
    printf("Syntaxes:\n");
    printf("  man\n");
    printf("  man <commande>\n");
}

int afficher_man(char* commande) {
    printf(YEL);
    if (commande == NULL || commande[0] == '\0') {
        afficher_liste_commandes();
        printf(reset);
        return SUCCESS;
    }

    if (strcmp(commande, "cd") == 0) {
        afficher_man_cd();
    } else if (strcmp(commande, "cp") == 0) {
        afficher_man_cp();
    } else if (strcmp(commande, "find") == 0) {
        afficher_man_find();
    } else if (strcmp(commande, "ls") == 0) {
        afficher_man_ls();
    } else if (strcmp(commande, "mkdir") == 0) {
        afficher_man_mkdir();
    } else if (strcmp(commande, "mv") == 0) {
        afficher_man_mv();
    } else if (strcmp(commande, "print") == 0) {
        afficher_man_print();
    } else if (strcmp(commande, "pwd") == 0) {
        afficher_man_pwd();
    } else if (strcmp(commande, "rm") == 0) {
        afficher_man_rm();
    } else if (strcmp(commande, "touch") == 0) {
        afficher_man_touch();
    } else if (strcmp(commande, "history") == 0) {
        afficher_man_history();
    } else if (strcmp(commande, "load") == 0) {
        afficher_man_load();
    } else if (strcmp(commande, "save") == 0) {
        afficher_man_save();
    } else if (strcmp(commande, "man") == 0) {
        afficher_man_man();
    } else {
        printf("commande inconnue: %s\n", commande);
        printf("Utilise 'man' pour la liste des commandes.\n");
        return ERR_COMMANDE_INCONNUE;
    }

    printf(reset);
    return SUCCESS;
}

int instr_man(char* commande, contexte* ctx) {
    (void)ctx;
    return afficher_man(commande);
}

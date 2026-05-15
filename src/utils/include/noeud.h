#ifndef NOEUD_H
#define NOEUD_H

struct noeud {
    int est_dossier; // 1 pour true, 0 pour false
    char nom[100];
    struct noeud* pere;
    struct noeud* racine;
    struct liste_noeud* fils;
};

typedef struct noeud noeud;

#endif
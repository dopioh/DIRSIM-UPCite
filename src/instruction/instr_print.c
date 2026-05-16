#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/include/noeud.h"
#include "../utils/include/liste_noeud.h"
#include "../utils/include/clear.h"
#include "../utils/include/erreur.h"
#include "instr_print.h"

static void print_node(noeud* n) {
	if (n == NULL) return;

	const char* nom = (n->nom[0] == '\0') ? "/" : n->nom;
	const char* type = (n->est_dossier) ? "D" : "F";

	int nombre_fils = 0;
	liste_noeud* courant = n->fils;
	while (courant != NULL) {
		nombre_fils++;
		courant = courant->succ;
	}

	if (n->pere == n) {
		printf("Noeud %s ( %s ) , %d fils", nom, type, nombre_fils);
	} else {
		const char* pere = (n->pere->nom[0] == '\0') ? "/" : n->pere->nom;
		printf("Noeud %s ( %s ) , pere : %s , %d fils", nom, type, pere, nombre_fils);
	}

	if (nombre_fils > 0) {
		printf(" : ");
		courant = n->fils;
		int premier = 1;
		while (courant != NULL) {
			if (!premier) printf(" , ");
			const char* nom_fils = (courant->no->nom[0] == '\0') ? "/" : courant->no->nom;
			const char* type_fils = (courant->no->est_dossier) ? "D" : "F";
			printf("%s ( %s )", nom_fils, type_fils);
			premier = 0;
			courant = courant->succ;
		}
	}

	printf("\n");
}

static void affiche_arbre(noeud* n) {
	if (n == NULL) return;
	print_node(n);
	liste_noeud* courant = n->fils;
	while (courant != NULL) {
		affiche_arbre(courant->no);
		courant = courant->succ;
	}
}

int instr_print(contexte* ctx) {
	if (ctx == NULL || ctx->noeud_racine == NULL){
        return ERR_PARAMETRE_INVALIDE;
	}

	affiche_arbre(ctx->noeud_racine);
	return SUCCESS;
}

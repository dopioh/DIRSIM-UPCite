# c-dirsim

Simulateur de système de fichiers en C.
Ecrit par MAZRI Nassim & WU Billy

## Prérequis

- `gcc`
- `make`
- `valgrind`

## Compilation

```bash
make
```

Génère l'exécutable:

```text
build/bin/programme
```

## Exécution

Mode interactif:

```bash
./build/bin/programme
```

Mode fichier d'instructions:

```bash
./build/bin/programme instructions.txt
```


## Commandes Make utiles

```bash
make            # compile
make run        # lance en mode intéractif
make clean      # supprime l'exécutable
make test-mem   # execute la commande valgrind du sujet
```

## Commandes disponibles

| Commande | Syntaxe | Explication |
|---|---|---|
| `print` | `print` | Affiche toute l'arborescence. |
| `pwd` | `pwd` | Affiche le chemin du dossier courant. |
| `cd` | `cd` ou `cd <chemin>` | Change le dossier courant. Sans argument, va à la racine `/`. |
| `mkdir` | `mkdir <nom>` ou `mkdir <chemin> <nom>` | Crée un dossier. |
| `touch` | `touch <nom>` ou `touch <chemin> <nom>` | Crée un fichier. |
| `ls` | `ls`, `ls <chemin>`, `ls -f [<chemin>]`, `ls -fichier [<chemin>]`, `ls -d [<chemin>]`, `ls -dossier [<chemin>]` | Liste le contenu d'un dossier avec filtres. |
| `find` | `find <nom>` ou `find <chemin> <fichier\|dossier> <nom>` | Recherche un nom et affiche les chemins trouvés. |
| `cp` | `cp <source> <destination>` | Copie un fichier ou un dossier (récursif pour dossier). |
| `mv` | `mv <source> <destination>` | Déplace ou renomme un fichier/dossier. |
| `rm` | `rm <chemin>` | Supprime un fichier/dossier (récursif pour dossier). |
| `history` | `history` | Affiche l'historique des commandes. |
| `save` | `save <fichier>` | Sauvegarde les commandes déjà executées (et qui impactent l'arborescence). |
| `load` | `load <fichier>` | Exécute les commandes contenues dans un fichier. |
| `man` | `man` ou `man <commande>` | Affiche l'aide générale ou le manuel d'une commande. |


## Jeu de tests

Un dossier `tests/` contient des fichiers d'instructions prêts à lancer:

```bash
./build/bin/programme tests/test_01.txt
```

## Ressources

- [Chronomètre C (Developpez)](https://c.developpez.com/faq/?page=Gestion-des-dates-et-heures)
- [Couleurs ANSI (Gist)](https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a)
- [Documentation C (IBM)](https://ibm.com)
- [Documentation C (koor.fr)](https://koor.fr/)
- [Makefile (UCLouvain)](https://sites.uclouvain.be/SystInfo/notes/Outils/make.html)

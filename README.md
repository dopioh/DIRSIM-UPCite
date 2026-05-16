# c-dirsim

Simulateur de commandes de type système de fichiers, écrit en C par MAZRI Nassim et WU Billy.

## Prerequis

- Compilateur C
- Commande `make`
- Commande `valgrind`

## Compiler le projet

La compilation se fait avec:

```bash
make
```

`make` lance la commande `main` du `Makefile`:

- création du dossier `build/bin` (si il n'existe pas déjà)
- compile les fichiers `.c` du projet
- genere l'executable `build/bin/programme`

## Lancer le programme

Pour executer le binaire avec le fichier d'instructions:

```bash
make run
```

La commande lance:

```bash
./build/bin/programme instructions.txt
```
> si votre le fichier d'instruction ne s'appelle pas ```instructions.txt```, executer le programme sans ```make run``` et avec le bon nom de votre fichier d'instruction

## Commandes disponibles

```text
print
pwd
cd <chemin>
touch <nom>
touch <chemin> <nom>
mkdir <nom>
mkdir <chemin> <nom>
ls
ls <chemin>
ls -f
ls -f <chemin>
ls -fichier
ls -fichier <chemin>
ls -d
ls -d <chemin>
ls -dossier
ls -dossier <chemin>
find <chemin> <fichier|dossier> <nom>
```


- Les noms pour `touch` et `mkdir` sont alphanumeriques uniquement (`a-z`, `A-Z`, `0-9`).
- Les noms pour `touch` et `mkdir` sont limites a 99 caracteres.
- Les chemins peuvent etre absolus (`/a/b`) ou relatifs (`a/b`, `.`, `..`).

## Nettoyer les fichiers de build

Pour supprimer le dernier executable:

```bash
make clean
```

## Verification memoire (avec Valgrind)
Tester le programme avec la commande Valgrind du sujet
```bash
make test-mem
```


## Compilation manuelle

Pour compiler sans ```make```

```bash
gcc -Wall -Wextra -g -o build/bin/programme src/*.c src/utils/*.c src/instruction/*.c
```

## Ressources utilisées
- [Chronometre C (Developpez)](https://c.developpez.com/faq/?page=Gestion-des-dates-et-heures) | pour le temps d'éxécution des commandes dans les journaux

- [Couleurs ASCII (Gist)](https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a) | pour les différentes couleurs sur les sorties du programme

- [Documentation C (ibm.com)](https://ibm.com) et [Documentation C (koor.fr)](https://koor.fr/)


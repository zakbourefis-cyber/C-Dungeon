# C-Dungeon

Petit RPG en terminal développé en C avec **ncursesw**.

## Prérequis

Sous Debian / Ubuntu / WSL :

```sh
sudo apt update
sudo apt install build-essential libncursesw5-dev
```

## Compiler et tester

```sh
make clean
make
make test
```

La commande `make` construit la bibliothèque statique `libListeElement.a` et le programme de tests `test_liste`.

## Lancer le jeu

```sh
make game
./c-dungeon
```

Ou directement :

```sh
make run
```

Le jeu nécessite un terminal d'au moins 80 colonnes et 24 lignes. Les chemins des fichiers de décor sont relatifs à la racine du dépôt.

## Nettoyer

```sh
make clean
```

## Organisation

- `include/` : fichiers d'en-tête (structures et prototypes).
- `src/liste_element.c` : opérations sur la liste chaînée d'éléments.
- `src/entity.c` : joueur et inventaire.
- `src/display.c` : affichage ncursesw.
- `src/game_main.c` : point d'entrée du jeu.
- `src/main.c` et `tests/` : programme de tests de la liste.

Le projet contient deux listes chaînées distinctes pour le moment : `Element` (bibliothèque de données) et `Item` (inventaire du joueur). Leur éventuelle unification pourra être faite dans une étape dédiée afin de ne pas mélanger les responsabilités.

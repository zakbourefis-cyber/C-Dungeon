#ifndef ENTITY_H
#define ENTITY_H

typedef struct Item {
    char nom[50];
    int valeur;
    struct Item* next;
} Item;

typedef struct Joueur {
    char nom[50];
    int hp;
    int max_hp;
    int mana;
    int max_mana;
    int gold;
    Item* inventaire;
} Joueur;

void initialiser_joueur(Joueur* j, const char* nom);
void ajouter_inventaire(Joueur* j, const char* nom_item, int valeur);
void afficher_inventaire(const Joueur* j);
void liberer_inventaire(Joueur* j);

#endif

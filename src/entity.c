#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entity.h"

void initialiser_joueur(Joueur *j, const char *nom)
{
    if (j == NULL) {
        return;
    }

    memset(j, 0, sizeof(*j));
    if (nom != NULL) {
        strncpy(j->nom, nom, sizeof(j->nom) - 1);
    }

    j->hp = 100;
    j->max_hp = 100;
    j->mana = 50;
    j->max_mana = 50;
    j->gold = 50;
}

void ajouter_inventaire(Joueur *j, const char *nom_item, int valeur)
{
    Item *nouveau;
    Item *dernier;

    if (j == NULL || nom_item == NULL) {
        return;
    }

    nouveau = malloc(sizeof(*nouveau));
    if (nouveau == NULL) {
        perror("Impossible d'ajouter l'objet à l'inventaire");
        return;
    }

    strncpy(nouveau->nom, nom_item, sizeof(nouveau->nom) - 1);
    nouveau->nom[sizeof(nouveau->nom) - 1] = '\0';
    nouveau->valeur = valeur;
    nouveau->next = NULL;

    if (j->inventaire == NULL) {
        j->inventaire = nouveau;
        return;
    }

    dernier = j->inventaire;
    while (dernier->next != NULL) {
        dernier = dernier->next;
    }
    dernier->next = nouveau;
}

void afficher_inventaire(const Joueur *j)
{
    const Item *item;
    int numero = 1;

    if (j == NULL) {
        return;
    }

    printf("--- INVENTAIRE DE %s ---\n", j->nom);
    item = j->inventaire;
    if (item == NULL) {
        puts("  (Inventaire vide)");
        return;
    }

    while (item != NULL) {
        printf("  %d. %s (Effet/Valeur : %d)\n",
               numero, item->nom, item->valeur);
        item = item->next;
        numero++;
    }
}

void liberer_inventaire(Joueur *j)
{
    Item *actuel;

    if (j == NULL) {
        return;
    }

    actuel = j->inventaire;
    while (actuel != NULL) {
        Item *suivant = actuel->next;
        free(actuel);
        actuel = suivant;
    }
    j->inventaire = NULL;
}

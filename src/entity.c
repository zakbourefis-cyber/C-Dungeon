#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/entity.h"

void initialiser_joueur(Joueur* j, const char* nom) {
    if (j == NULL) return;
    
    strncpy(j->nom, nom, sizeof(j->nom) - 1);
    j->nom[sizeof(j->nom) - 1] = '\0';
    j->hp = 100;
    j->max_hp = 100;
    j->mana = 50;
    j->max_mana = 50;
    j->gold = 50;
    j->inventaire = NULL; // L'inventaire commence vide
}

void ajouter_inventaire(Joueur* j, const char* nom_item, int valeur) {
    if (j == NULL) return;

    // Allocation dynamique d'un nouvel objet
    Item* nouveau = (Item*)malloc(sizeof(Item));
    if (nouveau == NULL) {
        exit(EXIT_FAILURE);
    }

    strncpy(nouveau->nom, nom_item, sizeof(nouveau->nom) - 1);
    nouveau->nom[sizeof(nouveau->nom) - 1] = '\0';
    nouveau->valeur = valeur;
    nouveau->next = NULL;

    // Si l'inventaire est vide, le nouvel objet devient la tête
    if (j->inventaire == NULL) {
        j->inventaire = nouveau;
    } else {
        // Sinon, on parcourt la liste jusqu'au dernier élément
        Item* temp = j->inventaire;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nouveau;
    }
}

void afficher_inventaire(const Joueur* j) {
    if (j == NULL) return;

    printf("--- INVENTAIRE DE %s ---\n", j->nom);
    if (j->inventaire == NULL) {
        printf("  (Inventaire vide)\n");
        return;
    }

    Item* temp = j->inventaire;
    int i = 1;
    while (temp != NULL) {
        printf("  %d. %s (Effet/Valeur : %d)\n", i, temp->nom, temp->valeur);
        temp = temp->next;
        i++;
    }
}

void liberer_inventaire(Joueur* j) {
    if (j == NULL) return;

    Item* actuel = j->inventaire;
    while (actuel != NULL) {
        Item* suivant = actuel->next;
        free(actuel); // Libération dynamique de chaque objet
        actuel = suivant;
    }
    j->inventaire = NULL;
}
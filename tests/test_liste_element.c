
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liste_element.h"

void afficher_resultat(const char *nomTest, int reussi)
{
    if (reussi) {
        printf("[REUSSI] %s\n", nomTest);
    } else {
        printf("[ECHEC]  %s\n", nomTest);
    }
}

/* Test de l'ajout en tête */
void tester_ajout_tete(void)
{
    Element *liste = NULL;

    ajouterElement(&liste, "Potion", "Soin", 20);
    ajouterElement(&liste, "Epee", "Arme", 10);

    int reussi = liste != NULL
        && strcmp(liste->nom, "Epee") == 0
        && liste->suivant != NULL
        && strcmp(liste->suivant->nom, "Potion") == 0;

    afficher_resultat("Ajout en tete", reussi);
    libererListeElements(liste);
}

/* Test de l'ajout en fin */
void tester_ajout_fin(void)
{
    Element *liste = NULL;

    ajouterElementFin(&liste, "Potion", "Soin", 20);
    ajouterElementFin(&liste, "Epee", "Arme", 10);

    int reussi = liste != NULL
        && strcmp(liste->nom, "Potion") == 0
        && liste->suivant != NULL
        && strcmp(liste->suivant->nom, "Epee") == 0
        && liste->suivant->suivant == NULL;

    afficher_resultat("Ajout en fin", reussi);
    libererListeElements(liste);
}

/* Test de la recherche par nom */
void tester_recherche_nom(void)
{
    Element *liste = NULL;

    ajouterElementFin(&liste, "Potion", "Soin", 20);
    ajouterElementFin(&liste, "Epee", "Arme", 10);

    Element *resultat = rechercherElementNom(liste, "Epee");

    int reussi = resultat != NULL
        && strcmp(resultat->nom, "Epee") == 0;

    afficher_resultat("Recherche par nom", reussi);

    resultat = rechercherElementNom(liste, "ObjetInexistant");
    afficher_resultat("Recherche d'un nom inexistant", resultat == NULL);

    libererListeElements(liste);
}

/* Test de la recherche par indice */
void tester_recherche_indice(void)
{
    Element *liste = NULL;

    ajouterElementFin(&liste, "Potion", "Soin", 20);
    ajouterElementFin(&liste, "Epee", "Arme", 10);

    Element *premier = rechercherElementIndice(liste, 0);
    Element *deuxieme = rechercherElementIndice(liste, 1);
    Element *inexistant = rechercherElementIndice(liste, 2);

    afficher_resultat(
        "Recherche par indice 0",
        premier != NULL && strcmp(premier->nom, "Potion") == 0
    );

    afficher_resultat(
        "Recherche par indice 1",
        deuxieme != NULL && strcmp(deuxieme->nom, "Epee") == 0
    );

    afficher_resultat(
        "Recherche par indice inexistant",
        inexistant == NULL
    );

    libererListeElements(liste);
}

/* Test de la suppression */
void tester_suppression(void)
{
    Element *liste = NULL;

    ajouterElementFin(&liste, "Potion", "Soin", 20);
    ajouterElementFin(&liste, "Epee", "Arme", 10);
    ajouterElementFin(&liste, "Bouclier", "Armure", 15);

    /* Suppression au milieu */
    supprimerElement(&liste, "Epee");

    int milieu_reussi =
        rechercherElementNom(liste, "Epee") == NULL
        && liste->suivant != NULL
        && strcmp(liste->suivant->nom, "Bouclier") == 0;

    afficher_resultat("Suppression au milieu", milieu_reussi);

    /* Suppression en tete */
    supprimerElement(&liste, "Potion");

    int tete_reussi = liste != NULL
        && strcmp(liste->nom, "Bouclier") == 0;

    afficher_resultat("Suppression en tete", tete_reussi);

    /* Suppression du dernier élément */
    supprimerElement(&liste, "Bouclier");

    afficher_resultat("Suppression du dernier element", liste == NULL);

    /* Suppression d'un élément inexistant */
    supprimerElement(&liste, "Inexistant");

    afficher_resultat("Suppression d'un element inexistant", liste == NULL);

    libererListeElements(liste);
}

/* Test du tirage aléatoire */
void tester_tirage_aleatoire(void)
{
    Element *liste = NULL;

    Element *resultat_vide = tirageAleatoireElement(liste);

    afficher_resultat("Tirage dans une liste vide", resultat_vide == NULL);

    ajouterElementFin(&liste, "Potion", "Soin", 20);
    ajouterElementFin(&liste, "Epee", "Arme", 10);
    ajouterElementFin(&liste, "Bouclier", "Armure", 15);

    Element *resultat = tirageAleatoireElement(liste);

    int appartient_liste = 0;

    Element *actuel = liste;
    while (actuel != NULL) {
        if (actuel == resultat) {
            appartient_liste = 1;
            break;
        }
        actuel = actuel->suivant;
    }

    afficher_resultat("Tirage d'un element existant", appartient_liste);

    libererListeElements(liste);
}

/* Test de l'affichage */
void tester_affichage(void)
{
    Element *liste = NULL;

    ajouterElementFin(&liste, "Potion", "Soin", 20);
    ajouterElementFin(&liste, "Epee", "Arme", 10);

    printf("\n--- Affichage de la liste ---\n");
    afficherElements(liste);
    printf("-----------------------------\n");

    afficher_resultat("Affichage de la liste (verification visuelle)", 1);

    libererListeElements(liste);
}

/* Fonction appelée depuis src/main.c */
void test_liste_chainee(void)
{
    printf("\n========== TESTS LISTE CHAINEE ==========\n\n");

    tester_ajout_tete();
    tester_ajout_fin();
    tester_recherche_nom();
    tester_recherche_indice();
    tester_suppression();
    tester_tirage_aleatoire();
    tester_affichage();

    printf("\n========== FIN DES TESTS ================\n");
}

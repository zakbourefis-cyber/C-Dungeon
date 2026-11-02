#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "liste_element.h"

static void verifier_ajout_en_tete(void)
{
    Element *liste = NULL;

    ajouterElement(&liste, "Potion", "Soin", 20);
    ajouterElement(&liste, "Gobelin", "Monstre", 12);

    assert(liste != NULL);
    assert(strcmp(liste->nom, "Gobelin") == 0);
    assert(strcmp(liste->type, "Monstre") == 0);
    assert(liste->valeur == 12);
    assert(liste->suivant != NULL);
    assert(strcmp(liste->suivant->nom, "Potion") == 0);
    assert(liste->suivant->valeur == 20);

    libererListeElements(liste);
}

static void verifier_ajout_en_fin(void)
{
    Element *liste = NULL;

    ajouterElementFin(&liste, "Potion", "Soin", 20);
    ajouterElementFin(&liste, "Piege", "Environnement", 18);

    assert(liste != NULL);
    assert(strcmp(liste->nom, "Potion") == 0);
    assert(liste->valeur == 20);
    assert(liste->suivant != NULL);
    assert(strcmp(liste->suivant->nom, "Piege") == 0);
    assert(liste->suivant->valeur == 18);
    assert(liste->suivant->suivant == NULL);

    libererListeElements(liste);
}

static void verifier_recherches(void)
{
    Element *liste = NULL;

    ajouterElementFin(&liste, "Potion", "Soin", 20);
    ajouterElementFin(&liste, "Gobelin", "Monstre", 12);

    assert(rechercherElementNom(liste, "Gobelin") == liste->suivant);
    assert(rechercherElementNom(liste, "Inconnu") == NULL);
    assert(rechercherElementNom(liste, NULL) == NULL);
    assert(rechercherElementIndice(liste, 0) == liste);
    assert(rechercherElementIndice(liste, 1) == liste->suivant);
    assert(rechercherElementIndice(liste, 2) == NULL);

    libererListeElements(liste);
}

static void verifier_suppression(void)
{
    Element *liste = NULL;

    ajouterElementFin(&liste, "Potion", "Soin", 20);
    ajouterElementFin(&liste, "Gobelin", "Monstre", 12);
    ajouterElementFin(&liste, "Piege", "Environnement", 18);

    supprimerElement(&liste, "Gobelin");
    assert(liste != NULL);
    assert(strcmp(liste->nom, "Potion") == 0);
    assert(liste->suivant != NULL);
    assert(strcmp(liste->suivant->nom, "Piege") == 0);

    supprimerElement(&liste, "Potion");
    assert(liste != NULL);
    assert(strcmp(liste->nom, "Piege") == 0);

    supprimerElement(&liste, "Piege");
    assert(liste == NULL);

    libererListeElements(liste);
}

static void verifier_tirage_aleatoire(void)
{
    Element *liste = NULL;
    Element *elementTire;

    ajouterElementFin(&liste, "Potion", "Soin", 20);
    elementTire = tirageAleatoireElement(liste);

    assert(elementTire == liste);
    assert(tirageAleatoireElement(NULL) == NULL);

    libererListeElements(liste);
}

void test_liste_chainee(void)
{
    verifier_ajout_en_tete();
    verifier_ajout_en_fin();
    verifier_recherches();
    verifier_suppression();
    verifier_tirage_aleatoire();
    puts("Tous les tests ok");
}

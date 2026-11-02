#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liste_element.h"

static Element *creer_element(const char *nomElement, const char *nomType, int valeur)
{
    Element *element;

    if (nomElement == NULL || nomType == NULL) {
        return NULL;
    }

    element = malloc(sizeof(*element));
    if (element == NULL) {
        perror("Erreur d'allocation de mémoire");
        return NULL;
    }

    strncpy(element->nom, nomElement, TAILLE_NOM_ELEMENT - 1);
    element->nom[TAILLE_NOM_ELEMENT - 1] = '\0';
    strncpy(element->type, nomType, TAILLE_TYPE_ELEMENT - 1);
    element->type[TAILLE_TYPE_ELEMENT - 1] = '\0';
    element->valeur = valeur;
    element->suivant = NULL;

    return element;
}

void ajouterElement(Element **liste, const char *nomElement, const char *nomType, int valeur)
{
    Element *nouvelElement;

    if (liste == NULL) {
        return;
    }

    nouvelElement = creer_element(nomElement, nomType, valeur);
    if (nouvelElement == NULL) {
        return;
    }

    nouvelElement->suivant = *liste;
    *liste = nouvelElement;
}

void ajouterElementFin(Element **liste, const char *nomElement, const char *nomType, int valeur)
{
    Element *nouvelElement;
    Element *dernierElement;

    if (liste == NULL) {
        return;
    }

    nouvelElement = creer_element(nomElement, nomType, valeur);
    if (nouvelElement == NULL) {
        return;
    }

    strncpy(nouvelElement->nom, nomElement, TAILLE_NOM_ELEMENT - 1);
    nouvelElement->nom[TAILLE_NOM_ELEMENT - 1] = '\0';
    strncpy(nouvelElement->type, nomType, TAILLE_TYPE_ELEMENT - 1);
    nouvelElement->type[TAILLE_TYPE_ELEMENT - 1] = '\0';
    nouvelElement->suivant = NULL;

    if (*liste == NULL) {
        *liste = nouvelElement;
        return;
    }

    dernierElement = *liste;
    while (dernierElement->suivant != NULL) {
        dernierElement = dernierElement->suivant;
    }
    dernierElement->suivant = nouvelElement;
}

void supprimerElement(Element **liste, const char *nomElement)
{
    Element *elementActuel;
    Element *elementPrecedent = NULL;

    if (liste == NULL || nomElement == NULL) {
        return;
    }

    elementActuel = *liste;
    while (elementActuel != NULL &&
           strcmp(elementActuel->nom, nomElement) != 0) {
        elementPrecedent = elementActuel;
        elementActuel = elementActuel->suivant;
    }

    if (elementActuel == NULL) {
        return;
    }

    if (elementPrecedent == NULL) {
        *liste = elementActuel->suivant;
    } else {
        elementPrecedent->suivant = elementActuel->suivant;
    }

    free(elementActuel);
}

void afficherElements(const Element *liste)
{
    const Element *elementActuel = liste;

    while (elementActuel != NULL) {
        printf("Nom : %s | Type : %s | Valeur : %d\n",
               elementActuel->nom,
               elementActuel->type);
               elementActuel->valeur;
        elementActuel = elementActuel->suivant;
    }
}

void libererListeElements(Element *liste)
{
    while (liste != NULL) {
        Element *suivant = liste->suivant;
        free(liste);
        liste = suivant;
    }
}

Element *rechercherElementNom(Element *liste, const char *nomElement)
{
    if (nomElement == NULL) {
        return NULL;
    }

    while (liste != NULL) {
        if (strcmp(liste->nom, nomElement) == 0) {
            return liste;
        }
        liste = liste->suivant;
    }

    return NULL;
}

Element *rechercherElementIndice(Element *liste, size_t indice)
{
    size_t indiceActuel = 0;

    while (liste != NULL && indiceActuel < indice) {
        liste = liste->suivant;
        indiceActuel++;
    }

    return liste;
}

Element *tirageAleatoireElement(Element *liste)
{
    Element *elementActuel;
    size_t nombreElements = 0;

    for (elementActuel = liste;
         elementActuel != NULL;
         elementActuel = elementActuel->suivant) {
        nombreElements++;
    }

    if (nombreElements == 0) {
        return NULL;
    }

    return rechercherElementIndice(liste, (size_t)rand() % nombreElements);
}

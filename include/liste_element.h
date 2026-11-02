#ifndef LISTE_ELEMENT_H
#define LISTE_ELEMENT_H

#include <stddef.h>

#define TAILLE_NOM_ELEMENT 50
#define TAILLE_TYPE_ELEMENT 50

/**
 * @brief Élément d'une liste chaînée
 */
typedef struct Element {
    char nom[TAILLE_NOM_ELEMENT];
    char type[TAILLE_TYPE_ELEMENT];
    int valeur;
    struct Element *suivant;
} Element;

/**
 * @brief Ajoute un élément au début de la liste
 *
 * @param liste Adresse du pointeur vers le premier élément de la liste
 * @param nomElement Nom du nouvel élément
 * @param nomType Type du nouvel élément
 */
void ajouterElement(Element **liste, const char *nomElement, const char *nomType, int valeur);

/**
 * @brief Ajoute un élément à la fin de la liste.
 *
 * @param liste Adresse du pointeur vers le premier élément de la liste.
 * @param nomElement Nom du nouvel élément.
 * @param nomType Type du nouvel élément.
 */
void ajouterElementFin(Element **liste, const char *nomElement, const char *nomType, int valeur);

/**
 * @brief Supprime le premier élément ayant le nom indiqué.
 *
 * @param liste Adresse du pointeur vers le premier élément de la liste.
 * @param nomElement Nom de l'élément à supprimer.
 */
void supprimerElement(Element **liste, const char *nomElement);

/**
 * @brief Affiche tous les éléments de la liste.
 *
 * @param liste Premier élément de la liste à afficher.
 */
void afficherElements(const Element *liste);

/**
 * @brief Libère tous les éléments de la liste.
 *
 * @param liste Premier élément de la liste à libérer.
 */
void libererListeElements(Element *liste);

/**
 * @brief Recherche le premier élément correspondant à un nom.
 *
 * @param liste Premier élément de la liste à parcourir.
 * @param nomElement Nom recherché.
 * @return Élément trouvé ou NULL si aucun élément ne correspond.
 */
Element *rechercherElementNom(Element *liste, const char *nomElement);

/**
 * @brief Recherche un élément à partir de son indice.
 *
 * @param liste Premier élément de la liste à parcourir.
 * @param indice Indice recherché, à partir de 0.
 * @return Élément trouvé ou NULL si l'indice est invalide.
 */
Element *rechercherElementIndice(Element *liste, size_t indice);

/**
 * @brief Retourne un élément choisi aléatoirement.
 *
 * @param liste Premier élément de la liste à parcourir.
 * @return Élément choisi ou NULL si la liste est vide.
 */
Element *tirageAleatoireElement(Element *liste);

#endif

typedef struct Item {
    char nom[50]; // Nom de l'objet
    int valeur; // Valeur de l'objet
    struct Item* next; // Pointeur vers l'objet suivant 
} Item;

typedef struct Joueur {
    char nom[50]; // Nom du héros
    int hp; // Points de vie actuels
    int max_hp; // Points de vie maximum
    int mana; // Points de mana actuels
    int max_mana; // Points de mana maximum
    int gold; // Quantité d'or possédée
    Item* inventaire; // Pointeur vers le premier élément de l'inventaire
} Joueur;

void initialiser_joueur(Joueur* j, const char* nom);
void ajouter_inventaire(Joueur* j, const char* nom_item, int valeur);
void afficher_inventaire(const Joueur* j);
void liberer_inventaire(Joueur* j);

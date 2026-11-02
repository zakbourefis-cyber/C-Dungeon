#include <stdlib.h>
#include <time.h>

#include "entity.h"
#include "display.h"

int main(void)
{
    Joueur joueur;

    srand((unsigned int)time(NULL));
    initialiser_joueur(&joueur, "Aventurier");
    ajouter_inventaire(&joueur, "Potion de soin", 25);
    ajouter_inventaire(&joueur, "Epee rouillee", 10);

    if (display_init() != 0) {
        liberer_inventaire(&joueur);
        return EXIT_FAILURE;
    }

    display_render(
        &joueur,
        "include/assets/environnement/desert.txt",
        "Squelette",
        "include/assets/monsters/Squelette.txt",
        25,
        30,
        "Bienvenue dans C-Dungeon !"
    );

    display_get_action();

    display_shutdown();
    liberer_inventaire(&joueur);

    return EXIT_SUCCESS;
}

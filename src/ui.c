#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/entity.h"
#include "../include/ui.h"


void afficher_ui(Joueur* j){
    printf("%s", separation);
    printf("Hero : %s\n", j->nom);
    printf("[HP] : %d/%d\n", j->hp,j->max_hp);
    printf("[MANA] : %d/%d\n", j->mana,j->max_mana);
    printf("[OR] : %d\n", j->gold);
    afficher_inventaire(j);
    printf("%s", separation);
}
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "grille.h"
#include "map.h"

#define COLONNE 10
#define LIGNE 10

static char **game_map = NULL; 
static char caractere; 

void map_init() {
    // allocation
    game_map = (char **)malloc(LIGNE * sizeof(char *));
    for (int i = 0; i < LIGNE; i++) {
        game_map[i] = (char *)malloc(COLONNE * sizeof(char));
    }

    // initialisation
    for (int i = 0; i < LIGNE; i++) {
        for (int j = 0; j < COLONNE; j++) {
            game_map[i][j] = ' ';
        }
    }
}

void map_print() {  // print la carte
    grille_print(game_map, COLONNE, LIGNE);
}

void map_free() {  // libère la mémoire
    for (int i = 0; i < LIGNE; i++) {
        free(game_map[i]);
    }
    free(game_map);
}

int get_colonne() {
    return COLONNE;
}

int get_ligne() {
    return LIGNE;
}

int get_case() {
    return caractere;
}

void set_case(char lettre) {
    caractere = lettre;
}

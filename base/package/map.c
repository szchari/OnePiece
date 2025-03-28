#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "map.h"
#include "grille.h"

#define COLONNE 10
#define LIGNE 10

static char **game_map = NULL; 
static char caractere; 

extern void map_init() {
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

extern void map_print() {  // print la carte
    grille_print(game_map, COLONNE, LIGNE);
}

extern void map_free() {  // libère la mémoire
    for (int i = 0; i < LIGNE; i++) {
        free(game_map[i]);
    }
    free(game_map);
}

extern int get_colonne() {
    return COLONNE;
}

extern int get_ligne() {
    return LIGNE;
}

extern char get_case(int posx, int posy) {
    return game_map[posx][posy];
}

extern void set_case(int posx, int posy, char lettre) {
    game_map[posx][posy] = lettre;
}

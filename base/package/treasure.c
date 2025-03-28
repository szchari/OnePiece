#include "treasure.h"
#include "coord.h"
#include <stdlib.h>
#include "map.h"
#include <time.h>
#include "player.h"

// Instance unique de Treasure
static Coord treasure = {0, 0}; // Initialisation par défaut
static int initialized = 0; // Flag pour éviter une réinitialisation multiple


// Initialise la position du trésor (une seule fois)
extern void treasure_init() {
    if (!initialized) {
        treasure.x = rand() % get_ligne();
        treasure.y = rand() % get_colonne();
        initialized = 1; // Marquer comme initialisé
    }
}

// Retourne la position du trésor
extern Coord treasure_get_pos(void) {
    return treasure;
}

extern int verifVictoire(Player* player){
    Coord coordj = player_get_pos(player);
    if (treasure.x == coordj.x && treasure.y == coordj.y){
        return 1;
    }
    return 0;
}


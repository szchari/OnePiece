#include "treasure.h"
#include "coord.h"
#include <stdlib.h>
#include "map.h"
#include <time.h>

// Instance unique de Treasure
static Coord treasure = {0, 0}; // Initialisation par défaut
static int initialized = 0; // Flag pour éviter une réinitialisation multiple


// Initialise la position du trésor (une seule fois)
void treasure_init() {
    if (!initialized) {
        treasure.x = rand() % get_ligne();
        treasure.y = rand() % get_colonne();
        initialized = 1; // Marquer comme initialisé
    }
}

// Retourne la position du trésor
Coord treasure_get_pos(void) {
    return treasure;
}


#include "coord.h" 
#include "player.h"
#include "treasure.h"
#include "map.h"
#include <time.h>
#include <stdlib.h>

static int initialized = 0; 

extern void initialisation(){
    if (!initialized){
        srand(time(NULL)); // Initialisation du générateur aléatoire
        treasure_init();
        map_init();
        initialized = 1;
    }
}

extern int verifVictoire(Player* player, Coord treasure){
    Coord coordj = player_get_pos(player);
    if (treasure.x == coordj.x && treasure.y == coordj.y){
        return 1;
    }
    return 0;
}
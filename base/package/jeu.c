#include "jeu.h"
#include "coord.h" 
#include "player.h"
#include "treasure.h"
#include "map.h"
#include "piege.h"
#include "pirate.h"
#include <time.h>
#include <stdlib.h>
#include "piege.h"
#include "piegelist.h"
#include <assert.h>

static int initialized = 0; 
static Piegelist* piegeList;
static Pirate* pirate;


extern void initialisation(int nb_trap){
    if (!initialized){
        srand(time(NULL)); // Initialisation du générateur aléatoire
        piegeList = piege_list_new(nb_trap);
        piege_list_init(piegeList);
        treasure_init();
        map_init();
        pirate = pirate_new();
        pirate_init(pirate);
        initialized = 1;
    }
}

extern int verifVictoire(Player* player, Coord treasure){
    assert(player != NULL);
    Coord coordj = player_get_pos(player);
    if (treasure.x == coordj.x && treasure.y == coordj.y){
        //libère la mémoire de piegeList
        piege_list_free(piegeList);
        pirate_free(pirate);
        return 1;
    }
    if (player_get_hp(player)<=0){
        return-1;
    }
    return 0;
}

extern void hitTrap(Player* player){
    assert(player != NULL);
    Coord coord =player_get_pos(player);

    if(verifPieges(piegeList,coord)){
        set_case(coord.x,coord.y,'X');
        player_modifhp(player,-20);
    }
}

extern void movePirate(Player* player){
    assert(player != NULL);
    pirate_move(pirate, player);
}
#ifndef PLAYR_H
#define PLAYER_H

#include <stdint.h> // uint8_t
#include "getch.h"
#include "map.h"
#include "coord.h"


typedef struct player_s Player;
extern Player* player_new();
extern int mouvement(Player* this, char direction);  
extern void player_init(Player* this);
extern Coord player_get_pos(Player* this);
extern int player_get_hp(Player* this);
extern void player_modifhp(Player* this, int hp);
extern void player_print_healthbar(Player* this);
extern void player_free(Player* this);

#endif
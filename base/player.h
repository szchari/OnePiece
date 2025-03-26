#ifndef PLAYR_H
#define PLAYER_H

#include <stdint.h> // uint8_t
#include "getch.h"
#include "map.h"
#include "coord.h"


typedef struct player_s Player;
extern bool movement(Player* this, char direction);  
extern void player_s* init_p(Map* map);
extern char* get_pos(Player* this);
#endif
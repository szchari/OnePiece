#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h> // uint8_t
#include "getch.h"
#include "map.h"
#include "coord.h"

typedef enum {
    HAUT,
    BAS,
    DROITE,
    GAUCHE,
    NUL,
} player_state;

typedef struct player_s {
    int healthbar;
    int posx;
    int posy;
} Player;

extern Player* player_new();
extern int mouvement(Player* this, player_state state);  
extern void player_init(Player* this);
extern Coord player_get_pos(Player* this);
extern int player_get_hp(Player* this);
extern void player_modifhp(Player* this, int hp);
extern void player_print_healthbar(Player* this);
extern void player_free(Player* this);

#endif
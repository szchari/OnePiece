#ifndef PIRATE_H
#define PIRATE_H

#include <stdint.h>
#include "coord.h"
#include "player.h"
#include "getch.h"
#include "map.h"

typedef struct pirate_s {
    int posx;
    int posy;
} Pirate;

extern Pirate* pirate_new();

extern void pirate_init(Pirate* this);
extern int pirate_move(Pirate* this, Player* player);
extern Coord pirate_get_pos(Pirate* this);
extern void pirate_random_pos(Pirate* this);
extern void pirate_free(Pirate* this);

#endif
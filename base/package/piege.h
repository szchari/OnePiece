#ifndef PLAYR_H
#define PLAYER_H

#include <stdlib.h>
#include "coord.h" 
#include <time.h>

typedef struct piege_s Piege;
extern Piege* piege_new();
extern Coord piege_get_pos();
extern void piege_set_pos();
extern void piege_free();

#endif
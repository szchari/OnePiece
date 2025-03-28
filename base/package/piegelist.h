#ifndef PIEGELIST_H
#define PIEGELIST_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "getch.h"
#include "map.h"
#include "player.h"
#include "piege.h"

typedef struct piegelist_s Piegelist;
extern Piegelist* piege_list_new(int capacity);
extern void piege_list_init(Piegelist* this);
extern int verifPieges(Piegelist* this, Coord coordplayer);
void piege_list_free(Piegelist* this);
#endif
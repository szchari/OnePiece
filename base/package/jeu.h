#ifndef JEU_H
#define JEU_H
#include "coord.h" 
#include "player.h"
#include "treasure.h"
#include "map.h"


extern void initialisation();
extern int verifVictoire(Player* player, Coord treasure);


#endif
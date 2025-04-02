#ifndef JEU_H
#define JEU_H
#include "coord.h" 
#include "player.h"
#include "treasure.h"
#include "map.h"
#include "pirate.h"



extern void initialisation(int nb_trap);
extern int verifVictoire(Player* player, Coord treasure);
extern void hitTrap(Player* player);
extern void movePirate(Player* player);

#endif
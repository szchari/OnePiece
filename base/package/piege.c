#include "piege.h"
#include <stdlib.h>
#include "coord.h" 
#include <time.h>
#include <assert.h>
#include "map.h"



struct piege_s {
    Coord piege_coord;
};

extern Piege* piege_new(){
    Piege* this = (Piege*)calloc(1,sizeof(Piege));
    this->piege_coord.x =0;
    this->piege_coord.y =0;
    // il faut tester s'il y a une erreur ici même si c'est pas censé   
    return this;
}


extern Coord piege_get_pos(Piege* this){
    return this->piege_coord;
}
extern void piege_set_pos(Piege* this,int posx, int posy){
    this->piege_coord.x = posx;
    this->piege_coord.y = posy;
}

extern void piege_free(Piege* this){
    free(this);
}

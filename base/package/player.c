#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "getch.h"
#include "map.h"
#include "player.h"
#include "coord.h"

struct player_s {
    int posx;
    int posy;   
};

extern Player* player_new(){
    Player* this = (Player*)calloc(1,sizeof(Player));
    // il faut tester s'il y a une erreur ici même si c'est pas censé
    return this;
}
    
extern void player_init(Player* this){
    this->posx= 0;
    this->posy = 0;
    set_case(this->posx,this->posy,'j');
}  

extern int mouvement(Player* this, char direction){
    //tester si le mouvement est valide
    
    set_case(this->posx,this->posy,' ');
    switch(direction)
        {
            case 'i':
                //verif dépassement
                if (this->posx-1<0){
                    set_case(this->posx,this->posy,'j');
                    return 0;
                }
                this->posx--; 
                break;
            case 'k':
                //verif dépassement
                if (this->posx==get_colonne()-1){
                    set_case(this->posx,this->posy,'j');
                    return 0;
                }
                this->posx++; 
                break;
            case 'j':
                //verif dépassement
                if (this->posy-1<0){
                    set_case(this->posx,this->posy,'j');
                    return 0;
                }
                this->posy--; 
                break;
            case 'l':
                //verif dépassement
                if (this->posy==get_ligne()-1){    
                    set_case(this->posx,this->posy,'j');
                    return 0;
                }
                this->posy++; 
                break;
        }
    
        set_case(this->posx,this->posy,'j');
    return 1;
}

extern Coord player_get_pos(Player* this){
    Coord coord;
    coord.x = this->posx;
    coord.y = this->posy;
    return coord;
}

extern void player_free(Player* this){
    free(this);
}




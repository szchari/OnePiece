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
    this = (Player*)calloc(1,sizeof(Player));
    // il faut tester s'il y a une erreur ici même si c'est pas censé
    return this;
}
    
extern void player_init(Player* player, char **map){
    player->posx= 0;
    player->posy = 0;
    set_case(map,this->posx,this->posy)= 'j';
}  

extern bool movement(Player* this, char **map, char direction){
    //tester si le mouvement est valide
    
    switch(direction)
    set_case(map,this->posx,this->posy)= ' ';
        {
            case 'q':
                fin = 1;
                break;
            case 'i':
                //verif dépassement
                if (this->posx-1<0){
                    set_case(map,this->posx,this->posy)= 'j';
                    return 0
                }
                this->posx--; 
                break;
            case 'k':
                //verif dépassement
                if (this->posx+1>get_colonne(map)){
                    set_case(map,this->posx,this->posy)= 'j';
                    return 0
                }
                this->posx++; 
                break;
            case 'j':
                //verif dépassement
                if (this->posy-1<0){
                    set_case(map,this->posx,this->posy)= 'j';
                    return 0
                }
                this->posy--; 
                break;
            case 'l':
                //verif dépassement
                if (this->posx+1>get_ligne(map)){    
                    set_case(map,this->posx,this->posy)= 'j';
                    return 0
                }
                this->posy++; 
                break;
        }
    
    set_case(map,this->posx,this->posy)= 'j';
    return 1
}

extern Coord get_pos(Player* this){
    Coord coord;
    coord->x = this->posx;
    coord->y = this->posy;
    return coord;
}




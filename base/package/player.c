#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "getch.h"
#include "map.h"
#include "player.h"
#include "coord.h"

static int total_hp = 20; // vie total d'un joueur

extern Player* player_new(){
    Player* this = (Player*)calloc(1,sizeof(Player));
    if (this == NULL) {
        fprintf(stderr, "Erreur d'allocation memoire pour le player\n");
        exit(EXIT_FAILURE);
    }    
    return this;
}
    
extern void player_init(Player* this){
    assert(this != NULL);
    this->posx= 0;
    this->posy = 0;
    this->healthbar = 100;
    set_case(this->posx,this->posy,'j');
}  

extern int mouvement(Player* this, player_state state){
    assert(this != NULL);
    //tester si le mouvement est valide
        set_case(this->posx,this->posy,' ');

    switch(state)
        {
            case HAUT:
                //verif dépassement
                if (this->posx-1<0){
                    set_case(this->posx,this->posy,'j');
                    return 0;
                }
                this->posx--; 
                break;
            case BAS:
                //verif dépassement
                if (this->posx==get_colonne()-1){
                    set_case(this->posx,this->posy,'j');
                    return 0;
                }
                this->posx++; 
                break;
            case DROITE:
                //verif dépassement
                if (this->posy-1<0){
                    set_case(this->posx,this->posy,'j');
                    return 0;
                }
                this->posy--; 
                break;
            case GAUCHE:
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
    assert(this != NULL);
    Coord coord;
    coord.x = this->posx;
    coord.y = this->posy;
    return coord;
}

extern int player_get_hp(Player* this){
    assert(this != NULL);
    return this->healthbar;
}

extern void player_modifhp(Player* this,int hp){
    assert(this != NULL);

    if (this->healthbar+hp>100){
        return;
    }
    this->healthbar+=hp;
}

extern void player_print_healthbar(Player* this){
    assert(this != NULL);
    printf("|");
    int hp_affiche = (this->healthbar * total_hp) / 100;
    for (int i = 0; i < hp_affiche; i++) {
        printf("=");
    }
    for (int i = hp_affiche; i < total_hp ; i++) {
        printf(" ");
    }
    printf("|");
    printf(" %d%%\n", this->healthbar);  // Afficher le pourcentage de vie
    
}
extern void player_free(Player* this){
    assert(this != NULL);
    free(this);
}




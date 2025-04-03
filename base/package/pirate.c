#include "pirate.h"
#include <stdlib.h>
#include <stdio.h>
#include "map.h"
#include "coord.h"
#include <time.h>


extern Pirate* pirate_new() {
    Pirate* this = (Pirate*)calloc(1, sizeof(Pirate));
    if (this == NULL) {
        fprintf(stderr, "Erreur d'allocation memoire pour le pirate\n");
        exit(EXIT_FAILURE);
    }
    return this;
}

extern void pirate_init(Pirate* this) {
    do {
        this->posx = rand() % get_ligne();
        this->posy = rand() % get_colonne();
    } while (this->posx == 0 && this->posy == 0);
    
    set_case(this->posx, this->posy, 'p');
}

extern int pirate_move(Pirate* this, Player* player) {
    set_case(this->posx, this->posy, ' ');
    
    Coord player_pos = player_get_pos(player);
    
    // si pirate sur la même ligne ou colonne que joueur --> pirate se déplace vers lui
    if (this->posx == player_pos.x || this->posy == player_pos.y) {
        // x
        if (this->posx == player_pos.x) {
            if (this->posy < player_pos.y) {
                this->posy++;
            } else if (this->posy > player_pos.y) {
                this->posy--;
            }
        }
        // y
        else if (this->posy == player_pos.y) {
            if (this->posx < player_pos.x) {
                this->posx++;
            } else if (this->posx > player_pos.x) {
                this->posx--;
            }
        }
    } else {
        // random move
        int direction = rand() % 4;
        
        switch(direction) {
            case 0: // up
                if (this->posx > 0) this->posx--;
                break;
            case 1: // down
                if (this->posx < get_ligne() - 1) this->posx++;
                break;
            case 2: // gauche   
                if (this->posy > 0) this->posy--;
                break;
            case 3: // droite 
                if (this->posy < get_colonne() - 1) this->posy++;
                break;
        }
    }
    
    // catach player
    if (this->posx == player_pos.x && this->posy == player_pos.y) {
        // losing hp if same cell
        player_modifhp(player, -20); // -20% de vie
        
        // déplacé à un endroit random
        pirate_random_pos(this);
        set_case(player_pos.x, player_pos.y, 'j');
        
        return 1; // le pirate a choppé le joueur
    } else {
        // dessiner le pirate à sa nouvelle position
        set_case(this->posx, this->posy, 'p');
        return 0; // le pirate n'a pas attrapé le joueur
    }
}

extern Coord pirate_get_pos(Pirate* this) {
    Coord coord;
    coord.x = this->posx;
    coord.y = this->posy;
    return coord;
}

extern void pirate_random_pos(Pirate* this) {
    set_case(this->posx, this->posy, ' ');
    
    this->posx = rand() % get_ligne();
    this->posy = rand() % get_colonne();
    
    set_case(this->posx, this->posy, 'P');
}

extern void pirate_free(Pirate* this) {
    free(this);
}
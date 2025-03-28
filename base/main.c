#include <stdlib.h>
#include "player.h"
#include "map.h"
#include "coord.h"
#include "treasure.h"
#include <time.h>
#include "jeu.h"

int main()
{
    
    char car ;
    int fin = 0;

    //initialisation 
    initialisation();
    Player* player = player_new();
    player_init(player);
    Coord coord = treasure_get_pos();

    while(!fin)
    {
        map_print();
        printf("x = %d, y = %d\n",coord.x,coord.y);
        player_print_healthbar(player);
        //traitement du déplacement
        car = getch();
        mouvement(player,car);
        system("clear");
        //verifier la victoire
        if (verifVictoire(player,treasure_get_pos())){
            fin =1;
        }
        //verif quitter jeu
        if (car == 'q'){
            break;
        }
    }
    if (fin){
        printf("bravo\n");
    }
    //Liberation de la memoire pour le/les joueurs:
    player_free(player);
    //Liberation de la memoire pour le tableau
    map_free();

}

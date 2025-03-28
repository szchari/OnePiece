#include <stdlib.h>
#include "player.h"
#include "map.h"
#include "coord.h"
#include "treasure.h"
#include <time.h>
int main()
{
    srand(time(NULL)); // Initialisation du générateur aléatoire
    char car ;
    int fin = 0;
    map_init();
    Player* player = player_new();
    player_init(player);
    treasure_init();

    while(!fin)
    {
        
        //traitement du déplacement
        mouvement(player,car);
        system("clear");
        map_print();
        car = getch();
        if (car == 'q'){
            Coord coord = treasure_get_pos();
            printf("x = %d, y = %d\n",coord.x,coord.y);
            break;
        }
    }

    //Liberation de la memoire pour le/les joueurs:
    player_free(player);
    //Liberation de la memoire pour le tableau
    map_free();

}

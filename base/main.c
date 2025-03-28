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
    Coord coord = treasure_get_pos();
    while(!fin)
    {
        map_print();
        printf("x = %d, y = %d\n",coord.x,coord.y);
        //traitement du déplacement
        car = getch();
        mouvement(player,car);
        system("clear");
        if (verifVictoire(player)){
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

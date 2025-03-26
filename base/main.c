#include <stdlib.h>
#include "grille.h"
#include "player.h"
#include "map.h"


#define COLONNE 5
#define LIGNE 4

int main()
{
    char car ;
    int fin = 0;
    char **map;
    
    Player* player = player_new();
    init(player,map)




    while(!fin)
    {
        car = getch();
        //traitement du déplacement
        mouvement(player,map,car)
        system("clear");
        grille_print(map, get_colonne(map), get_ligne(map));

    }

  
    //Liberation de la memoire pour le tableau
    for (int i = 0; i < LIGNE; i++) {
        free(test_grille[i]);
    }
    free(test_grille);

}

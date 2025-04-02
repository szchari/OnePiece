#include <stdio.h>
#include "coord.h"
#include "player.h"
#include "treasure.h"
#include "map.h"
#include "piege.h"
#include "piegelist.h"
#include "getch.h"
#include "jeu.h"


typedef enum {
    INIT,
    ACQUISITION_CLAVIER,
    DEPLACEMENT_GAUCHE,
    DEPLACEMENT_DROITE,
    DEPLACEMENT_HAUT,
    DEPLACEMENT_BAS,
    VERIFICATION_VICTOIRE,
    FIN
} State;

int main() {
    char car;
    State state = INIT;
    int fin = 0;

    Player* player = NULL;
    Coord coord;

    while (state != FIN) {
        switch (state) {
            case INIT:
                initialisation(5);
                player = player_new();
                player_init(player);
                coord = treasure_get_pos();
                state = ACQUISITION_CLAVIER;
                break;

            case ACQUISITION_CLAVIER:
                map_print();
                printf("x = %d, y = %d\n", coord.x, coord.y);
                player_print_healthbar(player);
                car = getch();
                
                switch (car) {
                    case 'i': state = DEPLACEMENT_HAUT; break;
                    case 'k': state = DEPLACEMENT_BAS; break;
                    case 'j': state = DEPLACEMENT_GAUCHE; break;
                    case 'l': state = DEPLACEMENT_DROITE; break;
                    case 'q': state = FIN; break;
                    default: state = ACQUISITION_CLAVIER; break;
                }
                break;

            case DEPLACEMENT_GAUCHE:
                mouvement(player, 'j');
                state = VERIFICATION_VICTOIRE;
                break;

            case DEPLACEMENT_DROITE:
                mouvement(player, 'l');
                state = VERIFICATION_VICTOIRE;
                break;

            case DEPLACEMENT_HAUT:
                mouvement(player, 'i');
                state = VERIFICATION_VICTOIRE;
                break;

            case DEPLACEMENT_BAS:
                mouvement(player, 'k');
                state = VERIFICATION_VICTOIRE;
                break;

            case VERIFICATION_VICTOIRE:
                system("clear");
                hitTrap(player);
                fin = verifVictoire(player, treasure_get_pos());
                if (fin == 1) {
                    printf("gg wp\n");
                    state = FIN;
                } else {
                    state = ACQUISITION_CLAVIER;
                }
                break;

            case FIN:
                printf("J'ai jamais vu quelqu'un d'aussi nul c'est chaud là\n");
                break;
        }
    }

    // Libération de la mémoire
    if (player) {
        player_free(player);
    }
    map_free();

    return 0;
}



/* #include <stdlib.h>
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
    initialisation(5);
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
        hitTrap(player);
        //verifier la victoire
        fin =verifVictoire(player,treasure_get_pos());
        //verif quitter jeu
        if (car == 'q'){
            break;
        }
    }
    if (fin==1){
        printf("bravo\n");
    }
    else{
        printf("vous êtes mort espèce de nul\n");
    }
    //Liberation de la memoire pour le/les joueurs:
    player_free(player);
    //Liberation de la memoire pour le tableau
    map_free();

}
 */
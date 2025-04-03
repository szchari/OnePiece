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
    MOUVEMENT_PIRATE,
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
                system("clear");
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
                state = MOUVEMENT_PIRATE;
                break;

            case DEPLACEMENT_DROITE:
                mouvement(player, 'l');
                state = MOUVEMENT_PIRATE;
                break;

            case DEPLACEMENT_HAUT:
                mouvement(player, 'i');
                state = MOUVEMENT_PIRATE;
                break;

            case DEPLACEMENT_BAS:
                mouvement(player, 'k');
                state = MOUVEMENT_PIRATE;
                break;
                
            case MOUVEMENT_PIRATE:
                movePirate(player);
                state = VERIFICATION_VICTOIRE;
                break;

            case VERIFICATION_VICTOIRE:
                system("clear");
                hitTrap(player);
                fin = verifVictoire(player, treasure_get_pos());
                if (fin == 1) {
                    printf("gg wp\n");
                    state = FIN;
                } else if (fin == -1) {
                    printf("Finito\n");
                    state = FIN;
                } else {
                    state = ACQUISITION_CLAVIER;
                }
                break;

            case FIN:
                if (fin == 1) {
                    printf("Félicitations! Vous avez trouvé le trésor\n");
                } else if (fin == -1) {
                    printf("Dommage\n");
                } else {
                    printf("Jeu terminé\n");
                }
                break;
        }
    }

    if (player) {
        player_free(player);
    }
    map_free();

    return 0;
}
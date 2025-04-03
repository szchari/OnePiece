#include <stdio.h>
#include "coord.h"
#include "player.h"
#include "treasure.h"
#include "map.h"
#include "piege.h"
#include "piegelist.h"
#include "getch.h"
#include "jeu.h"

//Définition des états possibles du jeu 
typedef enum {
    S_FORGET,
    S_INIT,               // État initial
    S_ACQUISITION,        // Attente de saisie clavier
    S_DEPLACEMENT,        // Traitement du déplacement
    S_PIRATE,             // Mouvement des pirates
    S_VERIFICATION,       // Vérification victoire/défaite
    S_FIN,                // Fin du jeu
    NB_STATES             // Nombre total d'états
} state_t;

//Définition des événements possibles 
typedef enum {
    E_START,              // Démarrage
    E_INPUT_HAUT,         // Touche pour aller vers le haut
    E_INPUT_BAS,          // Touche pour aller vers le bas
    E_INPUT_GAUCHE,       // Touche pour aller vers la gauche
    E_INPUT_DROITE,       // Touche pour aller vers la droite
    E_INPUT_QUITTER,      // Touche pour quitter
    E_DEPLACEMENT_FINI,   // Déplacement terminé
    E_PIRATE_FINI,        // Mouvement des pirates terminé
    E_VICTOIRE,           // Condition de victoire
    E_DEFAITE,            // Condition de défaite
    E_CONTINUER,          // Continuer le jeu
    NB_EVENTS             // Nombre total d'événements
} event_t;

// Définition des actions possibles 
typedef enum {
    A_NOP,                // Aucune action
    A_INIT,               // Initialiser le jeu
    A_AFFICHER,           // Afficher l'état du jeu
    A_DEPLACER_HAUT,      // Déplacer vers le haut
    A_DEPLACER_BAS,       // Déplacer vers le bas
    A_DEPLACER_GAUCHE,    // Déplacer vers la gauche
    A_DEPLACER_DROITE,    // Déplacer vers la droite
    A_MOUVEMENT_PIRATE,   // Faire bouger les pirates
    A_VERIFIER,           // Vérifier victoire/défaite
    A_TERMINER,           // Terminer le jeu
    NB_ACTIONS            // Nombre total d'actions
} action_t;

// Structure de transition 
typedef struct {
    state_t destination;  // État de destination
    action_t action;      // Action à effectuer
} transition_t;

// Table de transition d'états 
static const transition_t table[NB_STATES][NB_EVENTS] ={

    [S_INIT][E_START]           = {S_ACQUISITION, A_INIT},
    [S_INIT][E_INPUT_QUITTER]   = {S_FIN, A_TERMINER},

    [S_ACQUISITION][E_INPUT_HAUT]      = {S_DEPLACEMENT, A_DEPLACER_HAUT},
    [S_ACQUISITION][E_INPUT_BAS]       = {S_DEPLACEMENT, A_DEPLACER_BAS},
    [S_ACQUISITION][E_INPUT_GAUCHE]    = {S_DEPLACEMENT, A_DEPLACER_GAUCHE},
    [S_ACQUISITION][E_INPUT_DROITE]    = {S_DEPLACEMENT, A_DEPLACER_DROITE},
    [S_ACQUISITION][E_INPUT_QUITTER]   = {S_FIN, A_TERMINER},
    [S_ACQUISITION][E_CONTINUER]       = {S_ACQUISITION, A_AFFICHER},

    [S_DEPLACEMENT][E_INPUT_QUITTER]   = {S_FIN, A_TERMINER},
    [S_DEPLACEMENT][E_DEPLACEMENT_FINI]= {S_PIRATE, A_MOUVEMENT_PIRATE},

    [S_PIRATE][E_INPUT_QUITTER]   = {S_FIN, A_TERMINER},
    [S_PIRATE][E_PIRATE_FINI]     = {S_VERIFICATION, A_VERIFIER},
    

    [S_VERIFICATION][E_INPUT_QUITTER]   = {S_FIN, A_TERMINER},
    [S_VERIFICATION][E_VICTOIRE]        = {S_FIN, A_TERMINER},
    [S_VERIFICATION][E_DEFAITE]         = {S_FIN, A_TERMINER},
    [S_VERIFICATION][E_CONTINUER]       = {S_ACQUISITION, A_AFFICHER}};


void init(Player* player, int* fin);
void terminer(int* fin);
void verif(Player* player, int* fin, player_state* direction);
void afficher(Player* player);

//Fonction d'exécution d'une action en fonction de l'état et de l'événement 
static void execute_action(action_t action, Player* player, player_state* direction, int* fin) {
    
    switch (action) {
        case A_NOP:
            //Aucune action 
            break;
            
        case A_INIT:
            init(player,fin);
            break;
            
        case A_AFFICHER:
            
            afficher(player);
            break;
            
        case A_DEPLACER_HAUT:
            //Déplacement vers le haut
            *direction = HAUT;
            mouvement(player, *direction);
            break;
            
        case A_DEPLACER_BAS:
            //Déplacement vers le bas 
            *direction = BAS;
            mouvement(player, *direction);
            break;
            
        case A_DEPLACER_GAUCHE:
            //Déplacement vers la gauche 
            *direction = DROITE;  // Note: inverse dans le code original
            mouvement(player, *direction);
            break;
            
        case A_DEPLACER_DROITE:
            // Déplacement vers la droite 
            *direction = GAUCHE;  // Note: inverse dans le code original
            mouvement(player, *direction);
            break;
            
        case A_MOUVEMENT_PIRATE:
            movePirate(player);
            break;
            
        case A_VERIFIER:

            verif(player, fin, direction);
            break;
            
        case A_TERMINER:
            terminer(fin);
            break;
            
        default:
            // Action inconnue 
            fprintf(stderr, "Action inconnue: %d\n", action);
            break;
    }
}

//Fonction principale 
int main() {
    //Variables locales 
    state_t current_state = S_INIT;
    event_t current_event = E_START;
    Player* player = player_new();
    player_state direction;
    int fin = 0;
    char car;
    
    //Boucle principale du jeu 
    while (current_state != S_FIN) {
        // Récupération de la transition 
        transition_t transition = table[current_state][current_event];
        
        // Mise à jour de l'état 
        current_state = transition.destination;
        
        // Exécution de l'action 
        execute_action(transition.action, player, &direction, &fin);
        
        if (current_state == S_FORGET){
            current_event = E_CONTINUER;  // Force la sortie de cet état
            continue;  // Passe directement à l'itération suivante de la boucle
        }
        //Détermination du prochain événement 
        else if (current_state == S_ACQUISITION) {
            // Attente d'une touche
            car = getch();
            
            switch (car) {
                case 'i': current_event = E_INPUT_HAUT; break;
                case 'k': current_event = E_INPUT_BAS; break;
                case 'j': current_event = E_INPUT_GAUCHE; break;
                case 'l': current_event = E_INPUT_DROITE; break;
                case 'q': current_event = E_INPUT_QUITTER; break;
                default: current_event = E_CONTINUER; break;
            }
        } else if (current_state == S_DEPLACEMENT) {
            current_event = E_DEPLACEMENT_FINI;
        } else if (current_state == S_PIRATE) {
            current_event = E_PIRATE_FINI;
        } else if (current_state == S_VERIFICATION) {
            if (fin == 1) {
                current_event = E_VICTOIRE;
            } else if (fin == -1) {
                current_event = E_DEFAITE;
            } else {
                current_event = E_CONTINUER;
            }
        } else {
            current_event = E_CONTINUER;
        }
    }
    
    // Libération du joueur
    player_free(player);
    
    //Libération de la carte (map_free fait partie de la fonction jeu_free())
    map_free();
    
    return 0;
}

//Initialisation du jeu 
void init(Player* player, int* fin){
    initialisation(5);
    player_init(player);
    *fin = 0;
    afficher(player);
}

//Affichage de l'état du jeu 
void afficher(Player* player){
        system("clear");
        map_print();
        Coord coord_tresor = treasure_get_pos();
        printf("trésor = %d, y = %d\n", coord_tresor.x, coord_tresor.y);
        player_print_healthbar(player);
}

//Vérification des conditions de victoire/défaite 
void verif(Player* player, int* fin, player_state* direction){
    system("clear");
    hitTrap(player);
    Coord coord_tresor = treasure_get_pos();
    *fin = verifVictoire(player, coord_tresor);
}

//Affichage du message de fin 
void terminer(int* fin){
    if (*fin == 1) {
        printf("Félicitations! Vous avez trouvé le trésor\n");
    } else if (*fin == -1) {
        printf("Dommage\n");
    } else {
        printf("Jeu terminé\n");
    }
}

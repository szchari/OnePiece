#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "getch.h"
#include "map.h"
#include "player.h"
#include "piege.h"
#include "piegelist.h"

typedef struct piegelist_s{
    Piege** elements;  // Dynamic array of Piege pointers
    int size;          // Current number of elements
    int capacity;      // Total allocated capacity
};

extern Piegelist* piege_list_new(int capacity) {
    Piegelist* list = (Piegelist*)malloc(sizeof(Piegelist));
    if (list == NULL) {
        fprintf(stderr, "Echec malloc pour PiegeList\n");
        return NULL;
    }
    
    list->capacity = capacity;  // Initial capacity
    list->size = 0;
    list->elements = (Piege**)malloc(list->capacity * sizeof(Piege*));
    
    if (list->elements == NULL) {
        fprintf(stderr, "Echec malloc pour PiegeList elements\n");
        free(list);
        return NULL;
    }
    
    return list;
}

extern void piege_list_init(Piegelist* this) {
    for (int i = 0; i < this->capacity; i++) {
        //nouveau piege
        this->elements[i] = piege_new();
        if (this->elements[i] == NULL) {
            fprintf(stderr, "Echec de création du piège\n");
            return;
        }
        // on teste les coord pour qu'elles soient uniques
        int x, y;
        int unique = 0;

        // Find a unique position
        while (!unique) {
            x = rand() % get_ligne();  // Random pos x
            y = rand() % get_colonne();  // Random pos y

            unique = 1;  // on assume que les coords sont bonnes
            for (int j = 0; j < i; j++) {
                Coord coord = piege_get_pos(this->elements[j]);
                if ((coord.x == x && 
                    coord.y == y) || 
                    (coord.x == 0 && 
                    coord.y == 0)) {
                    unique = 0;  // on continue la boucle
                    break;
                }
            }
        }

        //On assigne les coordonnées
        piege_set_pos(this->elements[i],x,y);
        // size grandit
        this->size++;
    }
}


extern int verifPieges(Piegelist* this, Coord coordplayer){
    int player_x = coordplayer.x;
    int player_y = coordplayer.y;
    
    for (int i = 0; i<this->size; i++){
        if (this->elements[i]!=NULL){
            int trap_x =    piege_get_pos(this->elements[i]).x;
            int trap_y = piege_get_pos(this->elements[i]).y;
            if (trap_x==player_x && trap_y==player_y){
                return 1;
            }
        }
    }
    return 0;
}



void piege_list_free(Piegelist* this) {
    // Free each Piege
    for (int i = 0; i < this->size; i++) {
        free(this->elements[i]);
    }
    
    // Free the array of pointers
    free(this->elements);
    
    // Free the list structure
    free(this);
}
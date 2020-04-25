/**
 * \file modele_demineur.c
 * \brief Ce fichier contient les définitions de types et les fonctions pour la gestion
 * de l'interface graphique de la calculatrice addition.
 * 
 * \author{Randaxhe Martin - Russe Cyril}
 * \date: 24-04-2020
 * 
 */

#include "modele_demineur.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void aleatoire_bombe(Terrain *terrain_de_jeu){
    srand(time(NULL));
    unsigned short nbr_mine = get_nombre_mine(get_regle(terrain_de_jeu));
    unsigned short colonne_max = get_ligne(get_regle(terrain_de_jeu));
    unsigned short ligne_max = get_colonne(get_regle(terrain_de_jeu));

    

    for(unsigned short k = 0; k < nbr_mine; k++){
        unsigned short i = rand()%ligne_max;
        unsigned short j = rand()%colonne_max;
        if(get_mine(get_elem_champ_mine(terrain_de_jeu, i, j)) == 0)
            --k;
        else{
            set_mine(get_elem_champ_mine(terrain_de_jeu, i, j), -1);
        }
        
    }
}
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
#include <assert.h>

static void actualise_compteur_autour_de_bombe(Terrain *Terrain_de_jeu, unsigned short i, unsigned short j, unsigned short ligne_max, unsigned short colonne_max);

void initialisation_champ_mine(Terrain *terrain_de_jeu){
    assert(terrain_de_jeu!=NULL);
    initialisation_mine_0(terrain_de_jeu);
    aleatoire_bombe_et_compteur(terrain_de_jeu);
}


void initialisation_mine_0(Terrain *terrain_de_jeu){
    assert(terrain_de_jeu != NULL);
    unsigned short colonne_max = get_ligne(get_regle(terrain_de_jeu));
    unsigned short ligne_max = get_colonne(get_regle(terrain_de_jeu));

    for(int i = 0; i<ligne_max; i++){
        for(int j = 0; j<colonne_max; j++){
            set_mine(get_elem_champ_mine(terrain_de_jeu, i, j), 0);
        }
    }
}

void aleatoire_bombe_et_compteur(Terrain *terrain_de_jeu){
    assert(terrain_de_jeu != NULL);
    srand(time(NULL));
    unsigned short nbr_mine = get_nombre_mine(get_regle(terrain_de_jeu));
    unsigned short colonne_max = get_ligne(get_regle(terrain_de_jeu));
    unsigned short ligne_max = get_colonne(get_regle(terrain_de_jeu)), i, j;
    int compteur =0;

    

    for(unsigned short k = 0; k < nbr_mine;){
        i = rand()%ligne_max;
        j = rand()%colonne_max;
        compteur++;
        printf("%d\n", compteur);

        if(get_mine(get_elem_champ_mine(terrain_de_jeu, i, j)) >= 0){
            set_mine(get_elem_champ_mine(terrain_de_jeu, i, j), -1);
            actualise_compteur_autour_de_bombe(terrain_de_jeu, i, j, ligne_max-1, colonne_max-1);
            k++;
        }
    }
}

void verife_bombe_dans_ta_mere(Terrain *terrain_de_jeu, unsigned short ligne, unsigned short colonne){
    assert(terrain_de_jeu != NULL);
    // if(!(get_Boite_decouverte(get_elem_champ_mine(terrain_de_jeu, ligne, colonne))) && get_mine(get_elem_champ_mine(terrain_de_jeu, ligne, colonne)) > 0){
    //    set_Boite_decouverte(get_elem_champ_mine(terrain_de_jeu, ligne, colonne), 1);
    //     //affiche l'image démerde toi
    // }
    if (!(get_Boite_decouverte(get_elem_champ_mine(terrain_de_jeu, ligne, colonne))) && !(get_mine(get_elem_champ_mine(terrain_de_jeu, ligne, colonne)))){
        //affiche cette case en blanc
        set_Boite_decouverte(get_elem_champ_mine(terrain_de_jeu, ligne, colonne), 1);
        unsigned short colonne_max = get_ligne(get_regle(terrain_de_jeu)) - 1;
        unsigned short ligne_max = get_colonne(get_regle(terrain_de_jeu)) - 1;
        if(ligne == 0){
            verife_bombe_dans_ta_mere(terrain_de_jeu, ligne+1, colonne);
            if(colonne == 0){
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne, colonne+1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne+1, colonne+1);
            }
            else if(colonne == colonne_max){
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne, colonne-1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne+1, colonne-1);
            }
            else{
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne, colonne-1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne+1, colonne-1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne, colonne + 1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne+1, colonne+1);
            }
        }
        else if(ligne == ligne_max){
            verife_bombe_dans_ta_mere(terrain_de_jeu, ligne-1, colonne);
            if (colonne == 0)
            {
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne, colonne+1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne-1, colonne+1);
            }
            else if (colonne == colonne_max)
            {
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne, colonne-1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne-1, colonne-1);
            }
            else
            {
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne, colonne-1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne-1, colonne -1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne, colonne+1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne-1, colonne+1);
            }
        }
        else
        {
            verife_bombe_dans_ta_mere(terrain_de_jeu, ligne-1, colonne);
            verife_bombe_dans_ta_mere(terrain_de_jeu, ligne+1, colonne);
            if(colonne == 0){
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne-1, colonne+1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne, colonne+1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne+1, colonne+1);
            }
            else if(colonne == colonne_max){
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne-1, colonne-1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne, colonne-1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne+1, colonne-1);
            }
            else{
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne-1, colonne-1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne, colonne-1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne+1, colonne-1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne-1, colonne+1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne, colonne+1);
                verife_bombe_dans_ta_mere(terrain_de_jeu, ligne+1, colonne+1);
            }
        }
        
    }
}

static void actualise_compteur_autour_de_bombe(Terrain *terrain_de_jeu, unsigned short i, unsigned short j, unsigned short ligne_max, unsigned short colonne_max){
    assert(terrain_de_jeu != NULL);
    if(i == 0){
        if (get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j)) != -1)
            set_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j), get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j)) + 1);

        if (j == 0){
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1), get_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j+1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j+1), get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j+1)) + 1);
        }
        else if(j == colonne_max){
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i+1,j-1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j-1), get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j-1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1), get_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1)) + 1);
        }
        else{
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1), get_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j+1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j+1), get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j+1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j-1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j-1), get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j-1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1), get_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1)) + 1);
        }  
    }
    else if(i == ligne_max){
        if (get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j)) != -1)
            set_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j), get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j)) + 1);

        if (j == 0)
        {
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1), get_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j+1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j+1), get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j+1)) + 1);
        }
        else if (j == colonne_max)
        {
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j-1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j-1), get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j-1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1), get_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1)) + 1);
        }
        else
        {
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1), get_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j+1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j+1), get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j+1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j-1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j-1), get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j-1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1), get_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1)) + 1);
        }
    }
    else{
        if (get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j)) != -1)
            set_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j), get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j)) + 1);
        if (get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j)) != -1)
            set_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j), get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j)) + 1);
        if(j == 0){
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j+1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j+1), get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j+1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1), get_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j+1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j+1), get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j+1)) + 1);
        }
        else if(j == colonne_max){
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j-1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j-1), get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j-1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1), get_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j-1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j-1), get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j-1)) + 1);
        }
        else{
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j-1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j-1), get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j-1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1), get_mine(get_elem_champ_mine(terrain_de_jeu, i, j-1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j-1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j-1), get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j-1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j+1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j+1), get_mine(get_elem_champ_mine(terrain_de_jeu, i-1, j+1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1), get_mine(get_elem_champ_mine(terrain_de_jeu, i, j+1)) + 1);
            if (get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j+1)) != -1)
                set_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j+1), get_mine(get_elem_champ_mine(terrain_de_jeu, i+1, j+1)) + 1);
        }


    }

}


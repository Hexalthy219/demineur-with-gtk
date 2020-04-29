/**
 * \file modele_demineur.c
 * \brief Ce fichier contient les définitions de types et les fonctions pour la gestion
 * de l'interface graphique de la calculatrice addition.
 * 
 * \author{Randaxhe Martin - Russe Cyril}
 * \date: 24-04-2020
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#include "modele_demineur.h"
#include "vue_demineur.h"
#include "controleur_demineur.h"
#include "type_opaque.h"

#define NBR_MINE_DEBUTANT 10
#define TEMPS_DEBUTANT 60
#define NBR_LIGNE_DEBUTANT 10
#define NBR_COLONNE_DEBUTANT 10

#define NBR_MINE_INTERMEDIAIRE 40
#define TEMPS_INTERMEDIAIRE 180
#define NBR_LIGNE_INTERMEDIAIRE 20
#define NBR_COLONNE_INTERMEDIAIRE 20

#define NBR_MINE_EXPERT 90
#define TEMPS_EXPERT 300
#define NBR_LIGNE_EXPERT 30
#define NBR_COLONNE_EXPERT 30

static void actualise_compteur_autour_de_bombe(Terrain *Terrain_de_jeu, unsigned short i, unsigned short j, unsigned short ligne_max, unsigned short colonne_max);

void nouvelle_partie(Terrain *terrain_de_jeu){
    assert(terrain_de_jeu!=NULL);
    initialisation_mine_0(terrain_de_jeu);
    aleatoire_bombe_et_compteur(terrain_de_jeu);
    initialisation_case_decouvert_0(terrain_de_jeu);
    set_Boite_deja_decouverte(get_regle(terrain_de_jeu), 0);
}

void initialisation_mine_0(Terrain *terrain_de_jeu){
    assert(terrain_de_jeu != NULL);
    unsigned short colonne_max = get_colonne(get_regle(terrain_de_jeu));
    unsigned short ligne_max = get_ligne(get_regle(terrain_de_jeu));

    for(unsigned short i = 0; i<ligne_max; i++){
        for(unsigned short j = 0; j<colonne_max; j++){
            set_mine(get_elem_champ_mine(terrain_de_jeu, i, j), 0);
        }
    }

}

void initialisation_case_decouvert_0(Terrain *terrain_de_jeu){
    assert(terrain_de_jeu != NULL);
    unsigned short colonne_max = get_colonne(get_regle(terrain_de_jeu)), ligne_max = get_ligne(get_regle(terrain_de_jeu));

    for (int i = 0; i < ligne_max; i++){
        for (int j = 0; j < colonne_max; j++)
            set_Boite_decouverte(get_elem_champ_mine(terrain_de_jeu, i, j), 0);
    }
}

void aleatoire_bombe_et_compteur(Terrain *terrain_de_jeu){
    assert(terrain_de_jeu != NULL);
    srand(time(NULL));
    unsigned short nbr_mine = get_nombre_mine(get_regle(terrain_de_jeu));
    unsigned short colonne_max = get_colonne(get_regle(terrain_de_jeu));
    unsigned short ligne_max = get_ligne(get_regle(terrain_de_jeu)), i, j;

    for(unsigned short k = 0; k < nbr_mine;){
        i = rand()%ligne_max;
        j = rand()%colonne_max;

        if(get_mine(get_elem_champ_mine(terrain_de_jeu, i, j)) >= 0){
            set_mine(get_elem_champ_mine(terrain_de_jeu, i, j), -1);
            actualise_compteur_autour_de_bombe(terrain_de_jeu, i, j, ligne_max-1, colonne_max-1);
            k++;
        }
    }
}

void decouvre_boite(Terrain *terrain_de_jeu, unsigned int ligne, unsigned int colonne){
    assert(terrain_de_jeu != NULL);
    
    if(!(get_Boite_decouverte(get_elem_champ_mine(terrain_de_jeu, ligne, colonne))) && get_mine(get_elem_champ_mine(terrain_de_jeu, ligne, colonne)) > 0){
        set_Boite_deja_decouverte(get_regle(terrain_de_jeu), get_Boite_deja_decouverte(get_regle(terrain_de_jeu)) + 1);
        set_Boite_decouverte(get_elem_champ_mine(terrain_de_jeu, ligne, colonne), 1);
        
        charge_image_bouton(get_bouton(terrain_de_jeu, ligne, colonne), get_mine(get_elem_champ_mine(terrain_de_jeu, ligne, colonne)));
    }
    else if (!(get_Boite_decouverte(get_elem_champ_mine(terrain_de_jeu, ligne, colonne))) && !(get_mine(get_elem_champ_mine(terrain_de_jeu, ligne, colonne)))){
        charge_image_bouton(get_bouton(terrain_de_jeu, ligne, colonne), 0);
        set_Boite_deja_decouverte(get_regle(terrain_de_jeu), get_Boite_deja_decouverte(get_regle(terrain_de_jeu)) + 1);
        set_Boite_decouverte(get_elem_champ_mine(terrain_de_jeu, ligne, colonne), 1);
        unsigned short colonne_max = get_ligne(get_regle(terrain_de_jeu)) - 1;
        unsigned short ligne_max = get_colonne(get_regle(terrain_de_jeu)) - 1;
        if(ligne == 0){
            decouvre_boite(terrain_de_jeu, ligne+1, colonne);
            if(colonne == 0){
                decouvre_boite(terrain_de_jeu, ligne, colonne+1);
                decouvre_boite(terrain_de_jeu, ligne+1, colonne+1);
            }
            else if(colonne == colonne_max){
                decouvre_boite(terrain_de_jeu, ligne, colonne-1);
                decouvre_boite(terrain_de_jeu, ligne+1, colonne-1);
            }
            else{
                decouvre_boite(terrain_de_jeu, ligne, colonne-1);
                decouvre_boite(terrain_de_jeu, ligne+1, colonne-1);
                decouvre_boite(terrain_de_jeu, ligne, colonne + 1);
                decouvre_boite(terrain_de_jeu, ligne+1, colonne+1);
            }
        }
        else if(ligne == ligne_max){
            decouvre_boite(terrain_de_jeu, ligne-1, colonne);
            if (colonne == 0)
            {
                decouvre_boite(terrain_de_jeu, ligne, colonne+1);
                decouvre_boite(terrain_de_jeu, ligne-1, colonne+1);
            }
            else if (colonne == colonne_max)
            {
                decouvre_boite(terrain_de_jeu, ligne, colonne-1);
                decouvre_boite(terrain_de_jeu, ligne-1, colonne-1);
            }
            else
            {
                decouvre_boite(terrain_de_jeu, ligne, colonne-1);
                decouvre_boite(terrain_de_jeu, ligne-1, colonne -1);
                decouvre_boite(terrain_de_jeu, ligne, colonne+1);
                decouvre_boite(terrain_de_jeu, ligne-1, colonne+1);
            }
        }
        else
        {
            decouvre_boite(terrain_de_jeu, ligne-1, colonne);
            decouvre_boite(terrain_de_jeu, ligne+1, colonne);
            if(colonne == 0){
                decouvre_boite(terrain_de_jeu, ligne-1, colonne+1);
                decouvre_boite(terrain_de_jeu, ligne, colonne+1);
                decouvre_boite(terrain_de_jeu, ligne+1, colonne+1);
            }
            else if(colonne == colonne_max){
                decouvre_boite(terrain_de_jeu, ligne-1, colonne-1);
                decouvre_boite(terrain_de_jeu, ligne, colonne-1);
                decouvre_boite(terrain_de_jeu, ligne+1, colonne-1);
            }
            else{
                decouvre_boite(terrain_de_jeu, ligne-1, colonne-1);
                decouvre_boite(terrain_de_jeu, ligne, colonne-1);
                decouvre_boite(terrain_de_jeu, ligne+1, colonne-1);
                decouvre_boite(terrain_de_jeu, ligne-1, colonne+1);
                decouvre_boite(terrain_de_jeu, ligne, colonne+1);
                decouvre_boite(terrain_de_jeu, ligne+1, colonne+1);
            }
        }
        
    }
    // else if (!(get_Boite_decouverte(get_elem_champ_mine(terrain_de_jeu, ligne, colonne))) && get_mine(get_elem_champ_mine(terrain_de_jeu, ligne, colonne)) == -1){

    // }
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

void mode_debutant(Terrain *terrain_de_jeu){
    destructeur_champ_mine(get_champ_mine(terrain_de_jeu), get_ligne(get_regle(terrain_de_jeu)), get_colonne(get_regle(terrain_de_jeu)));
    set_ligne(get_regle(terrain_de_jeu), NBR_LIGNE_DEBUTANT);
    set_colonne(get_regle(terrain_de_jeu), NBR_COLONNE_DEBUTANT);
    set_temps(get_regle(terrain_de_jeu), TEMPS_DEBUTANT);
    set_nombre_mine(get_regle(terrain_de_jeu), NBR_MINE_DEBUTANT);
    set_champ_mine(terrain_de_jeu, constructeur_champ_mine(get_ligne(get_regle(terrain_de_jeu)), get_colonne(get_regle(terrain_de_jeu))));
    nouvelle_partie(terrain_de_jeu);
}

void mode_intermediaire(Terrain * terrain_de_jeu){
    destructeur_champ_mine(get_champ_mine(terrain_de_jeu), get_ligne(get_regle(terrain_de_jeu)), get_colonne(get_regle(terrain_de_jeu)));
    set_ligne(get_regle(terrain_de_jeu), NBR_LIGNE_INTERMEDIAIRE);
    set_colonne(get_regle(terrain_de_jeu), NBR_COLONNE_INTERMEDIAIRE);
    set_temps(get_regle(terrain_de_jeu), TEMPS_INTERMEDIAIRE);
    set_nombre_mine(get_regle(terrain_de_jeu), NBR_MINE_INTERMEDIAIRE);
    set_champ_mine(terrain_de_jeu, constructeur_champ_mine(get_ligne(get_regle(terrain_de_jeu)), get_colonne(get_regle(terrain_de_jeu))));
    nouvelle_partie(terrain_de_jeu);
}

void mode_expert(Terrain *terrain_de_jeu){
    destructeur_champ_mine(get_champ_mine(terrain_de_jeu), get_ligne(get_regle(terrain_de_jeu)), get_colonne(get_regle(terrain_de_jeu)));
    set_ligne(get_regle(terrain_de_jeu), NBR_LIGNE_EXPERT);
    set_colonne(get_regle(terrain_de_jeu), NBR_COLONNE_EXPERT);
    set_temps(get_regle(terrain_de_jeu), TEMPS_EXPERT);
    set_nombre_mine(get_regle(terrain_de_jeu), NBR_MINE_EXPERT);
    set_champ_mine(terrain_de_jeu, constructeur_champ_mine(get_ligne(get_regle(terrain_de_jeu)), get_colonne(get_regle(terrain_de_jeu))));
    nouvelle_partie(terrain_de_jeu);
}

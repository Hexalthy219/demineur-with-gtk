/**
 * \file controleur_demineur.c
 * \brief Ce fichier contient les définitions de types et les fonctions pour la gestion
 * de la logique du demineur
 * 
 * \author{Randaxhe Martin - Russe Cyril}
 * \date: 24-04-2020
 * 
 */
#include <stdlib.h>
#include <assert.h>

#include "controleur_demineur.h"

short **cree_tableau2D(int ligne, int colonne){
    assert(ligne>0 && colonne>0);

    short **tableau = malloc(ligne*short);
    if(tableau==NULL)
        return NULL;
    
    for(int i=0; i<ligne, i++){
        tableau[i] = malloc(colonne*short);
        if(tableau[i]==NULL){
            for(--i; i>=0; i--)
                free(tableau[i]);
            free(tableau);
            return NULL;
        }
    }
    return tableau;
}//fin cree_tableau2D
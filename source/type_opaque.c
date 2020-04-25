/**
 * \file type_opaque.c
 * \brief Ce fichier contient les définitions de types et les fonctions pour la gestion
 * des types opaques du demineur
 * 
 * \author{Randaxhe Martin - Russe Cyril}
 * \date: 24-04-2020
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "type_opaque.h"

struct Boite_t{
    short mine;
    short boite_decouverte;
};

struct Regle_t{
    unsigned short ligne;
    unsigned short colonne;
    unsigned short temps;
    unsigned short nombre_mine;
};

struct Terrain_t{
    Boite ***champ_mine;
    Regle *regle;
};

Terrain *constructeur_Terrain(unsigned short ligne, unsigned short colonne, unsigned short temps, unsigned short nombre_mine){
    Terrain *terrain = malloc(sizeof(Terrain));
    if(terrain==NULL)
        return NULL;
    
    terrain->regle = constructeur_Regle();
    if(terrain->regle==NULL){
        free(terrain);
        return NULL;
    }
    terrain->regle->ligne = ligne;
    terrain->regle->colonne = colonne;
    terrain->regle->temps = temps;
    terrain->regle->nombre_mine = nombre_mine;

    terrain->champ_mine = constructeur_champ_mine(ligne, colonne);
    if(terrain->champ_mine==NULL){
        destructeur_Regle(terrain->regle);
        free(terrain);
        return NULL;
    }

    return terrain;
}//fin constructeur_Terrain

void destructeur_Terrain(Terrain *terrain){
    if(terrain==NULL)
        return;
    assert(terrain->regle!=NULL);
    if(terrain->champ_mine!=NULL)
        destructeur_champ_mine(terrain->champ_mine, terrain->regle->ligne, terrain->regle->colonne);
    destructeur_Regle(terrain->regle);
    free(terrain);
}

Boite ***get_champ_mine(Terrain *recup){
    assert(recup!=NULL);
    return recup->champ_mine;
}
Boite *get_elem_champ_mine(Terrain *recup, unsigned int i, unsigned int j){
    assert(recup!=NULL);
    return recup->champ_mine[i][j];
}

void set_champ_mine(Terrain *change, Boite ***champ_mine){
    assert(change!=NULL && champ_mine!=NULL);
    destructeur_champ_mine(change->champ_mine, change->regle->ligne, change->regle->colonne);
    change->champ_mine = champ_mine;
}
void set_elem_champ_mine(Terrain *change, Boite *mine, unsigned int i, unsigned int j){
    assert(change!=NULL);
    change->champ_mine[i][j] = mine; 
}

Regle *get_regle(Terrain *recup){
    assert(recup!=NULL);
    return recup->regle;
}
void set_regle(Terrain *change, Regle *regle){
    assert(change!=NULL && regle!=NULL);
    change->regle = regle;
}

Boite ***constructeur_champ_mine(unsigned short ligne, unsigned short colonne){
    assert(ligne>0 && colonne>0);

    Boite ***tableau = malloc(ligne*sizeof(Boite**));
    if(tableau==NULL)
        return NULL;
    int i, j;

    for(i=0; i<(int)ligne; i++){
        tableau[i] = malloc(colonne*sizeof(Boite*));

        if(tableau[i]==NULL){
            for(--i; i>=0; i--){
                for(j=0; j<(int)colonne; j++)
                    destructeur_Boite(tableau[i][j]);
                free(tableau[i]);
            }
            free(tableau);
            return NULL;
        }
        for(j=0; j<colonne; j++){
            tableau[i][j] = constructeur_Boite();

            if(tableau[i][j]==NULL){
               for(--j; j>=0; j--)
                    destructeur_Boite(tableau[i][j]); 
                free(tableau[i]);
                for(--i; i<=0; i--){
                    for(j=0; j<colonne; j++)
                        destructeur_Boite(tableau[i][j]);
                }
                free(tableau);
                return NULL;
            }
        }
    }
    return tableau;
}//fin constructeur_champ_mine

void destructeur_champ_mine(Boite ***champ_mine, unsigned short ligne, unsigned short colonne){
    unsigned short i, j;
    if(champ_mine==NULL)
        return;
    for(i=0; i<ligne; i++){
        if(champ_mine[i]!=NULL){
            for(j=0; j<colonne; j++)
                destructeur_Boite(champ_mine[i][j]);
        }
        if(champ_mine[i]!=NULL)
            free(champ_mine[i]);
    }
    free(champ_mine);
}//fin destructeur_champ_mine

Boite *constructeur_Boite(void){
    Boite *boite = malloc(sizeof(Boite));

    return boite;
}//fin constructeur_Boite

void destructeur_Boite(Boite *detruit){
    if(detruit!=NULL)
        free(detruit);
}//fin destructeur_Boite

Regle *constructeur_Regle(void){
    Regle *regle = malloc(sizeof(Regle));

    return regle;
}

void destructeur_Regle(Regle *regle){
    if(regle!=NULL)
        free(regle);
}

short get_mine(Boite *recup){
    assert(recup!=NULL);

    return recup->mine;
}//fin get_mine

void set_mine(Boite *change, short mine){
    assert(change!=NULL);

    change->mine = mine;
}//fin set_mine

short get_Boite_decouverte(Boite *recup){
    assert(recup!=NULL);

    return recup->boite_decouverte;
}//fin get_Boite_decouverte

void set_Boite_decouverte(Boite *change, short boite_decouverte){
    assert(change!=NULL);

    change->boite_decouverte = boite_decouverte;
}//fin set_Boite_decouverte

unsigned short get_ligne(Regle *recup){
    assert(recup!=NULL);

    return recup->ligne;
}//fin get_ligne

void set_ligne(Regle *change, unsigned short ligne){
    assert(change!=NULL);

    change->ligne = ligne;
}//fin set_ligne

unsigned short get_colonne(Regle *recup){
    assert(recup!=NULL);

    return recup->colonne;
}//fin get_colonne

void set_colonne(Regle *change, unsigned short colonne){
    assert(change!=NULL);

    change->colonne = colonne;
}//fin set_colonne

unsigned short get_temps(Regle *recup){
    assert(recup!=NULL);

    return recup->temps;
}//fin get_temps

void set_temps(Regle *change, unsigned short temps){
    assert(change!=NULL);

    change->temps = temps;
}//fin set_temps

unsigned short get_nombre_mine(Regle *recup){
    assert(recup!=NULL);

    return recup->nombre_mine;
}//fin get_nombre_mine

void set_nombre_mine(Regle *change, unsigned short nombre_mine){
    assert(change!=NULL);

    change->nombre_mine = nombre_mine;
}//fin set_nombre_mine



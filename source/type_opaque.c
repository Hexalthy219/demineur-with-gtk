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
#include <gtk/gtk.h>

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
    short boite_deja_decouverte;
    short win;
};

struct Terrain_t{
    Boite ***champ_mine;
    Regle *regle;
    Timer *timer;
    GtkWidget **pTableau_bouton;
    GtkWidget *pBouton_new_game;
};

struct Data_for_Callback_t{
    Terrain *terrain;
    GtkWidget *pFenetre;
    unsigned int coord_boutton[2];
};

struct Timer_t{
    int temps_restant;
    int timer_lance;
    GtkWidget *pLabel;
};

Timer *constructeur_Timer(int temps_restant){
    Timer *timer = malloc(sizeof(Timer));
    if(timer==NULL)
        return NULL;
    timer->temps_restant = temps_restant;

    return timer;
}//fin constructeur_Timer

void destructeur_Timer(Timer *timer){
    if(timer==NULL)
        return;
    free(timer);
    timer=NULL;
}//fin destructeur_Timer

int get_temps_restant(Timer *recup){
    assert(recup!=NULL);

    return recup->temps_restant;
}//fin get_temps_restant

int get_timer_lance(Timer *recup){
    assert(recup!=NULL);

    return recup->timer_lance;
}//fin get_timer_lance

GtkWidget *get_label_timer(Timer *recup){
    assert(recup!=NULL);

    return recup->pLabel;
}//fin get_label_timer

void set_temps_restant(Timer *change, int temps_restant){
    assert(change!=NULL);

    change->temps_restant = temps_restant;
}//fin set_temps_restant

void set_timer_lance(Timer *change, int timer_lance){
    assert(change!=NULL);

    change->timer_lance = timer_lance;
}//fin set_timer_lance

void set_timer_label(Timer *change, GtkWidget *label){
    assert(change!=NULL && label!=NULL);

    change->pLabel = label;
}//fin set_timer_label

Data_for_Callback *constructeur_Data_for_Callback(Terrain *terrain, GtkWidget *pFenetre){
    assert(terrain!=NULL && pFenetre!=NULL);

    Data_for_Callback *data = malloc(sizeof(Data_for_Callback));
    if(data==NULL)
        return NULL;
    
    data->terrain = terrain;
    data->pFenetre = pFenetre;

    return data;
}//fin constructeur_Data_for_Callback

void destructeur_Data_for_Callback(Data_for_Callback *data){
    if(data!=NULL)
        free(data);
}//fin destructeur_Data_for_Callback

unsigned int *get_coord_boutton(Data_for_Callback *data){
    assert(data!=NULL);

    return data->coord_boutton;
}//fin get_coord_boutton

void set_coord_boutton(Data_for_Callback *data, unsigned int coord[2]){
    assert(data!=NULL && coord!=NULL);

    data->coord_boutton[0] = coord[0];
    data->coord_boutton[1] = coord[1];
}//fin set_coord_boutton

Terrain *get_Terrain(Data_for_Callback *data){
    assert(data!=NULL);

    return data->terrain;
}//fin get_Terrain

GtkWidget *get_fenetre(Data_for_Callback *data){
    assert(data!=NULL);

    return data->pFenetre;
}//fin get_fenetre

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
    destructeur_Timer(terrain->timer);
    free(terrain);
}//fin destructeur_Terrain

Timer *get_timer(Terrain *recup){
    assert(recup!=NULL);

    return recup->timer;
}//fin get_timer

void set_timer(Terrain *change, Timer *timer){
    assert(change!=NULL && timer!=NULL);

    change->timer =timer; 
}//fin set_timer

Boite ***get_champ_mine(Terrain *recup){
    assert(recup!=NULL);

    return recup->champ_mine;
}//fin get_champ_mine

Boite *get_elem_champ_mine(Terrain *recup, unsigned int i, unsigned int j){
    assert(recup!=NULL);
    return recup->champ_mine[i][j];
}//fin get_elem_champ_mine

void set_champ_mine(Terrain *change, Boite ***champ_mine){
    assert(change!=NULL && champ_mine!=NULL);
    change->champ_mine = champ_mine;
}//fin set_champ_mine

void set_elem_champ_mine(Terrain *change, Boite *mine, unsigned int i, unsigned int j){
    assert(change!=NULL);
    change->champ_mine[i][j] = mine; 
}//fin set_elem_champ_mine

Regle *get_regle(Terrain *recup){
    assert(recup!=NULL);
    return recup->regle;
}//fin get_regle

void set_regle(Terrain *change, Regle *regle){
    assert(change!=NULL && regle!=NULL);
    change->regle = regle;
}//fin set_regle

GtkWidget **get_tableau_bouton(Terrain *recup){
    assert(recup!=NULL);

    return recup->pTableau_bouton;
}

GtkWidget *get_bouton(Terrain *terrain, unsigned int ligne, unsigned int colonne){
    assert(terrain!=NULL);
    unsigned short colonne_max = get_colonne(get_regle(terrain));

    return terrain->pTableau_bouton[(ligne*colonne_max)+colonne];
}

void set_tableau_bouton(Terrain *change, GtkWidget **tableau_bouton){
    assert(change!=NULL && tableau_bouton!=NULL);

    change->pTableau_bouton = tableau_bouton;
}

GtkWidget *get_bouton_new_game(Terrain *terrain){
    assert(terrain!=NULL);

    return terrain->pBouton_new_game;
}

void set_bouton_new_game(Terrain *terrain, GtkWidget *pBouton_new_game){
    assert(terrain!=NULL && pBouton_new_game!=NULL);

    terrain->pBouton_new_game = pBouton_new_game;
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
}//fin constructeur_Regle

void destructeur_Regle(Regle *regle){
    if(regle!=NULL)
        free(regle);
}//fin destructeur_Regle

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

short get_Boite_deja_decouverte(Regle *recup){
    assert(recup != NULL);
    return recup->boite_deja_decouverte;
}//fin get_Boite_deja_decouverte

void set_Boite_deja_decouverte(Regle *change, short boite_deja_decouverte){
    assert(change != NULL);
    change->boite_deja_decouverte = boite_deja_decouverte;
}//fin set_Boite_deja_decouverte

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

short get_win(Regle *recup){
    assert(recup!=NULL);

    return recup->win;
}//fin get_win

void set_win(Regle *change, short win){
    assert(change!=NULL);

    change->win = win;
}//fin set_win

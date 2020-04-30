/**
 * \file controleur_demineur.c
 * \brief Ce fichier contient les définitions de types et les fonctions pour la gestion
 * de la logique du demineur
 * 
 * \author{Randaxhe Martin - Russe Cyril}
 * \date: 30-04-2020
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "modele_demineur.h"
#include "vue_demineur.h"
#include "controleur_demineur.h"
/**
 * \fn reinitialise_fenetre_nouvelle_pvbox(Data_for_Callback *data)
 * \brief crée une nouvelle pvbox, supprime l'ancienne contenue dans le container pFenetre et le remplace par cette nouvelle pvbox
 * 
 * \param data un pointeur vers Data_for_Callback contenant les données nécessaires au changement de fenêtre
 * 
 * \pre data!=NULL
 * 
 */
static void reinitialise_fenetre_nouvelle_pvbox(Data_for_Callback *data);

void click_difficulte_debutant(GtkWidget *pButton, gpointer data){
    assert(data!=NULL);

    pButton+=0;
    Data_for_Callback *recup_data = data;
    mode_debutant(get_Terrain(recup_data));
    reinitialise_fenetre_nouvelle_pvbox(recup_data);
    gtk_window_resize(GTK_WINDOW(get_fenetre(recup_data)), 300, 400);
    gtk_widget_show_all(get_fenetre(recup_data));
}

void click_difficulte_intermediaire(GtkWidget *pButton, gpointer data){
    assert(data!=NULL);

    pButton+=0;
    Data_for_Callback *recup_data = data;
    mode_intermediaire(get_Terrain(recup_data));
    reinitialise_fenetre_nouvelle_pvbox(recup_data);
    gtk_window_resize(GTK_WINDOW(get_fenetre(recup_data)), 600, 700);
    gtk_widget_show_all(get_fenetre(recup_data));
}

void click_difficulte_expert(GtkWidget *pButton, gpointer data){
    assert(data!=NULL);

    pButton+=0;
    Data_for_Callback *recup_data = data;
    mode_expert(get_Terrain(recup_data));
    reinitialise_fenetre_nouvelle_pvbox(recup_data);
    gtk_window_resize(GTK_WINDOW(get_fenetre(recup_data)), 1000, 1100);
    gtk_widget_show_all(get_fenetre(recup_data));
}

static void reinitialise_fenetre_nouvelle_pvbox(Data_for_Callback *data){
    GtkWidget *pVBox = structure_box(get_fenetre(data), get_Terrain(data), get_tableau_bouton(get_Terrain(data)), get_bouton_new_game(get_Terrain(data)));
    gtk_container_foreach (GTK_CONTAINER (get_fenetre(data)), (GtkCallback) gtk_widget_destroy, NULL);
    gtk_container_add(GTK_CONTAINER(get_fenetre(data)), pVBox);
}

void click_decouvre_case(GtkWidget *pButton, GdkEventButton *type_click, gpointer data){
    assert(data!=NULL);
    pButton+=0;

    Data_for_Callback *recup_data = data;
    if(get_win(get_regle(get_Terrain(recup_data)))!=0)
        return;
    unsigned int *coord = get_coord_boutton(recup_data);
    unsigned int ligne = get_ligne(get_regle(get_Terrain(recup_data))), colonne = get_colonne(get_regle(get_Terrain(recup_data)));
    if(get_Boite_decouverte(get_elem_champ_mine(get_Terrain(recup_data), coord[0], coord[1]))==1){
        if(type_click->button==2){
            if(verifie_correspondance_nombre_drapeau_nombre_mine(get_Terrain(recup_data), coord[0], coord[1])==1){
                if(coord[0]!=0 && coord[1]!=0)
                    decouvre_boite(get_Terrain(recup_data), coord[0]-1, coord[1]-1);
                if(coord[0]!=0)
                    decouvre_boite(get_Terrain(recup_data), coord[0]-1, coord[1]);
                if(coord[0]!=0 && coord[1]!=colonne-1)
                    decouvre_boite(get_Terrain(recup_data), coord[0]-1, coord[1]+1);
                if(coord[1]!=0)
                    decouvre_boite(get_Terrain(recup_data), coord[0], coord[1]-1);
                if(coord[1]!=colonne-1)
                    decouvre_boite(get_Terrain(recup_data), coord[0], coord[1]+1);
                if(coord[0]!=ligne-1 && coord[1]!=0)
                    decouvre_boite(get_Terrain(recup_data), coord[0]+1, coord[1]-1);
                if(coord[0]!=ligne-1)
                    decouvre_boite(get_Terrain(recup_data), coord[0]+1, coord[1]);
                if(coord[0]!=ligne-1 && coord[1]!=colonne-1)
                    decouvre_boite(get_Terrain(recup_data), coord[0]+1, coord[1]+1);
            }      
        }
        return;
    }
    
    if(type_click->button==1)  
        decouvre_boite(get_Terrain(recup_data), coord[0], coord[1]);
    else if(type_click->button==3){
        if(get_Boite_decouverte(get_elem_champ_mine(get_Terrain(recup_data), coord[0], coord[1]))==0){
            set_Boite_decouverte(get_elem_champ_mine(get_Terrain(recup_data), coord[0], coord[1]), -1);
            charge_image_bouton(get_bouton(get_Terrain(recup_data), coord[0], coord[1]), -4);
        }
        else{
            set_Boite_decouverte(get_elem_champ_mine(get_Terrain(recup_data), coord[0], coord[1]), 0);
            gtk_button_set_image(GTK_BUTTON(pButton), NULL);
        }
    }
}

void click_nouvelle_partie(GtkWidget *pButton, gpointer data){
    assert(data!=NULL);
    pButton+=0;

    Data_for_Callback *recup_data = data;
    nouvelle_partie(get_Terrain(recup_data));
    reinitialise_image_bouton(get_Terrain(recup_data));
    charge_image_bouton(get_bouton_new_game(get_Terrain(recup_data)), -5);
    gtk_widget_show_all(get_fenetre(recup_data));
}

void click_a_propos(GtkWidget *pButton, gpointer data){
    pButton+=0;

    fenetre_pop_up_a_propos();
}



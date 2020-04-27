/**
 * \file controleur_demineur.c
 * \brief Ce fichier contient les définitions de types et les fonctions pour la gestion
 * de la logique du demineur
 * 
 * \author{Randaxhe Martin - Russe Cyril}
 * \date: 24-04-2020
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

void click_difficulte_debutant(GtkWidget *pButton, gpointer data){
    assert(data!=NULL);

    pButton+=0;
    Terrain *terrain = data;
    mode_debutant(terrain);
    GtkWidget *pVBox = structure_box(get_fenetre(terrain), terrain);
    gtk_widget_show_all(get_fenetre(terrain));
    gtk_container_foreach (GTK_CONTAINER (get_fenetre(terrain)), (GtkCallback) gtk_widget_destroy, NULL);
    gtk_container_add(GTK_CONTAINER(get_fenetre(terrain)), pVBox);
    gtk_window_resize(GTK_WINDOW(get_fenetre(terrain)), 300, 340);
    gtk_widget_show_all(get_fenetre(terrain));
}

void click_difficulte_intermediaire(GtkWidget *pButton, gpointer data){
    assert(data!=NULL);

    pButton+=0;
    Terrain *terrain = data;
    mode_intermediaire(terrain);
    GtkWidget *pVBox = structure_box(get_fenetre(terrain), terrain);
    gtk_widget_show_all(get_fenetre(terrain));
    gtk_container_foreach (GTK_CONTAINER (get_fenetre(terrain)), (GtkCallback) gtk_widget_destroy, NULL);
    gtk_container_add(GTK_CONTAINER(get_fenetre(terrain)), pVBox);
    gtk_window_resize(GTK_WINDOW(get_fenetre(terrain)), 600, 640);
    gtk_widget_show_all(get_fenetre(terrain));
}

void click_difficulte_expert(GtkWidget *pButton, gpointer data){
    assert(data!=NULL);

    pButton+=0;
    Terrain *terrain = data;
    mode_expert(terrain);
    GtkWidget *pVBox = structure_box(get_fenetre(terrain), terrain);
    gtk_widget_show_all(get_fenetre(terrain));
    gtk_container_foreach (GTK_CONTAINER (get_fenetre(terrain)), (GtkCallback) gtk_widget_destroy, NULL);
    gtk_container_add(GTK_CONTAINER(get_fenetre(terrain)), pVBox);
    gtk_window_resize(GTK_WINDOW(get_fenetre(terrain)), 1000, 1040);
    gtk_widget_show_all(get_fenetre(terrain));
}

void click_decouvre_case(GtkWidget *pButton, gpointer data){
    assert(data!=NULL);
    pButton+=0;

    
}



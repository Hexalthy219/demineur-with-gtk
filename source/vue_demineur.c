/**
 * \file vue_demineur.c
 * \brief Ce fichier contient les définitions de types et les fonctions pour la gestion
 * de l'interface graphique de la calculatrice addition.
 * 
 * \author{Randaxhe Martin - Russe Cyril}
 * \date: 24-04-2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "vue_demineur.h"
#include "type_opaque.h"

GtkWidget *creation_fenetre(void){
    GtkWidget *pFenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pFenetre), "Démineur");
    return pFenetre;
}

GtkWidget *creer_menus(GtkWidget *pFenetre){
    //Déclaration des variables
    GtkWidget *barre_menu;

    GtkWidget *menu_partie;
    GtkWidget *item_partie;
    GtkWidget *item_nouveau;
    GtkWidget *item_separateur;
    GtkWidget *item_quitter;

    GtkWidget *menu_niveau;
    GtkWidget *item_niveau;
    GtkWidget *item_niveau_debutant;
    GtkWidget *item_niveau_intermediaire;
    GtkWidget *item_niveau_expert;

    GtkWidget *menu_aide;
    GtkWidget *item_aide;
    GtkWidget *item_info_createur;
    
    GtkAccelGroup *accelerateur = NULL;

    //barre de menu
    barre_menu = gtk_menu_bar_new();

    //le menu "Partie"
    menu_partie = gtk_menu_new();
    menu_niveau = gtk_menu_new();
    menu_aide = gtk_menu_new();

    //accélérateur
    accelerateur = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(pFenetre), accelerateur);
    
    //création des items avec images
    item_partie = gtk_menu_item_new_with_mnemonic("_Partie");
    item_nouveau = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, NULL);
    item_separateur = gtk_separator_menu_item_new();
    item_quitter = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, accelerateur);

    item_niveau = gtk_menu_item_new_with_mnemonic("_Niveau");
    item_niveau_debutant = gtk_menu_item_new_with_mnemonic("_Débutant");
    item_niveau_intermediaire = gtk_menu_item_new_with_mnemonic("_Intermédiaire");
    item_niveau_expert = gtk_menu_item_new_with_mnemonic("_Expert");

    item_aide = gtk_menu_item_new_with_mnemonic("_Aide");
    item_info_createur = gtk_menu_item_new_with_mnemonic("_A propos");


    gtk_widget_add_accelerator(item_quitter, "activate", accelerateur, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

    //attacher les items
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_partie), menu_partie);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_partie), item_nouveau);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_partie), item_separateur);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_partie), item_quitter);
    gtk_menu_shell_append(GTK_MENU_SHELL(barre_menu), item_partie);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_niveau), menu_niveau);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_niveau), item_niveau_debutant);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_niveau), item_niveau_intermediaire);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_niveau), item_niveau_expert);
    gtk_menu_shell_append(GTK_MENU_SHELL(barre_menu), item_niveau);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_aide), menu_aide);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_aide), item_info_createur);
    gtk_menu_shell_append(GTK_MENU_SHELL(barre_menu), item_aide);

    //les signaux
    g_signal_connect(G_OBJECT(item_quitter), "activate", G_CALLBACK(gtk_main_quit), NULL);

    return barre_menu;


}


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

#include "modele_demineur.h"
#include "vue_demineur.h"
#include "controleur_demineur.h"


GtkWidget *creation_fenetre(void){
    GtkWidget *pFenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pFenetre), "Démineur");
    gtk_window_set_default_size(GTK_WINDOW(pFenetre), 1000, 1000);
    return pFenetre;
}

GtkWidget *creation_menus(GtkWidget *pFenetre, Terrain *terrain){
    //Déclaration des variables
    GtkWidget *barre_menu;

    GtkWidget *menu_partie;
    GtkWidget *item_partie, *item_nouveau, *item_separateur, *item_quitter;

    GtkWidget *menu_niveau;
    GtkWidget *item_niveau, *item_niveau_debutant, *item_niveau_intermediaire, *item_niveau_expert; 

    GtkWidget *menu_aide;
    GtkWidget *item_aide, *item_info_createur;
    
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
    g_signal_connect(G_OBJECT(item_niveau_debutant), "activate", G_CALLBACK(click_difficulte_debutant), (gpointer)terrain);
    g_signal_connect(G_OBJECT(item_niveau_intermediaire), "activate", G_CALLBACK(click_difficulte_intermediaire), (gpointer)terrain);
    g_signal_connect(G_OBJECT(item_niveau_expert), "activate", G_CALLBACK(click_difficulte_expert), (gpointer)terrain);


    return barre_menu;
}

GtkWidget *structure_box(GtkWidget *pFenetre, Terrain *terrain){
    char texte_nbr_mine[4], texte[4];
    int nombre_ligne = get_ligne(get_regle(terrain)), nombre_colonne = get_colonne(get_regle(terrain));
   
    //Initialisation box
    GtkWidget *pVBox = gtk_vbox_new(TRUE, 0);
    GtkWidget *pHBox_info = gtk_hbox_new(TRUE, 0);
    GtkWidget *pHBox_champ_mine[get_ligne(get_regle(terrain))];

    //Initialisation boutons
    GtkWidget *pButton[get_ligne(get_regle(terrain))][get_colonne(get_regle(terrain))];
    sprintf(texte_nbr_mine, "%hu", get_nombre_mine(get_regle(terrain)));
    GtkWidget *pButton_new_game = gtk_button_new_with_label("O");

    //Initialisation labels
    GtkWidget *pLabel_nbr_mine = gtk_label_new(texte_nbr_mine);
    GtkWidget *pLabel_timer = gtk_label_new("60");

    //Initialisation barre menu
    GtkWidget *pBarre_menu = creation_menus(pFenetre, terrain);

    gtk_box_pack_start(GTK_BOX(pVBox), pBarre_menu, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), pHBox_info, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox_info), pLabel_nbr_mine, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox_info), pButton_new_game, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox_info), pLabel_timer, TRUE, TRUE, 0);
    
    for (int i = 0; i < nombre_ligne; i++){
        pHBox_champ_mine[i]=gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(pVBox), pHBox_champ_mine[i], TRUE, TRUE, 0);
        for(int j=0; j<nombre_colonne; j++){
            sprintf(texte, "%hd", get_mine(get_elem_champ_mine(terrain, i, j)));
            pButton[i][j]=gtk_button_new_with_label(texte);
            gtk_widget_set_size_request(pButton[i][j], 20, 20);
            gtk_box_pack_start(GTK_BOX(pHBox_champ_mine[i]), pButton[i][j], TRUE, TRUE, 0);
        }
    }
    
    return pVBox;
}


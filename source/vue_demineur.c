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
#include <assert.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "modele_demineur.h"
#include "vue_demineur.h"
#include "controleur_demineur.h"


GtkWidget *creation_fenetre(Terrain *terrain){
    GtkWidget *pFenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pFenetre), "Démineur");
    gtk_window_resize(GTK_WINDOW(pFenetre), get_ligne(get_regle(terrain))*30, (get_colonne(get_regle(terrain))*30)+40);
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
    Data_for_Callback *data  = constructeur_Data_for_Callback(terrain, pFenetre);
    //les signaux
    g_signal_connect(G_OBJECT(item_quitter), "activate", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(item_niveau_debutant), "activate", G_CALLBACK(click_difficulte_debutant), (gpointer)data);
    g_signal_connect(G_OBJECT(item_niveau_intermediaire), "activate", G_CALLBACK(click_difficulte_intermediaire), (gpointer)data);
    g_signal_connect(G_OBJECT(item_niveau_expert), "activate", G_CALLBACK(click_difficulte_expert), (gpointer)data);

    g_signal_connect(G_OBJECT(item_nouveau), "activate", G_CALLBACK(click_nouvelle_partie), (gpointer)data);

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

    //Signaux
    Data_for_Callback *data_nouvelle_partie = constructeur_Data_for_Callback(terrain, pFenetre);
    g_signal_connect(G_OBJECT(pButton_new_game), "clicked", G_CALLBACK(click_nouvelle_partie), (gpointer)data_nouvelle_partie);

    gtk_box_pack_start(GTK_BOX(pVBox), pBarre_menu, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), pHBox_info, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox_info), pLabel_nbr_mine, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox_info), pButton_new_game, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox_info), pLabel_timer, TRUE, TRUE, 0);
    
    unsigned int tab_coord[2];
    for (int i = 0; i < nombre_ligne; i++){
        pHBox_champ_mine[i]=gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(pVBox), pHBox_champ_mine[i], TRUE, TRUE, 0);
        for(int j=0; j<nombre_colonne; j++){
            sprintf(texte, "%hd", get_mine(get_elem_champ_mine(terrain, i, j)));
            pButton[i][j]=gtk_button_new();
            gtk_widget_set_size_request(pButton[i][j], 20, 20);
            gtk_box_pack_start(GTK_BOX(pHBox_champ_mine[i]), pButton[i][j], TRUE, TRUE, 0);
            Data_for_Callback *data = constructeur_Data_for_Callback(terrain, pFenetre);
            tab_coord[0]=i;
            tab_coord[1]=j;
            set_coord_boutton(data, tab_coord);
            g_signal_connect(G_OBJECT(pButton[i][j]), "clicked", G_CALLBACK(click_decouvre_case), (gpointer)data);
        }
    }
    set_tableau_bouton(terrain, pButton);
    return pVBox;
}

int charge_image_bouton(GtkWidget *pButton){
    assert(pButton!=NULL);
    GdkPixbuf *pb_temp, *pb;
    GtkWidget *image;
    printf("1\n");
    // 1. Charger l’image et la redimensionner (100*100 pixels)
    pb_temp = gdk_pixbuf_new_from_file("images/1.bmp", NULL);
    if(pb_temp == NULL)
    {
        printf(" Erreur de chargement de l’image qu'on tente d'afficher bordel de merde!\n");
        return -1;
    }
    pb = gdk_pixbuf_scale_simple(pb_temp, 20, 20, GDK_INTERP_NEAREST);
    printf("2\n");

    // 2. Placer l’image
    image = gtk_image_new_from_pixbuf(pb);
    printf("3\n");

    gtk_button_set_image(GTK_BUTTON(pButton), image);
    printf("4\n");
    return 0; 
} // fin charge_image_bouton()

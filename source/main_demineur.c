/**
 * \file main.c
 * \brief Ce fichier contient la fonction main()
 * \author{Randaxhe Martin - Russe Cyril}
 * \date 24-04-2020
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "modele_demineur.h"
#include "vue_demineur.h"
#include "controleur_demineur.h"
#include "type_opaque.h"

#define NBR_MINE_DEFAULT 10
#define TEMPS_DEFAULT 60
#define NBR_LIGNE_DEFAULT 10
#define NBR_COLONNE_DEFAULT 10


int main(int argc, const char **argv){

    GtkWidget *pFenetre;
    GtkWidget *pVBox;
    GtkWidget *pHBox[NBR_LIGNE_DEFAULT+1];
    GtkWidget *pButton[NBR_LIGNE_DEFAULT][NBR_COLONNE_DEFAULT];
    GtkWidget *pLabel_nbr_mine = gtk_label_new("10");
    GtkWidget *pLabel_timer = gtk_label_new("60");

    gtk_init(&argc, &argv);

    //création de la fenêtre
    pFenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pFenetre), "Démineur");
    
    g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    pVBox = gtk_vbox_new(TRUE, 0);
    pHBox[0] = gtk_hbox_new(TRUE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), pHBox[0], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox[0]), pLabel_nbr_mine, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox[0]), pLabel_timer, TRUE, TRUE, 0);

    for(int i=1; i<NBR_LIGNE_DEFAULT+1; i++){
        pHBox[i]=gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(pVBox), pHBox[i], TRUE, TRUE, 0);
        for(int j=0; j<NBR_COLONNE_DEFAULT; j++){
            pButton[i-1][j]=gtk_button_new_with_label("0");
            gtk_box_pack_start(GTK_BOX(pHBox[i]), pButton[i-1][j], TRUE, TRUE, 0);
        }
    }



    gtk_container_add(GTK_CONTAINER(pFenetre), pVBox);
    gtk_widget_show_all(pFenetre);

    gtk_main();

    return EXIT_SUCCESS;
}//fin programme
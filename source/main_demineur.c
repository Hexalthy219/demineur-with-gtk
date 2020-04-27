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



int main(int argc, char **argv){
    char *optstring = "l:h:t:m:H";
    Regle *recup_arg = constructeur_Regle();
    int val, recup, recup_nbr_mine;
    
    set_ligne(recup_arg, NBR_LIGNE_DEFAULT);
    set_colonne(recup_arg, NBR_COLONNE_DEFAULT);
    set_temps(recup_arg, TEMPS_DEFAULT);
    set_nombre_mine(recup_arg, NBR_MINE_DEFAULT);

    while ((val = getopt(argc, argv, optstring)) != EOF)
    {
        switch (val)
        {
        case 'l':
            recup = atoi(optarg);
            if(recup>=10 && recup<=30)
                set_ligne(recup_arg, (unsigned short)recup);
            break;
        case 'h':
            recup = atoi(optarg);
            if(recup>=10 && recup<=30)
                set_colonne(recup_arg, (unsigned short)recup);
            break;
        case 't':
            recup = atoi(optarg);
            if(recup>=60 && recup<=600)
                set_temps(recup_arg, (unsigned short)recup);
            break;
        case 'm':
            recup_nbr_mine = atoi(optarg);
            break;
        case 'H':
            printf("usage : ./demineur [-l <nombre ligne>] [-h <nombre colonne>] [-t <temps>] [-m <nombre mine>] [-H]\n\n");
            printf("\tl\tChoisir le nombre de ligne du demineur (10(default) - 30)\n");
            printf("\th\tChoisir le nombre de colonne du demineur (10(default) - 30)\n");
            printf("\tt\tChoisir le temps max pour résoudre le démineur (60(default) - 600)(secondes)\n");
            printf("\tm\tChoisir le nombre de mine (10(default) - l*h)\n");
            printf("\tH\thelp\n\n");
            printf("Si une option ne respecte pas les valeurs max, celle-ci sera automatique établie à sa valeur par défaut.\n");
            return EXIT_SUCCESS;

        default:
            break;
        }
    }

    if(recup_nbr_mine>=10 && (unsigned short)recup_nbr_mine<=(get_colonne(recup_arg)*get_ligne(recup_arg)))
        set_nombre_mine(recup_arg, (unsigned short)recup_nbr_mine);

    Terrain *terrain = constructeur_Terrain(get_ligne(recup_arg), get_colonne(recup_arg), get_temps(recup_arg), get_nombre_mine(recup_arg));
    destructeur_Regle(recup_arg);
    if (terrain==NULL)
        return EXIT_FAILURE;
    
    initialisation_champ_mine(terrain);

    char texte_nbr_mine[4], texte[4];

    GtkWidget *pFenetre;
    GtkWidget *pVBox;
    GtkWidget *pHBox_info;
    GtkWidget *pHBox_champ_mine[get_ligne(get_regle(terrain))];
    GtkWidget *pButton[get_ligne(get_regle(terrain))][get_colonne(get_regle(terrain))];
    sprintf(texte_nbr_mine, "%hu", get_nombre_mine(get_regle(terrain)));
    GtkWidget *pButton_new_game = gtk_button_new_with_label("O");
    GtkWidget *pLabel_nbr_mine = gtk_label_new(texte_nbr_mine);
    GtkWidget *pLabel_timer = gtk_label_new("60");
    GtkWidget *pBarre_menu;


    gtk_init(&argc, &argv);

    //création de la fenêtre
    pFenetre = creation_fenetre();
    
    g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    pVBox = gtk_vbox_new(TRUE, 0);
    pHBox_info = gtk_hbox_new(TRUE, 0);
    pBarre_menu = creation_menus(pFenetre);
    gtk_box_pack_start(GTK_BOX(pVBox), pBarre_menu, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), pHBox_info, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox_info), pLabel_nbr_mine, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox_info), pButton_new_game, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox_info), pLabel_timer, TRUE, TRUE, 0);
    int nombre_ligne = get_ligne(get_regle(terrain)), nombre_colonne = get_colonne(get_regle(terrain));
    for (int i = 0; i < nombre_ligne; i++){
        pHBox_champ_mine[i]=gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(pVBox), pHBox_champ_mine[i], TRUE, TRUE, 0);
        for(int j=0; j<nombre_colonne; j++){
            sprintf(texte, "%hd", get_mine(get_elem_champ_mine(terrain, i, j)));
            pButton[i][j]=gtk_button_new_with_label(texte);
            gtk_widget_set_size_request(pButton[i][j], 40, 40);
            gtk_box_pack_start(GTK_BOX(pHBox_champ_mine[i]), pButton[i][j], TRUE, TRUE, 0);
        }
    }

    gtk_container_add(GTK_CONTAINER(pFenetre), pVBox);
    gtk_widget_show_all(pFenetre);

    gtk_main();

    return EXIT_SUCCESS;
}//fin programme
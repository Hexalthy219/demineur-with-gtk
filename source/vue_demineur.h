/**
 * \file vue_demineur.h
 * \brief Ce fichier contient les déclarations de types et les prototypes des fonctions pour la gestion
 * des entrées de l'utilisateur
 * 
 * \author{Randaxhe Martin - Russe Cyril}
 * \date: 24-04-2020
 * 
 */

#ifndef __VUE_DEMINEUR__
#define __VUE_DEMINEUR__

#include "type_opaque.h"

/**
 * \fn creation_fenetre(Terrain *Terrain)
 * \brief crée la fenêtre et défini sa taille initiale en fonction des dimensions
 * demandées par l'utilisateur
 * 
 * \param terrain un pointeur vers Terrain, structure contenant les infos du terrain.
 * Ici, en particulier les règles du jeu.
 * 
 * \pre terrain!=NULL
 * 
 * \return 
 *      pFenetre    la fenêtre initialisée en fonction des règles contenue dans terrain
 * 
 */
GtkWidget *creation_fenetre(Terrain *Terrain);

/**
 * \fn creation_menus(GtkWidget *pFenetre, Terrain *terrain)
 * \brief crée la barre du menu et les items contenus dedans
 * 
 * \param pFenetre un pointeur vers GtkWidget, la fenêtre du démineur
 * \param terrain un pointeur vers Terrain, structure contenant toutes les infos à
 * transmettre aux fonctions callback des boutons du menu
 * 
 * \pre pFenetre!=NULL && terrain!=NULL
 * 
 * \return
 *      barre_menu  la barre du menu initialisée
 * 
 */
GtkWidget *creation_menus(GtkWidget *pFenetre, Terrain *terrain);

/**
 * \fn structure_box(GtkWidget *pFenetre, Terrain *terrain, GtkWidget **pButton, GtkWidget *pButton_new_game)
 * \brief crée les boxs et les structures dans fenêtre pour former l'affichage de l'interface
 * graphique
 * 
 * \param pFenetre un pointeur vers GtkWidget, la fenetre du démineur
 * \param terrain un pointeur vers Terrain, structure contenant toutes les infos nécessaires
 * à la création des boxs
 * \param pButton un tableau de pointeur vers GtkWidget, tableau contenant l'ensemble des
 * boutons du champ de mine
 * \param pButton_new_game un pointeur vers GtkWidget, le bouton de nouvelle partie
 * 
 * \pre pFenetre!=NULL && terrain!=NULL
 * \post tableau de bouton initialisé et integré à la pvbox que retourne la fonction et
 * signaux de ses boutons connecté aux fonctions callback correspondante
 * 
 * \return
 *      pVBox   pointeur vers GtkWidget, une box verticale contenant d'autres box contenant eux-mêmes
 * les élements nécessaires à l'affiche et l'interaction du démineur
 * 
 */
GtkWidget *structure_box(GtkWidget *pFenetre, Terrain *terrain, GtkWidget **pButton, GtkWidget *pButton_new_game);

/**
 * \fn charge_image_bouton(GtkWidget *pButton, int numero_image)
 * \brief charge dans pButton l'image correspondante à numero_image
 * 
 * \param pButton un pointeur vers GtkWidget, le bouton dans lequel charger l'image
 * \param numero_image un entier caractérisant l'image à charger
 * 
 * \pre pButton !=NULL
 * 
 * \return
 *      0   succès du chargement
 *     -1   echèc du chargement ou numero_image ne correspond à aucune image
 * 
 */
int charge_image_bouton(GtkWidget *pButton, int numero_image);

/**
 * \fn reinitialise_image_bouton(Terrain *terrain)
 * \brief retire toutes les images des boutons du champ de mine
 * 
 * \param terrain un pointeur vers Terrain, structure contenant le
 * tableau de bouton auquel retirer les images
 * 
 * \pre terrain!=NULL
 * 
 */
void reinitialise_image_bouton(Terrain *terrain);

/**
 * \fn fenetre_pop_up_a_propos(void)
 * \brief affiche la fenêtre popup des infos créateurs
 *  
 */
void fenetre_pop_up_a_propos(void);

void maj_timer(Timer *timer);

#endif
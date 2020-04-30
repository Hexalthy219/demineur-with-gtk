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

GtkWidget *creation_fenetre(Terrain *Terrain);

GtkWidget *creation_menus(GtkWidget *pFenetre, Terrain *terrain);

GtkWidget *structure_box(GtkWidget *pFenetre, Terrain *terrain, GtkWidget **pButton, GtkWidget *pButton_new_game);

int charge_image_bouton(GtkWidget *pButton, int numero_image);

void reinitialise_image_bouton(Terrain *terrain);

void fenetre_pop_up_a_propos(void);

#endif
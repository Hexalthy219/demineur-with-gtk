/**
 * \file controleur_demineur.h
 * \brief Ce fichier contient les déclarations de types et les prototypes des fonctions pour la gestion
 * de la logique du demineur
 * 
 * \author{Randaxhe Martin - Russe Cyril}
 * \date: 30-04-2020
 * 
 */

#ifndef __CONTROLEUR_DEMINEUR__
#define __CONTROLEUR_DEMINEUR__

#include "type_opaque.h"

/**
 * \fn click_difficulte_debutant(GtkWidget *pButton, gpointer data)
 * \brief fonction callback du signal du bouton de changement de difficulté débutant
 * 
 * \param data un pointeur vers Data_for_Callback contenant les données nécessaires
 * \param pButton un pointeur vers GtkWidget, le bouton ayant émis le signal
 * 
 * \pre data!=NULL
 * 
 * Change les règles avec les valeurs pour débutant. Met à jour la fenetre avec les 
 * nouvelles dimensions du jeu. Adapte la taille de la fenêtre en conséquence. \n
 * Réaffiche tous les widgets de la fenetre.
 * 
 */
void click_difficulte_debutant(GtkWidget *pButton, gpointer data);

/**
 * \fn click_difficulte_intermediaire(GtkWidget *pButton, gpointer data)
 * \brief fonction callback du signal du bouton de changement de difficulté intermédiaire
 * 
 * \param data un pointeur vers Data_for_Callback contenant les données nécessaires
 * \param pButton un pointeur vers GtkWidget, le bouton ayant émis le signal
 * 
 * \pre data!=NULL
 * 
 * Change les règles avec les valeurs pour intermédiaire. Met à jour la fenetre avec les 
 * nouvelles dimensions du jeu. Adapte la taille de la fenêtre en conséquence. \n
 * Réaffiche tous les widgets de la fenetre.
 * 
 */
void click_difficulte_intermediaire(GtkWidget *pButton, gpointer data);

/**
 * \fn click_difficulte_expert(GtkWidget *pButton, gpointer data)
 * \brief fonction callback du signal du bouton de changement de difficulté expert
 * 
 * \param data un pointeur vers Data_for_Callback contenant les données nécessaires
 * \param pButton un pointeur vers GtkWidget, le bouton ayant émis le signal
 * 
 * \pre data!=NULL
 * 
 * Change les règles avec les valeurs pour expert. Met à jour la fenetre avec les 
 * nouvelles dimensions du jeu. Adapte la taille de la fenêtre en conséquence. \n
 * Réaffiche tous les widgets de la fenetre.
 * 
 */
void click_difficulte_expert(GtkWidget *pButton, gpointer data);

/**
 * \fn click_decouvre_case(GtkWidget *pButton, GdkEventButton *type_click, gpointer data)
 * \brief fonction callback du signal d'un des boutons du champ de mine
 * 
 * \param data un pointeur vers Data_for_Callback contenant les données nécessaires
 * \param type_click un pointeur vers GdkEventButon, structure contenant un champ "button" : une valeur 
 * déterminant le type de clique effectué par le signal
 * \param pButton un pointeur vers GtkWidget, le bouton ayant émis le signal
 * 
 * \pre data!=NULL
 * 
 * Lance la découverte récursive des cases à partir de la position du bouton
 * ayant émis le signal si l'utilisateur à fait un clique gauche. \n
 * Lance la découverte récursive pour toutes les case, autour du bouton ayant 
 * émis le signal, n'ayant pas de drapeau si l'utilisateur a fait un clique molette
 * et que le nombre de drapeau autour du bouton coincide avec le nombre de mine autour. \n
 * Affiche un drapeau sur la case ou le retire si déjà affiché, si l'utilisateur
 * a fait un clique droit.
 */
void click_decouvre_case(GtkWidget *pButton, GdkEventButton *type_click, gpointer data);

/**
 * \fn click_nouvelle_partie(GtkWidget *pButton, gpointer data)
 * \brief fonction callback du signal du bouton nouvelle partie
 * 
 * \param data un pointeur vers Data_for_Callback contenant les données nécessaires
 * \param pButton un pointeur vers GtkWidget, le bouton ayant émis le signal
 * 
 * \pre data!=NULL
 * 
 * Appelle la fonction nouvelle partie pour réinitialisé le champ de mine
 * avec les règles actuelles. \n
 * Réinitialise l'affichage du champ de mine et l'image du bouton nouvelle partie.
 * 
 */
void click_nouvelle_partie(GtkWidget *pButton, gpointer data);

/**
 * \fn click_a_propos(GtkWidget *pButton, gpointer data)
 * \brief fonction callback du signal du bouton à propos
 * 
 * \param data un pointeur vers Data_for_Callback contenant les données nécessaires
 * \param pButton un pointeur vers GtkWidget, le bouton ayant émis le signal
 * 
 * \pre data!=NULL
 * 
 * Appelle la fonction d'affichage de la fenêtre popup d'information.
 */
void click_a_propos(GtkWidget *pButton, gpointer data);

#endif
/**
 * \file modele_demineur.h
 * \brief Ce fichier contient les déclarations de types et les prototypes des fonctions pour la gestion
 * de l'affichage de l'interface graphique demineur
 * 
 * \author{Randaxhe Martin - Russe Cyril}
 * \date: 24-04-2020
 * 
 */

#ifndef __MODELE_DEMINEUR__
#define __MODELE_DEMINEUR__

#include "type_opaque.h"

/**
 * \fn nouvelle_partie(Terrain *terrain)
 * \brief crée un champ de mine avec les bons compteurs
 * 
 * \param terrain un pointeur vers Terrain, structure contenant toutes les informations du terrain
 * 
 * \pre terrain!=NULL
 * 
 */
void nouvelle_partie(Terrain *terrain);

/**
 * \fn initialisation_mine_0(Terrain *terrain)
 * \brief initialise toutes les mines du champ de mine et Boite_decouverte à 0
 * 
 * \param terrain un pointeur vers Terrain, structure contenant toutes les informations du terrain
 * 
 * \pre terrain!=NULL
 * 
 */
void initialisation_0(Terrain *terrain);

/**
 * \fn aleatoire_bombe_et_compteur(Terrain *terrain)
 * \brief places les bombes et incrémente les compteurs des cases sans mines autour de chacune
 * d'entre elles
 * 
 * \param terrain un pointeur vers Terrain, structure contenant toutes les informations du terrain
 * 
 * \pre terrain!=NULL
 * 
 */
void aleatoire_bombe_et_compteur(Terrain *terrain);

/**
 * \fn decouvre_boite(Terrain *terrain, unsigned short ligne, unsigned short colonne)
 * \brief test si on est sur une case vide et si c'est le cas test les cases à coté
 * 
 * \param terrain un pointeur vers Terrain, structure contenant toutes les informations du terrain
 * \param ligne La ligne où on fait le test
 * \param colonne La colonne où on fait le test 
 * 
 * \pre terrain!=NULL
 * 
 */
void decouvre_boite(Terrain *terrain, unsigned int ligne, unsigned int colonne);

/**
 * \fn mode_debutant(Terrain *terrain)
 * \brief Change les valeurs dans le terrain pour le mettre en mode débutant
 * 
 * \param terrain un pointeur vers Terrain, structure contenant toutes les informations du terrain
 * 
 * \pre terrain!=NULL
 * 
 */
void mode_debutant(Terrain *terrain);

/**
 * \fn mode_intermediaire(Terrain *terrain)
 * \brief Change les valeurs dans le terrain pour le mettre en mode intermédiaire
 * 
 * \param terrain un pointeur vers Terrain, structure contenant toutes les informations du terrain
 * 
 * \pre terrain!=NULL
 * 
 */
void mode_intermediaire(Terrain *terrain);

/**
 * \fn mode_expert(Terrain *terrain)
 * \brief Change les valeurs dans le terrain pour le mettre en mode expert
 * 
 * \param terrain un pointeur vers Terrain, structure contenant toutes les informations du terrain
 * 
 * \pre terrain!=NULL
 * 
 */
void mode_expert(Terrain *terrain);

/**
 * \fn decouvre_bombe(Terrain *terrain)
 * \brief permet d'afficher toutes les bombes en cas de défaite et tous les drapeaux en cas de victoire
 * 
 * \param terrain un pointeur vers Terrain, structure contenant toutes les informations du terrain
 * 
 */ 
void decouvre_bombe(Terrain *terrain);

/**
 * \fn verifie_correspondance_nombre_drapeau_nombre_mine(Terrain *terrain, unsigned short i, unsigned short j)
 * \brief vérifie si le nombre de drapeau correspond au nombre de mine autour de la case (i, j)
 * 
 * \param terrain un pointeur vers Terrain, structure contenant toutes les informations du terrain
 * \param i la ligne à laquelle on fait la vérification
 * \param j la colonne à laquelle on fait la vérification
 * 
 * \return 
 *      1   si il y a bien le même nombre de drapeau et de mine \n 
 *      0   sinon
 */
int verifie_correspondance_nombre_drapeau_nombre_mine(Terrain *terrain, unsigned short i, unsigned short j);

void Initialisation_timer(Terrain *terrain);

void demarre_timer(Terrain *terrain);

gint tic(gpointer data);

#endif
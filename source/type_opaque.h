/**
 * \file controleur_demineur.h
 * \brief Ce fichier contient les déclarations de types et les prototypes des fonctions pour la gestion
 * de la logique du demineur
 * 
 * \author{Randaxhe Martin - Russe Cyril}
 * \date: 24-04-2020
 * 
 */

#ifndef __TYPE_OPAQUE__
#define __TYPE_OPAQUE__

#include <gtk/gtk.h>

/**
 * \struct typedef struct Boite_t Boite
 * \brief Déclaration du type opaque Boite
 *
 */
typedef struct Boite_t Boite;

/**
 * \struct typedef struct Regle_t Regle
 * \brief Déclaration du type opaque Regle
 * 
 * 
 *
 */
typedef struct Regle_t Regle;

/**
 * \struct typedef struct Terrain_t Terrain
 * \brief Déclaration du type opaque Terrain
 *
 */
typedef struct Terrain_t Terrain;

/**
 * \struct typedef struct Data_for_Callback_t Data_for_Callback
 * \brief Déclaration du type opaque Data_for_Callback
 *
 */
typedef struct Data_for_Callback_t Data_for_Callback;

Data_for_Callback *constructeur_Data_for_Callback(Terrain *terrain, GtkWidget *pFenetre);

void destructeur_Data_for_Callback(Data_for_Callback *data);

Terrain *get_Terrain(Data_for_Callback *data);

GtkWidget *get_fenetre(Data_for_Callback *data);

unsigned int *get_coord_boutton(Data_for_Callback *data);

void set_coord_boutton(Data_for_Callback *data, unsigned int coord[2]);

/**
 * \fn cree_champ_mine(int ligne, int colonne)
 * \brief allocation d'un tableau de structure ******* reprenant les infos
 * du champ de mine
 * 
 * \param ligne entier contenant le nombre de ligne
 * \param colonne entier contentant le nombre de colonne
 * 
 * \pre ligne>0 && colonne>0
 * 
 * \return 
 *      un pointeur de tableau 2d de structure      si succès de l'allocation de mémoire \n
 *      NULL                                        sinon
 */

Terrain *constructeur_Terrain(unsigned short ligne, unsigned short colonne, unsigned short temps, unsigned short nombre_mine);

void destructeur_Terrain(Terrain *terrain);

Boite ***get_champ_mine(Terrain *recup);

Boite *get_elem_champ_mine(Terrain *recup, unsigned int i, unsigned int j);

void set_champ_mine(Terrain *change, Boite ***champ_mine);

void set_elem_champ_mine(Terrain *change, Boite *mine, unsigned int i, unsigned int j);

Regle *get_regle(Terrain *recup);

void set_regle(Terrain *change, Regle *regle);

GtkWidget **get_tableau_bouton(Terrain *recup);

GtkWidget *get_bouton(Terrain *terrain, unsigned int ligne, unsigned int colonne);

void set_tableau_bouton(Terrain *change, GtkWidget **tableau_bouton);

GtkWidget *get_bouton_new_game(Terrain *terrain);

void set_bouton_new_game(Terrain *terrain, GtkWidget *pBouton_new_game);

Boite ***constructeur_champ_mine(unsigned short ligne, unsigned short colonne);

void destructeur_champ_mine(Boite ***champ_mine, unsigned short ligne, unsigned short colonne);

Boite *constructeur_Boite(void);

void destructeur_Boite(Boite *detruit);

Regle *constructeur_Regle(void);

void destructeur_Regle(Regle *regle);

short get_mine(Boite *recup);

void set_mine(Boite *change, short mine);

short get_Boite_decouverte(Boite *recup);

void set_Boite_decouverte(Boite *change, short boite_decouverte);

short get_Boite_deja_decouverte(Regle *recup);

void set_Boite_deja_decouverte(Regle *change, short boite_deja_decouverte);

unsigned short get_ligne(Regle *recup);

void set_ligne(Regle *change, unsigned short ligne);

unsigned short get_colonne(Regle *recup);

void set_colonne(Regle *change, unsigned short colonne);

unsigned short get_temps(Regle *recup);

void set_temps(Regle *change, unsigned short temps);

unsigned short get_nombre_mine(Regle *recup);

void set_nombre_mine(Regle *change, unsigned short nombre_mine);

short get_win(Regle *recup);

void set_win(Regle *change, short win);

#endif
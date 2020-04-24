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
 */
typedef struct Regle_t Regle;

/**
 * \struct typedef struct Terrain_t Terrain
 * \brief Déclaration du type opaque Terrain
 *
 */
typedef struct Terrain_t Terrain;


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

unsigned short get_ligne(Regle *recup);

void set_ligne(Regle *change, unsigned short ligne);

unsigned short get_colonne(Regle *recup);

void set_colonne(Regle *change, unsigned short colonne);

unsigned short get_temps(Regle *recup);

void set_temps(Regle *change, unsigned short temps);

unsigned short get_nombre_mine(Regle *recup);

void set_nombre_mine(Regle *change, unsigned short nombre_mine);

#endif
/**
 * \file controleur_demineur.h
 * \brief Ce fichier contient les déclarations de types et les prototypes des fonctions pour la gestion
 * de la logique du demineur
 * 
 * \author{Randaxhe Martin - Russe Cyril}
 * \date: 30-04-2020
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

/**
 * \struct typedef struct Timer_t Timer
 * \brief Déclaration du type opaque Timer
 *
 */
typedef struct Timer_t Timer;

Timer *constructeur_Timer(int temps_restant);

void destructeur_Timer(Timer *timer);

int get_temps_restant(Timer *recup);

int get_timer_lance(Timer *recup);

GtkWidget *get_label_timer(Timer *recup);

void set_temps_restant(Timer *change, int temps_restant);

void set_timer_lance(Timer *change, int timer_lance);

void set_timer_label(Timer *change, GtkWidget *label);

Data_for_Callback *constructeur_Data_for_Callback(Terrain *terrain, GtkWidget *pFenetre);

void destructeur_Data_for_Callback(Data_for_Callback *data);

/**
 * \fn get_Terrain(Data_for_Callback *data)
 * \brief cette fonction permet d'accéder à un pointeur sur terrain se trouvant dans la structure data
 * 
 * 
 * \param data est un pointeur sur une structure Data_for_Callback
 * 
 * \return un pointeur sur terrain se trouvant dans data
 * 
 */
Terrain *get_Terrain(Data_for_Callback *data);

/**
 * \fn get_fenetre(Data_for_Callback *data)
 * \brief cette fonction permet d'accéder à un pointeur sur fenetre se trouvant dans la structure data
 * 
 * 
 * \param data est un pointeur sur une structure Data_for_Callback
 * 
 * \return un pointeur sur fenetre se trouvant dans data
 * 
 */
GtkWidget *get_fenetre(Data_for_Callback *data);

/**
 * \fn get_coord_boutton(Data_for_Callback *data)
 * \brief cette fonction permet d'accéder à un pointeur sur coord_boutton se trouvant dans la structure data
 * 
 * 
 * \param data est un pointeur sur une structure Data_for_Callback
 * 
 * \return un pointeur sur coord_boutton se trouvant dans data
 * 
 */
unsigned int *get_coord_boutton(Data_for_Callback *data);

/**
 * \fn set_coord_boutton(Data_for_Callback *data, unsigned int coord[2])
 * \brief cette fonction permet de changer les valeurs de coord_boutton se trouvant dans la structure data
 * 
 * \param data est un pointeur sur une structure Data_for_Callback
 * \param coord un tableau contenant les valeurs à remplacer
 * 
 */
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

Timer *get_timer(Terrain *recup);

void set_timer(Terrain *change, Timer *timer);

/**
 * \fn get_champ_mine(Terrain *recup)
 * \brief cette fonction permet d'accéder à un pointeur sur le tableau champ_mine se trouvant dans la structure recup
 * 
 * 
 * \param recup est un pointeur sur une structure Terrain
 * 
 * \return un pointeur sur le tableau champ_mine se trouvant dans recup
 * 
 */
Boite ***get_champ_mine(Terrain *recup);

/**
 * \fn get_elem_champ_mine(Terrain *recup, unsigned int i, unsigned int j)
 * \brief cette fonction permet d'accéder à un pointeur sur l'élément i,j de champ_mine se trouvant dans la structure recup
 * 
 * 
 * \param recup est un pointeur sur une structure Terrain
 * \param i est la coordonnée verticale
 * \param j est la coordonnée horizontale
 * 
 * \return un pointeur sur l'élément i,j du tableau champ_mine se trouvant dans recup
 * 
 */
Boite *get_elem_champ_mine(Terrain *recup, unsigned int i, unsigned int j);

/**
 * \fn set_champ_mine(Terrain *change, Boite ***champ_mine)
 * \brief cette fonction permet de donner un nouveau tableau se trouvant dans la structure change
 * 
 * \param change est un pointeur sur une structure Terrain
 * \param champ_mine un tableau contenant les valeurs à remplacer
 * 
 */
void set_champ_mine(Terrain *change, Boite ***champ_mine);

/**
 * \fn set_champ_mine(Terrain *change, Boite ***champ_mine)
 * \brief cette fonction permet de changer un élément i,j de champ_mine se trouvant dans la structure change
 * 
 * \param change est un pointeur sur une structure Terrain
 * \param champ_mine un tableau contenant les valeurs à remplacer
 * \param i est la ligne de l'élément choisi
 * \param j est la colonne de l'élément choisi
 * 
 */
void set_elem_champ_mine(Terrain *change, Boite *mine, unsigned int i, unsigned int j);

/**
 * \fn get_regle(Terrain *recup)
 * \brief cette fonction permet d'accéder à un pointeur sur regle se trouvant dans la structure recup
 * 
 * 
 * \param recup est un pointeur sur une structure Terrain
 * 
 * \return un pointeur sur regle se trouvant dans recup
 * 
 */
Regle *get_regle(Terrain *recup);

/**
 * \fn set_regle(Terrain *change, Regle *regle)
 * \brief cette fonction permet de changer regle se trouvant dans la structure change
 * 
 * \param change est un pointeur sur une structure 
 * \param regle un pointeur sur la structure à remplacer
 * 
 */
void set_regle(Terrain *change, Regle *regle);

/**
 * \fn get_tableau_bouton(Terrain *recup)
 * \brief cette fonction permet d'accéder à un pointeur sur le tableau bouton se trouvant dans la structure recup
 * 
 * 
 * \param recup est un pointeur sur une structure Terrain
 * 
 * \return un pointeur sur le tableau de bouton se trouvant dans recup
 * 
 */
GtkWidget **get_tableau_bouton(Terrain *recup);

/**
 * \fn get_bouton(Terrain *terrain, unsigned int ligne, unsigned int colonne)
 * \brief cette fonction permet d'accéder à un pointeur sur l'élément ligne,colonne du tableau bouton se trouvant dans la structure recup
 * 
 * 
 * \param recup est un pointeur sur une structure Terrain
 * \param ligne est une des coordonnée de l'élément du tableau choisi
 * \param colonne est une des coordonnée de l'élément du tableau choisi
 * 
 * \return un pointeur sur l'élément au coordonnée ligne, colonne du tableau de bouton se trouvant dans recup
 * 
 */
GtkWidget *get_bouton(Terrain *terrain, unsigned int ligne, unsigned int colonne);

/**
 * \fn set_tableau_bouton(Terrain *change, GtkWidget **tableau_bouton)
 * \brief cette fonction permet de changer tableau_bouton se trouvant dans la structure change
 * 
 * \param change est un pointeur sur une structure 
 * \param tableau_bouton un pointeur sur le tableau de bouton à remplacer
 * 
 */
void set_tableau_bouton(Terrain *change, GtkWidget **tableau_bouton);

/**
 * \fn get_bouton_new_game(Terrain *terrain)
 * \brief cette fonction permet d'accéder à un pointeur sur bouton_new_game se trouvant dans la structure recup
 * 
 * 
 * \param recup est un pointeur sur une structure Terrain
 * 
 * \return un pointeur sur bouton_new_game se trouvant dans recup
 * 
 */
GtkWidget *get_bouton_new_game(Terrain *terrain);

/**
 * \fn set_bouton_new_game(Terrain *terrain, GtkWidget *pBouton_new_game)
 * \brief cette fonction permet de changer le bouton_new_game se trouvant dans la structure terrain
 * 
 * \param terrain est un pointeur sur une structure 
 * \param pBouton_new_game est la variable à remplacer dans terrain
 * 
 */
void set_bouton_new_game(Terrain *terrain, GtkWidget *pBouton_new_game);


Boite ***constructeur_champ_mine(unsigned short ligne, unsigned short colonne);

void destructeur_champ_mine(Boite ***champ_mine, unsigned short ligne, unsigned short colonne);

Boite *constructeur_Boite(void);

void destructeur_Boite(Boite *detruit);

Regle *constructeur_Regle(void);

void destructeur_Regle(Regle *regle);

/**
 * \fn get_mine(Boite *recup)
 * \brief cette fonction permet d'accéder à mine se trouvant dans la structure recup
 * 
 * 
 * \param recup est un pointeur sur une structure Boite
 * 
 * \return mine se trouvant dans recup
 * 
 */
short get_mine(Boite *recup);

/**
 * \fn set_mine(Boite *change, short mine)
 * \brief cette fonction permet de changer la mine se trouvant dans la structure change
 * 
 * \param change est un pointeur sur une structure 
 * \param mine est la variable à remplacer dans change
 * 
 */
void set_mine(Boite *change, short mine);

/**
 * \fn get_Boite_decouverte(Boite *recup)
 * \brief cette fonction permet d'accéder à Boite_decouverte se trouvant dans la structure recup
 * 
 * 
 * \param recup est un pointeur sur une structure Boite
 * 
 * \return Boite_decouverte se trouvant dans recup
 * 
 */
short get_Boite_decouverte(Boite *recup);

/**
 * \fn set_Boite_decouverte(Boite *change, short boite_decouverte)
 * \brief cette fonction permet de changer boite_decouverte se trouvant dans la structure change
 * 
 * \param change est un pointeur sur une structure 
 * \param boite_decouverte est la variable à remplacer dans change
 * 
 */
void set_Boite_decouverte(Boite *change, short boite_decouverte);

/**
 * \fn get_Boite_deja_decouverte(Regle *recup)
 * \brief cette fonction permet d'accéder à Boite_deja_decouverte se trouvant dans la structure recup
 * 
 * 
 * \param recup est un pointeur sur une structure Regle
 * 
 * \return Boite_deja_decouverte se trouvant dans recup
 * 
 */
short get_Boite_deja_decouverte(Regle *recup);

/**
 * \fn set_Boite_deja_decouverte(Regle *change, short boite_deja_decouverte)
 * \brief cette fonction permet de changer boite_deja_decouverte se trouvant dans la structure change
 * 
 * \param change est un pointeur sur une structure 
 * \param boite_deja_decouvert est la variable à remplacer dans change
 * 
 */
void set_Boite_deja_decouverte(Regle *change, short boite_deja_decouverte);

/**
 * \fn get_ligne(Regle *recup)
 * \brief cette fonction permet d'accéder à ligne se trouvant dans la structure recup
 * 
 * 
 * \param recup est un pointeur sur une structure Regle
 * 
 * \return ligne se trouvant dans recup
 * 
 */
unsigned short get_ligne(Regle *recup);

/**
 * \fn set_ligne(Regle *change, unsigned short ligne)
 * \brief cette fonction permet de changer ligne se trouvant dans la structure change
 * 
 * \param change est un pointeur sur une structure 
 * \param ligne est la variable à remplacer dans change
 * 
 */
void set_ligne(Regle *change, unsigned short ligne);

/**
 * \fn get_colonne(Regle *recup)
 * \brief cette fonction permet d'accéder à colonne se trouvant dans la structure recup
 * 
 * 
 * \param recup est un pointeur sur une structure Regle
 * 
 * \return colonne se trouvant dans recup
 * 
 */
unsigned short get_colonne(Regle *recup);

/**
 * \fn set_colonne(Regle *change, unsigned short colonne)
 * \brief cette fonction permet de changer ligne se trouvant dans la structure change
 * 
 * \param change est un pointeur sur une structure 
 * \param ligne est la variable à remplacer dans change
 * 
 */
void set_colonne(Regle *change, unsigned short colonne);

/**
 * \fn get_temps(Regle *recup)
 * \brief cette fonction permet d'accéder à temps se trouvant dans la structure recup
 * 
 * 
 * \param recup est un pointeur sur une structure Regle
 * 
 * \return temps se trouvant dans recup
 * 
 */
unsigned short get_temps(Regle *recup);

/**
 * \fn set_temps(Regle *change, unsigned short temps)
 * \brief cette fonction permet de changer temps se trouvant dans la structure change
 * 
 * \param change est un pointeur sur une structure 
 * \param temps est la variable à remplacer dans change
 * 
 */
void set_temps(Regle *change, unsigned short temps);

/**
 * \fn get_nombre_mine(Regle *recup)
 * \brief cette fonction permet d'accéder à nombre_mine se trouvant dans la structure recup
 * 
 * 
 * \param recup est un pointeur sur une structure Regle
 * 
 * \return nombre_mine se trouvant dans recup
 * 
 */
unsigned short get_nombre_mine(Regle *recup);

/**
 * \fn set_nombre_mine(Regle *change, unsigned short nombre_mine)
 * \brief cette fonction permet de changer nombre_mine se trouvant dans la structure change
 * 
 * \param change est un pointeur sur une structure 
 * \param nombre_mine est la variable à remplacer dans change
 * 
 */
void set_nombre_mine(Regle *change, unsigned short nombre_mine);

/**
 * \fn get_win(Regle *recup)
 * \brief cette fonction permet d'accéder à win se trouvant dans la structure recup
 * 
 * 
 * \param recup est un pointeur sur une structure Regle
 * 
 * \return win se trouvant dans recup
 * 
 */
short get_win(Regle *recup);

/**
 * \fn set_win(Regle *change, short win)
 * \brief cette fonction permet de changer win se trouvant dans la structure change
 * 
 * \param change est un pointeur sur une structure 
 * \param win est la variable à remplacer dans change
 * 
 */
void set_win(Regle *change, short win);

#endif
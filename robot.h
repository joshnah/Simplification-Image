
#include "image.h"

#ifndef _ROBOT_H_
#define _ROBOT_H_
typedef enum {Nord , Est , Sud , Ouest} Orientation ;


typedef struct 
{
    int x;
    int y;
    Orientation o;
} etat;


/* Initialisation de Robot */
void init_robot(etat *e, int x, int y);

/* Tourner le robot a droite */
void tourner(etat *e, int droite);

/* Avance le robot */
void avancer(etat *e);

/* Orientation du robot */
void nouvelle_orientation(etat *e, Image I);

/* Affichage la position du robot */
void afficher_pos(etat e);


#endif
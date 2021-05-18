
#include <math.h>
#ifndef _GEOM2D_H
#define _GEOM2D_H

typedef struct {
    double x,y;
} Vecteur;

typedef struct{
    double x,y;
} Point;

typedef struct{
    Point A;
    Point B;
} Segment;

/// Les operations ////
/* Creer point */
Point set_point(double x, double y);

/* Somme 2 points */
Point add_point(Point P1, Point P2);

/* Vecteur bipoint  AB */
Vecteur vect_bipoint(Point A, Point B);

/* Somme deux Vecteurs */
Vecteur add_vecteur(Vecteur a, Vecteur b);

/* Produit du reel */
Vecteur produit_reel(Vecteur a, double k);

/* Produit scalaire */
double produit_scalaire(Vecteur a, Vecteur b);

/* Distance */
double distance(Point a, Point b);

/* Norme d'un vecteur */
double norme(Vecteur a);

/* Distance entre un point et un segment */
double distance_point_segment(Point P, Segment S);

/* Multiply un point par un scalaire */
Point produit_scalaire_point(Point A, double k);

#endif
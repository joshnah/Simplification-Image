#include <stdio.h>
#include <stdlib.h>
#include "geom2d.h"
#include <math.h>


Point produit_scalaire_point(Point A, double k)
{
    return (Point){ A.x * k, A.y *k};
}

/* Creer point */
Point set_point(double x, double y)
{
    Point P = {x, y};
    return P;
}

/* Somme 2 points */
Point add_point(Point P1, Point P2)
{
    return set_point(P1.x + P2.x, P1.y + P2.y);
}

Point sub_point(Point P1, Point P2)
{
    return set_point(P1.x - P2.x, P1.y - P2.y);
}

/* Vecteur bipoint */
Vecteur vect_bipoint(Point A, Point B)
{
    Vecteur V = {B.x - A.x, B.y - A.y};
    return V;
}

/* Somme deux Vecteurs */
Vecteur add_vecteur(Vecteur a, Vecteur b)
{
    Vecteur V= {a.x + b.x, a.y + b.y};
    return V;
}


/* Produit du reel */
Vecteur produit_reel(Vecteur a, double k)
{
    Vecteur V = {a.x * k, a.y * k};
    return V;
}


/* Produit scalaire */
double produit_scalaire(Vecteur a, Vecteur b)
{
    return a.x * b.x + a.y *b.y;
}


/* Distance */
double distance(Point a, Point b)
{
    return sqrt(pow((a.x - b.x),2) + pow((a.y - b.y),2));
}

/* Norme d'un vecteur */
double norme(Vecteur a)
{
    return sqrt(pow(a.x, 2) + pow(a.y,2) );

}


/* Distance point - segment  */
double distance_point_segment(Point P, Segment S)
{
    if (S.A.x == S.B.x && S.A.y == S.B.y)
        return distance(P,S.A);

    Vecteur AP = vect_bipoint(S.A, P);
    Vecteur AB = vect_bipoint(S.A, S.B);
    double delta = produit_scalaire(AP,AB) / produit_scalaire(AB, AB);

    if (delta < 0)
        return distance(S.A, P);

    else if (delta > 1)
        return distance(S.B, P);
    else
    {
        Point Q =add_point(S.A, produit_scalaire_point(sub_point(S.B,S.A),delta));
        return distance(Q,P);
    }


}
#ifndef _SIMPLIFICATION_H_
#define _SIMPLIFICATION_H_
#include "geom2d.h"
#include "contour.h"

/* Simplification par segments */
List_Segment simplification(Tableau_Point C, int j1, int j2, double distance_seuil);

/* la Bézier de degré 2 approchant la partie d’un contour polygonal entre les indices j1 et j2 */
Bezier2 approx_bezier2(Tableau_Point C, int j1, int j2);

/* Distance entre le point P et C(ti) */
double distance_bezier_2(Bezier2 B, Point P, double ti);

/* Simplification d'un contour */
List_bezier_2 simplification_bezier_2(Tableau_Point C, int j1, int j2, double distance_seuil);

/* Calculer C(t) */
Point calculer_point_bezier2(Bezier2 B, double t);


/* Fonction approx_bezier3 */
Bezier3 approx_bezier3(Tableau_Point C, int j1, int j2);

/* Distance entre le point P et le courbe bezier a la valeur ti*/
double distance_bezier_3(Bezier3 B, Point P, double ti);

/* Simplification d'un contour */
List_bezier_3 simplification_bezier_3(Tableau_Point C, int j1, int j2, double distance_seuil);

/* Calculer C(t) */
Point calculer_point_bezier3(Bezier3 B, double t);


#endif
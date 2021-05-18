#include "robot.h"
#include "sequence_point.h"

/* Liste chainee pour les contours */
typedef struct cellule_contour
{
    Tableau_Point l;
    struct cellule_contour *suiv;
} cellule_contour;

typedef struct linked_contour
{
    int taille;
    cellule_contour *first;
    cellule_contour *last;
} linked_contour;

/* Liste chainee pour les segments */
typedef struct cellule_segment
{
    Segment S;
    struct cellule_segment *suiv;
}  cellule_segment;

typedef struct List_Segment
{
    int taille;
    cellule_segment *first;
    cellule_segment *last;
} List_Segment;



/* Cellule pour la liste de courbe bezier 2 */
typedef struct cellule_bezier_2
{
    Bezier2 B;
    struct cellule_bezier_2 *suiv;
}  cellule_bezier_2;

/* Liste chainee de courbe bezier 2 */
typedef struct List_bezier_2
{
    int taille;
    cellule_bezier_2 *first;
    cellule_bezier_2 *last;
} List_bezier_2;



/* Cellule pour la liste de courbe bezier 3 */
typedef struct cellule_bezier_3
{
    Bezier3 B;
    struct cellule_bezier_3 *suiv;
}  cellule_bezier_3;

/* Liste chainee de courbe bezier 3 */
typedef struct List_bezier_3
{
    int taille;
    cellule_bezier_3 *first;
    cellule_bezier_3 *last;
} List_bezier_3;






/* Renvoie un contour externe a partir d'un point */
Contour contour_externe(Image I, int x, int y);

/* Trouve un pixel depart pour le contour */
Point trouver_pixel_depart(Image A);

/* Trouver un pixel candidate a partir (px,py) */
Point trouver_point_noir(Image A, int px, int py);

/* Calculer le contour en supprimant les points candidats */
Image contour_supprimer(Image I, Image M, Contour *c_liste, int x, int y);

/* Ajouter un contour dans la liste de contours */
linked_contour ajouter_element_liste_contour(linked_contour L,  Tableau_Point T);






/* Initialisation d'une liste de segment */
List_Segment init_list_segment();

/* Ajouter un segment dans la liste de segment  */
void ajouter_element_list_segment(Segment S, List_Segment *  L );

/* Concatener deux listes de segment */
List_Segment concatener_list_segment(List_Segment L1, List_Segment L2);






/* Initialize la liste chainee bezier 2 */
List_bezier_2 init_list_bezier_2();

/* Ajout d'un element dans la liste de bezier 2 */
void ajouter_element_list_bezier_2(Bezier2 B, List_bezier_2 *  L );

/* Concatenation 2 listes de courbe Bezier 22  */
List_bezier_2 concatener_list_bezier_2(List_bezier_2 L1, List_bezier_2 L2);

/* Elevation de la courbe bezier 2 a la courbe bezier 3 */
Bezier3 elevation_bezier(Bezier2 B);






/* Initialize la liste chainee bezier 3 */
List_bezier_3 init_list_bezier_3();

/* Ajout d'un element dans la liste de bezier 3 */
void ajouter_element_list_bezier_3(Bezier3 B, List_bezier_3 *  L );

/* Concatenation 2 listes de courbe Bezier 3  */
List_bezier_3 concatener_list_bezier_3(List_bezier_3 L1, List_bezier_3 L2);



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "simplification.h"
#include "geom2d.h"



int main(int argc, char *argv[])
{
    Image A;
    FILE *f;
    if (argc != 2)
    {
        fprintf(stderr," Argument erreur");
        return 1;
    }

    A = lire_fichier_image(argv[1]);

    

    int L,H;
    L= largeur_image(A);
    H= hauteur_image(A);


    /* Image masque B */
    Image B = creer_image(L, H);
    Pixel a,b;
    int x,y;
	for (y = 1; y <= B.H; y++)
	{
		for (x = 1; x <= B.L; x++)
		{
            a = get_pixel_image(A, x, y);
            b =get_pixel_image(A,x, y-1);
            if ( a == NOIR && b == BLANC)
                set_pixel_image(B, x, y, NOIR);

		}
    }


    /* Initializarion de la liste de contours */
    linked_contour list_contour;
    list_contour.first = list_contour.last = NULL;
    list_contour.taille = 0;


    /* Nombre de points dans un contour */
    int nb_points = 0;
    
    /* Trouver un pixel candidat */
    Point p = trouver_point_noir(B, p.x, p.y);
    Contour *new_contour;

    /* La fonction trouver_point_noir retourne le point (-1,-1) s'il y a plus de contour */
    while (p.x != -1 || p.y != -1)
    {
        /* Init une sequence de points (Contour) */
        new_contour = (Contour*) malloc(sizeof(Contour));
        new_contour->first =new_contour->last = NULL;
        new_contour->taille = 0;

        B = contour_supprimer(A, B, new_contour, p.x, p.y);

        /* Convertir la liste chainee vers un tableau */
        Tableau_Point tab_contour = sequence_points_liste_vers_tableau(*new_contour);


        /* Ajouter le nouveau contour dans la liste de contours */
        list_contour = ajouter_element_liste_contour(list_contour, tab_contour);


        /* Trouver le pixel candidat suivant */
        p = trouver_point_noir(B, p.x, p.y);        

        nb_points += new_contour->taille;
    } 
 


    /* prend le prefixe et ajoute suffixe ".contours" */
    char *p_char = strstr(argv[1],".pbm");
    *p_char = '\0';
    strcat(argv[1],".contours.eps");

    /* Ecriture du fichier */

    f = fopen(argv[1],"w");

    fprintf(f, "%%!PS−Adobe−3.0 EPSF−3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", L,H);  

    cellule_contour *temp1 = list_contour.first;
    int i,k;

    for ( i = 0; i < list_contour.taille; i++ )
    {

        fprintf(f, "%1.f %1.f ", temp1->l.tab[0].x, H - temp1->l.tab[0].y);
        fprintf(f, "moveto ");   

        for ( k = 1; k < temp1->l.taille; k++)
        {
            fprintf(f, "%1.f %1.f ", temp1->l.tab[k].x, H - temp1->l.tab[k].y);
            fprintf(f, "lineto ");
        }

        temp1 = temp1->suiv;
    }

    fprintf(f,"fill\n");

    fprintf(f,"showpage");
    fclose(f);
    

    /* Affichage de resultats */
    printf("%s", argv[1]);
    printf("\nNombre de contours: %d\n", list_contour.taille);
    
}
    
    
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
    if (argc != 3)
    {
        fprintf(stderr," Argument erreur");
        return 1;
    }
    double distance_seuil = atof(argv[2]);

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
 
    /* Maintenant, on a tous les contours stockes dans list_contour */

    /* Prend le prefixe et ajoute suffixe ".eps" */
    char *p_char = strstr(argv[1],".pbm");
    *p_char = '\0';
    char buff[6];

    /* Convertir distance_seuil en string */
    gcvt(distance_seuil, 6, buff);

    strcat(argv[1],".bezier3(d=");
    strcat(argv[1],buff);
    strcat(argv[1],").eps");
    
    
    
    /* Ecriture du fichier */
    f = fopen(argv[1],"w");

    fprintf(f, "%%!PS−Adobe−3.0 EPSF−3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", L,H);  

    printf("début ecriture eps\n");
    
    cellule_bezier_3 *temp;
    int i;
    List_bezier_3 l1;
    int nb_bezier = 0;  

    Bezier3 B3;
    cellule_contour *cel_contour;
    cel_contour = list_contour.first;

    while (cel_contour != NULL)
    {
	    l1 = simplification_bezier_3(cel_contour->l, 0, cel_contour->l.taille-1 , distance_seuil);

        nb_bezier += l1.taille;
        temp = l1.first;
        B3 = temp->B;
        
        fprintf(f, "%1.f %1.f moveto ", B3.C0.x, H-B3.C0.y);
        fprintf(f, "%1.f %1.f ", B3.C1.x, H-B3.C1.y);
        fprintf(f, "%1.f %1.f ", B3.C2.x, H-B3.C2.y);
        fprintf(f, "%1.f %1.f ", B3.C3.x, H-B3.C3.y);
        fprintf(f, " curveto \n ");
        temp = temp->suiv;
        for ( i = 0; i < l1.taille-1  ; i++)
        {
            B3 = temp->B;
            fprintf(f, "%1.f %1.f ", B3.C1.x, H-B3.C1.y);
            fprintf(f, "%1.f %1.f ", B3.C2.x, H-B3.C2.y);
            fprintf(f, "%1.f %1.f ", B3.C3.x, H-B3.C3.y);
            fprintf(f, " curveto   \n ");


            temp = temp->suiv;
        }

        cel_contour = cel_contour->suiv;
    }
    

    fprintf(f, "  fill \n ");
    fprintf(f," showpage");
    fclose(f);



    /* Affichage l'information */


    printf("%s", argv[1]);
    printf("\nNombre de contours: %d\n", list_contour.taille);
    printf("Nombre de segments de l'image initial: %d\n", nb_points - list_contour.taille);
    printf("Nombre de Bezier3  %d\n", nb_bezier);



    
}
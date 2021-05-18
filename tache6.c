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
 

   /*  prend le prefixe et ajoute suffixe ".contours" */
    char *p_char = strstr(argv[1],".pbm");
    *p_char = '\0';
    char buff[6];

    /* Convertir distance_seuil en string */
    gcvt(distance_seuil, 6, buff);

    strcat(argv[1],".segment(d=");
    strcat(argv[1],buff);
    strcat(argv[1],").eps");

    /* Ecriture du fichier */

    f = fopen(argv[1],"w");

    fprintf(f, "%%!PS−Adobe−3.0 EPSF−3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", L,H);  



    /* Algorithm  */

    cellule_segment *temp;
    
    List_Segment l1;
    int i, nb_segment=0;

    cellule_contour *cel_contour;
    cel_contour = list_contour.first;

    while (cel_contour != NULL)
    {
        l1 = simplification(cel_contour->l, 0, cel_contour->l.taille-1, distance_seuil);
        nb_segment += l1.taille;
        temp = l1.first;
        
        fprintf(f, "%1.f %1.f ", temp->S.A.x, H - temp->S.A.y);
        fprintf(f, "moveto ");
        fprintf(f, "%1.f %1.f ", temp->S.B.x, H - temp->S.B.y);
        fprintf(f, "lineto ");
        temp = temp->suiv;
        for ( i = 0; i < l1.taille - 1; i++)
        {
            fprintf(f, "%1.f %1.f ", temp->S.A.x, H - temp->S.A.y);
            fprintf(f, "lineto ");
            fprintf(f, "%1.f %1.f ", temp->S.B.x, H - temp->S.B.y);
            fprintf(f, "lineto ");
            temp = temp->suiv;
        }
        cel_contour = cel_contour->suiv;
    }
    
    fprintf(f, "fill\n");

    fprintf(f,"showpage");
    fclose(f);
    



    printf("%s", argv[1]);
    printf("\nNombre de contours: %d\n", list_contour.taille);
    printf("Nombre de segments de l'image initial: %d\n", nb_points - list_contour.taille);
    printf("Nombre de segments  %d\n", nb_segment);


    
}
    
    
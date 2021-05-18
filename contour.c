#include "contour.h"


Contour contour_externe(Image I, int x, int y)
{
    Contour c_liste = creer_liste_Point_vide();
    etat e;
    init_robot(&e, x, y);
    int boucle = 0;
    Point p = {(double)x, (double) y};
    while (boucle == 0)
    {
        c_liste = ajouter_element_liste_Point(c_liste, p);
        avancer(&e);
        nouvelle_orientation(&e, I);
        p.x = (double)e.x;
        p.y = (double)e.y;
        afficher_pos(e);
        if (e.x == x && e.y == y && e.o == Est)
            boucle = 1;
    }

    c_liste = ajouter_element_liste_Point(c_liste, p);
    return c_liste;
}


Point trouver_pixel_depart(Image A)
{
    Pixel a,b;
    int x,y,flag = 0;
    for (y = 1; y <= A.H && flag == 0; y++ )
    {
        for (x = 1; x <= A.L && flag == 0; x++)
        {
            a = get_pixel_image(A, x, y);
            b =get_pixel_image(A,x, y-1);
            if ( a == NOIR && b == BLANC)
            {
                flag = 1;
                break;
            }

        }
    }
    Point p = {x-1, y-2};
    return p;
}



Point trouver_point_noir(Image A, int px, int py)
{
    Pixel a;
    int x=px,y=py,flag = 0;

    while (flag == 0 && y != A.H+1)
    {
        if (x > A.L)
        {
            x = 1;
            y++;
        }
        a = get_pixel_image(A, x, y);
        if (a == NOIR)
            flag = 1;
        x++;
    }

    if (y == A.H +1)
        return (Point){-1,-1};

    Point p = {x-2, y-1};
    return p;
}

Image contour_supprimer(Image I, Image M, Contour *c_liste, int x, int y)
{
    etat e;
    init_robot(&e, x, y);
    int boucle = 0;
    Point p = {(double)x, (double) y};

    while (boucle == 0)
    {
        (*c_liste) = ajouter_element_liste_Point((*c_liste), p);

        if (e.o == Est)
            set_pixel_image(M,e.x+1,e.y+1,BLANC);
        avancer(&e);
        nouvelle_orientation(&e, I);
        p.x = (double)e.x;
        p.y = (double)e.y;
        if (e.x == x && e.y == y && e.o == Est)
            boucle = 1;
    }

    (*c_liste) = ajouter_element_liste_Point((*c_liste), p);
    return M;
}


/* La fonction pour ajouter un contour dans la liste de contour */
linked_contour ajouter_element_liste_contour(linked_contour L,  Tableau_Point T)
{
	cellule_contour *el = malloc(sizeof(cellule_contour));
	
	el->suiv = NULL;
    el->l = T;

	if (L.taille == 0)
	{
		/* premier element de la liste */
		L.first = L.last =el;
	}
	else
	{
		L.last->suiv = el;
		L.last = el;
	}
	L.taille++;
	return L;
}



List_Segment init_list_segment()
{
    return (List_Segment){0, NULL, NULL};
}

cellule_segment *init_elem_segment(Segment S)
{
    cellule_segment *new = malloc(sizeof(cellule_segment));
    new->S = S;
    new->suiv = NULL;
    return new;
}

void ajouter_element_list_segment(Segment S, List_Segment *  L )
{
    cellule_segment *el = init_elem_segment(S);

    if (L->taille == 0)
        L->first = L->last = el;

    else 
    {
        L->last->suiv = el;
        L->last = el;
    }
    L->taille++;
}

List_Segment concatener_list_segment(List_Segment L1, List_Segment L2)
{
    if (L1.taille == 0) return L2;
    if (L2.taille == 0) return L1;


    L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier �l�ment de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}


List_bezier_2 init_list_bezier_2()
{
    return (List_bezier_2){0, NULL, NULL};
}

cellule_bezier_2 *init_elem_bezier_2(Bezier2 B)
{
    cellule_bezier_2 *new = malloc(sizeof(cellule_bezier_2));
    new->B = B;
    new->suiv = NULL;
    return new;
}


void ajouter_element_list_bezier_2(Bezier2 B, List_bezier_2 *  L )
{
    cellule_bezier_2 *el = init_elem_bezier_2(B);

    if (L->taille == 0)
        L->first = L->last = el;

    else 
    {
        L->last->suiv = el;
        L->last = el;
    }
    L->taille++;
}

List_bezier_2 concatener_list_bezier_2(List_bezier_2 L1, List_bezier_2 L2)
{
    if (L1.taille == 0) return L2;
    if (L2.taille == 0) return L1;


    L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier �l�ment de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}



Bezier3 elevation_bezier(Bezier2 B)
{
    Bezier3 B3;
    B3.C0 = B.C0;
    B3.C3 = B.C2;

    Point a,b;
    a = produit_scalaire_point(B.C1,2);
    b = add_point(a, B.C0);
    b.x = b.x / 3; 
    b.y = b.y / 3; 

    B3.C1 = b;
    b = add_point(a, B.C2);
    b.x = b.x / 3; 
    b.y = b.y / 3;  
    B3.C2 = b;

    return B3;
}




List_bezier_3 init_list_bezier_3()
{
    return (List_bezier_3){0, NULL, NULL};
}

cellule_bezier_3 *init_elem_bezier_3(Bezier3 B)
{
    cellule_bezier_3 *new = malloc(sizeof(cellule_bezier_3));
    new->B = B;
    new->suiv = NULL;
    return new;
}


void ajouter_element_list_bezier_3(Bezier3 B, List_bezier_3 *  L )
{
    cellule_bezier_3 *el = init_elem_bezier_3(B);

    if (L->taille == 0)
        L->first = L->last = el;

    else 
    {
        L->last->suiv = el;
        L->last = el;
    }
    L->taille++;
}

List_bezier_3 concatener_list_bezier_3(List_bezier_3 L1, List_bezier_3 L2)
{
    if (L1.taille == 0) return L2;
    if (L2.taille == 0) return L1;


    L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier �l�ment de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}

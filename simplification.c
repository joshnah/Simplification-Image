#include "simplification.h"

List_Segment simplification(Tableau_Point C, int j1, int j2, double distance_seuil)
{
    int save_indice;
    double max_distance = 0, dis;

    int i;

    Segment S = {C.tab[j1],C.tab[j2]};
    for (i = j1+1; i < j2; i++)
    {
        dis = distance_point_segment(C.tab[i], S);
        if (dis > max_distance)
        {
            max_distance = dis;
            save_indice = i;
        }
    }



    List_Segment L = init_list_segment();

    if (max_distance <= distance_seuil)
    {
        ajouter_element_list_segment(S, &L);
        return L;
    }

    else 
    {
        List_Segment L1, L2;
        L1 = simplification(C, j1, save_indice, distance_seuil );
        L2 = simplification(C, save_indice, j2, distance_seuil );
        L1 = concatener_list_segment(L1, L2);
        return L1;
    }

}


Bezier2 approx_bezier2(Tableau_Point C, int j1, int j2)
{
    int i;

    Bezier2 bez2;

    bez2.C0 = C.tab[j1];

    bez2.C2 = C.tab[j2];


    Point calcul = {0,0};
    Point temp_point;
    double n = j2 - j1;


    if (n == 1)
    {
        bez2.C1.x = (bez2.C0.x + bez2.C2.x)/2;
        bez2.C1.y = (bez2.C0.y + bez2.C2.y)/2;
    }


    else
    {

        for (i = j1+1; i < j2; i++)
        {
            calcul = add_point(calcul, C.tab[i]);
        }

        calcul = produit_scalaire_point(calcul, (double)( (3*n)/(n*n -1)) );

        temp_point = add_point(bez2.C0, bez2.C2);

        temp_point = produit_scalaire_point(temp_point, (double) ((1-2*n)/ (2*n + 2)) );

        bez2.C1 = add_point(calcul, temp_point);
    }
    return bez2;
}

/* Renvoyer C(t) */
Point calculer_point_bezier2(Bezier2 B, double t)
{
    Point a,b;
    a.x =   (1-t)*(1-t)*B.C0.x;
    a.y =  (1-t)*(1-t)*B.C0.y;


    b = produit_scalaire_point(B.C1, 2*(1-t)*t);

    a = add_point(a, b);

    b = produit_scalaire_point(B.C2, t*t);

    a = add_point(a, b);

    return a;
}


double distance_bezier_2(Bezier2 B, Point P, double ti)
{
    Point a = calculer_point_bezier2(B, ti);

    return distance(a, P);
}



List_bezier_2 simplification_bezier_2(Tableau_Point C, int j1, int j2, double distance_seuil)
{
    int n = j2 - j1;

    Bezier2 B = approx_bezier2(C, j1 ,j2);

    double dmax = 0;
    int k = j1;
    int j,i;
    double ti,dj;


    for (j = j1+1; j < j2; j++)
    {

        i = j -j1;

        ti = (double)i / (double)n;

        dj = distance_bezier_2(B, C.tab[j], ti);

        if (dmax < dj)
        {
            dmax = dj;
            k = j;
        }

    }



    List_bezier_2 L = init_list_bezier_2();

    if (dmax <= distance_seuil)
    {
        ajouter_element_list_bezier_2(B, &L);
        return L;
    }

    else 
    {
        List_bezier_2 L1, L2;
        L1 = simplification_bezier_2(C, j1, k, distance_seuil );
        L2 = simplification_bezier_2(C, k, j2, distance_seuil );
        L1 = concatener_list_bezier_2(L1, L2);
        return L1;
    }
}

double fgamma(double n, double k)
{
    double x = n*n*n*n;
    double y = n*n;
    double a = 6* k*k *k *k - 8 *n *k *k *k + 6 * k*k - 4*n*k + x - y;
    return a;
}


Bezier3 approx_bezier3(Tableau_Point C, int j1, int j2)
{
    int i;
    double n = j2 - j1;
    Bezier3 bez3;

    if (n == 1 || n == 2)
    {

        Bezier2 b2 = approx_bezier2(C,j1,j2);

        bez3 = elevation_bezier(b2);

        return bez3;

    }


    bez3.C0 = C.tab[j1];

    bez3.C3 = C.tab[j2];

    
    double alpha, beta,lambda;

    alpha = (-15*n*n*n + 5 *n*n+ 2*n +4 )/(3* (n+2) * (3*n*n + 1));
    beta = (10* n*n*n - 15*n*n + n +2) / ( 3 * (n+2) * (3 *n*n +1));
    lambda= (70* n)/ ( 3 * (n*n -1) * ( n*n -4) * (3*n*n +1));

    Point calcul= {0,0};
    double gam;


    /* Calculer C1 */
    for (i = j1+1; i < j2; i++)
    {

        gam = fgamma(n,(double)i-(double)j1);

        calcul = add_point(calcul, produit_scalaire_point(C.tab[i], gam));

    }

    calcul = produit_scalaire_point(calcul, lambda);

    calcul = add_point(calcul, produit_scalaire_point(bez3.C0, alpha) );

    calcul = add_point(calcul, produit_scalaire_point(bez3.C3, beta) );

    bez3.C1 = calcul;



    /* Calculer C2 */

    calcul = (Point){0,0};

    for (i = j1+1; i < j2; i++)
    {
        calcul = add_point(calcul, produit_scalaire_point(C.tab[i], fgamma(n,(double)n-(double)i + (double) j1)));
    }

    calcul = produit_scalaire_point(calcul, lambda);

    calcul = add_point(calcul, produit_scalaire_point(bez3.C0, beta) );

    calcul = add_point(calcul, produit_scalaire_point(bez3.C3, alpha) );

    bez3.C2 = calcul;

    return bez3;
}



Point calculer_point_bezier3(Bezier3 B, double t)
{
    Point a,b;
    a.x =   (1-t)*(1-t)*(1-t)*B.C0.x;
    a.y =  (1-t)*(1-t)*(1-t)*B.C0.y;

    b = produit_scalaire_point(B.C1, 3*(1-t)*(1-t)*t);

    a = add_point(a, b);

    b = produit_scalaire_point(B.C2, 3*(1-t)*t*t);

    a = add_point(a, b);

    b = produit_scalaire_point(B.C3, t*t*t);

    a = add_point(a,b);

    return a;
}

double distance_bezier_3(Bezier3 B, Point P, double ti)
{
    Point a = calculer_point_bezier3(B, ti);

    return distance(a, P);
}



List_bezier_3 simplification_bezier_3(Tableau_Point C, int j1, int j2, double distance_seuil)
{
    int n = j2 - j1;
    Bezier3 B = approx_bezier3(C, j1 ,j2);

    double dmax = 0;
    int k = j1;
    int j,i;
    double ti,dj;

    for (j = j1+1; j < j2; j++)
    {

        i = j -j1;

        ti = (double)i / (double)n;

        dj = distance_bezier_3(B, C.tab[j], ti);

        if (dmax < dj)
        {
            dmax = dj;
            k = j;
        }

    }



    List_bezier_3 L = init_list_bezier_3();
    
    if (dmax <= distance_seuil)
    {
        ajouter_element_list_bezier_3(B, &L);
        return L;
    }

    else 
    {
        List_bezier_3 L1, L2;
        L1 = simplification_bezier_3(C, j1, k, distance_seuil );
        L2 = simplification_bezier_3(C, k, j2, distance_seuil );
        L1 = concatener_list_bezier_3(L1, L2);
        return L1;
    }
}
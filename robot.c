#include "robot.h"

void init_robot(etat *e, int x, int y)
{
    e->o = Est;
    e->x = x;
    e->y = y;
}

void avancer(etat *e)
{
    switch (e->o)
    {
    case Nord:
        e->y--;
        break;

    case Est:
        e->x++;
        break;

    case Sud:
        e->y++;
        break;

    case Ouest:
        e->x--;
        break;
    default:
        break;
    }
}

void tourner(etat *e, int droite)
{
    if (droite == 1)
    {
        switch (e->o)
        {
        case Nord:
            e->o = Est;
            break;
        
        case Sud:
            e->o = Ouest;
            break;
        
        case Est:
            e->o = Sud;
            break;

        default:
            e->o = Nord;
            break;
        }
    }

    else
    {
        switch (e->o)
        {
        case Nord:
            e->o = Ouest;
            break;
        
        case Sud:
            e->o = Est;
            break;
        
        case Est:
            e->o = Nord;
            break;

        default:
            e->o = Sud;
            break;
        }
    }
}


void nouvelle_orientation(etat *e, Image I)
{
    Pixel valeur_gauche;
    Pixel valeur_droite;

    switch (e->o)
    {
    case Nord:
        valeur_droite = get_pixel_image(I, e->x +1, e->y);
        valeur_gauche = get_pixel_image(I, e->x, e->y);
        break;
    
    case Est:
        valeur_droite = get_pixel_image(I, e->x +1, e->y+1);
        valeur_gauche = get_pixel_image(I, e->x+1, e->y);
        break;

    case Sud:
        valeur_droite = get_pixel_image(I, e->x , e->y+1);
        valeur_gauche = get_pixel_image(I, e->x+1, e->y+1);
        break;
    
    
    case Ouest:
        valeur_droite = get_pixel_image(I, e->x, e->y);
        valeur_gauche = get_pixel_image(I, e->x, e->y+1);   
        break;
    
    default:
        break;
    }

    if (valeur_gauche == NOIR)
        tourner(e, 0);
    else if(valeur_droite == BLANC)
        tourner(e, 1);
    
    
}

void afficher_pos(etat e)
{
    printf("Position: (%d, %d) Orientation: ", e.x, e.y);
    switch (e.o)
    {
    case Nord:
        printf("Nord\n");
        break;

    case Est:
        printf("Est\n");
        break;

    case Ouest:
        printf("Ouest\n");
        break;

    default:
        printf("Sud\n");
        break;
    }
}
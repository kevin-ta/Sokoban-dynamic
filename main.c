#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sokoban.h"

int main(int argc, char ** argv)
{
    int i;
    Boolean encore = true;
    char commande[MAXCOMMANDE+1];
    Position position;
    Grille g = initGrille("grille1.sok");
    Grille init = copieGrille(g);
    position = getSokoban(g);
    printf("\nPosition du Sokoban : x = %d , y = %d\n", position.x, position.y);
    if(position.x == 0 && position.y == 0)
    {
        error(NO_SOKOBAN);
        exit(1);
    }
    nouveauJeu(g);
    while (encore == true)
    {
        i = 0;
        afficheGrille(init);
        printf("> ");
        fgets(commande, sizeof(commande), stdin);
        while(commande[i] != '\n')
        {
            switch (commande[i])
            {
                case HAUT    : position = joue(init, HAUT, position, g); break;
                case BAS     : position = joue(init, BAS, position, g); break;
                case GAUCHE  : position = joue(init, GAUCHE, position, g); break;
                case DROITE  : position = joue(init, DROITE, position, g); break;
                case AIDE    : aide(); break;
                case QUITTER : encore = false; break;
                default: printf("Commande inconnue\n"); break;
            }
            i++;
        }
        if(gagne(init, position, g))
        {
            afficheGrille(init);
            printf("GG WP");
            encore = false;
        }
    }
    freeGrille(g);
    return 0;
}
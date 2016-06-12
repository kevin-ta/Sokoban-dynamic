#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sokoban.h"
#include "pileGrille.h"

int main(int argc, char ** argv)
{
    int i;
    Boolean encore = true;
    char commande[MAXCOMMANDE+1];
    Position position;
    List history = NULL;
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
    push(&history, init, position);
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
                case HAUT    : position = joue(init, HAUT, position, g); push(&history, init, position); break;
                case BAS     : position = joue(init, BAS, position, g); push(&history, init, position); break;
                case GAUCHE  : position = joue(init, GAUCHE, position, g); push(&history, init, position); break;
                case DROITE  : position = joue(init, DROITE, position, g); push(&history, init, position); break;
                case AIDE    : aide(); break;
                case QUITTER : encore = false; break;
                case UNDO    : if((history->next)!= NULL){pop(&history); init = copieGrille(history->grille); position = history->position;}else{printf("Retour impossible\n");}; break;
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
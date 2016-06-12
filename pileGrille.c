#include "pileGrille.h"

Cell * newCell()
{
    Cell * cell = (Cell *) malloc(sizeof(Cell));
    cell->next = NULL;
    return cell;
}

void freeCell(Cell * c)
{
    freeGrille(c->grille);
    free(c);
}

void freeList(List l)
{
    if(l != NULL)
    {
       Cell * temp = l->next;
       freeCell(l);
       freeList(temp);
    }
}

void push(List * l, Grille g, Position p)
{
    Cell * cell = newCell();
    cell->grille = copieGrille(g);
    cell->position = p;
    cell->next = *l;
    *l = cell;
}

void pop(List * l)
{
    List temp = (*l);
    *l = (*l)->next;
    freeCell(temp);
}
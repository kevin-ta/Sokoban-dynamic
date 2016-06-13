#ifndef _SOKOBAN_UNDO_H
#define _SOKOBAN_UNDO_H

#include "sokoban.h"

typedef struct _cell {
    Grille grille;
    Position position;
    struct _cell * next;
} Cell;
typedef Cell * List;

/**
 * Crée une nouvelle cellule
 * @param
 * @return Cell *
 */
Cell * newCell();

/**
 * Libère la mémoire allouée à une cellule
 * @param Cell *
 * @return
 */
void freeCell(Cell *);

/**
 * Libère la mémoire allouée à une liste
 * @param List
 * @return
 */
void freeList(List);

/**
 * Ajoute la grille et la position à la liste
 * @param List *, Grille, Position
 * @return
 */
void push(List *, Grille, Position);

/**
 * Retire le dernier élément de la liste
 * @param List *
 * @return
 */
void pop(List *);

#endif
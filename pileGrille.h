#ifndef _SOKOBAN_UNDO_H
#define _SOKOBAN_UNDO_H

#include "sokoban.h"

typedef struct _cell {
    Grille grille;
    Position position;
    struct _cell * next;
} Cell;
typedef Cell * List;

Cell * newCell();
void freeCell(Cell *);
void freeList(List);
void push(List *, Grille, Position);
void pop(List *);

#endif
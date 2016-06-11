#ifndef _SOKOBAN_H
#define _SOKOBAN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXCH   40
#define MAXCOMMANDE 20

typedef enum {false, true} Boolean;
typedef enum {MUR = '#', CAISSE = 'O', CIBLE = 'o', SOKOBAN = 'S', VIDE = '.'} Symbole;
typedef enum {HAUT = 'h', BAS = 'b', GAUCHE = 'g', DROITE = 'd', AIDE = 'a', QUITTER = 'q'} Commande;
typedef enum {NO_SOKOBAN, NO_GRILLE, NO_CAISSE, NO_EQUAL} CodeErreur;
typedef char* Ligne;
typedef struct _grille{
	int hauteur;
	int largeur;
	Ligne * grille;
} Grille;
typedef struct Position {
    int x;
    int y;
} Position;

void afficheGrille(Grille);
Grille initGrille(char *);
void freeGrille(Grille);
Position getSokoban(Grille);
void error(CodeErreur);
void nouveauJeu(Grille);
Boolean verif(Grille);
int compte(Grille, char);
void aide();
Position pas(Position, Commande);
Boolean possible(Grille, Position);
void deplace(Grille,Position,Position, Grille);
Position joue(Grille, Commande, Position, Grille);
Boolean gagne(Grille, Position, Grille);
Grille creerGrille(int, int);
Grille copieGrille(Grille);
#endif
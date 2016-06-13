#ifndef _SOKOBAN_H
#define _SOKOBAN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXCH   40
#define MAXCOMMANDE 20

typedef enum {false, true} Boolean;
typedef enum {MUR = '#', CAISSE = 'O', CIBLE = 'o', SOKOBAN = 'S', VIDE = '.'} Symbole;
typedef enum {HAUT = 'h', BAS = 'b', GAUCHE = 'g', DROITE = 'd', AIDE = 'a', QUITTER = 'q', UNDO = 'u'} Commande;
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

/**
 * Affiche la grille par itération
 * @param Grille
 * @return
 */
void afficheGrille(Grille);

/**
 * Initie la grille
 * @param char *
 * @return Grille
 */
Grille initGrille(char *);

/**
 * Libère la mémoire réservée à la grille
 * @param Grille
 * @return
 */
void freeGrille(Grille);

/**
 * Retourne la position du Sokoban sur la grille
 * @param Grille
 * @return Position
 */
Position getSokoban(Grille);

/**
 * Affiche l'erreur envoyé en paramètre sous forme verbale
 * @param CodeErreur
 * @return
 */
void error(CodeErreur);

/**
 * Crée une grille à afficher et une grille à cacher
 * @param Grille
 * @return
 */
void nouveauJeu(Grille);

/**
 * Vérifie si le nombre de caisses est égal au nombre de cibles
 * @param Grille
 * @return Boolean
 */
Boolean verif(Grille);

/**
 * Compte le nombre d'occurrence d'un élément dans la grille
 * @param Grille, char
 * @return integer
 */
int compte(Grille, char);

/**
 * Affiche l'aide
 * @param 
 * @return
 */
void aide();

/**
 * Retourne la future position suite à une commande mouvement
 * @param Position, Commande
 * @return Position
 */
Position pas(Position, Commande);

/**
 * Teste si un mouvement est possible en fonction de la grille
 * @param Grille, Position
 * @return Boolean
 */
Boolean possible(Grille, Position);

/**
 * Déplace le Sokoban sur la Grille
 * @param Grille, Position, Position, Grille
 * @return
 */
void deplace(Grille, Position, Position, Grille);

/**
 * Déplace le Sokoban sur la Grille
 * @param Grille, Position, Position, Grille
 * @return Position
 */
Position joue(Grille, Commande, Position, Grille);

/**
 * Teste si le joueur a gagné
 * @param Grille, Position, Grille
 * @return Boolean
 */
Boolean gagne(Grille, Position, Grille);

/**
 * Crée une grille et l'alloue
 * @param integer, integer
 * @return Grille
 */
Grille creerGrille(int, int);

/**
 * Copie la grille passé en paramètre et la renvoie
 * @param Grille
 * @return Grille
 */
Grille copieGrille(Grille);

#endif
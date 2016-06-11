#include "sokoban.h"

void afficheGrille(Grille g)
{
    int i;
    printf("\n");
    for(i = 0; i < g.hauteur; i++) printf("%s\n", g.grille[i]);
}

Grille initGrille(char *filename)
{
    int i;
    Grille g;
    FILE * file = NULL;
    char *end;
    int backslash = 0;

    file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", filename);
        exit(0);
    }

    fscanf(file, "%d %d", &g.hauteur, &g.largeur);
    g = creerGrille(g.hauteur, g.largeur);

    while(backslash != '\n') backslash = fgetc(file);

    for(i = 0; i < g.hauteur; i++)
    {
        fgets(g.grille[i], g.largeur + 2, file);
        if((end = strchr(g.grille[i], '\n')) != NULL) *end = '\0';
    }

    fclose(file);

    return g;
}

void freeGrille(Grille g)
{
    int i;
    for(i = 0; i < g.hauteur; i++) free(g.grille[i]);
}

Position getSokoban(Grille g)
{
    int i, j;
    Position position;
    position.x = 0;
    position.y = 0; 
    for(i = 0; i < g.hauteur; i++)
    {
        for(j = 0; j < g.largeur; j++)
        {
            if(g.grille[i][j] == SOKOBAN)
            {
                position.x = j;
                position.y = i;
                break;
            }
        }
    }
    return position;
}

void error(CodeErreur code)
{
    switch (code) {
        case NO_SOKOBAN : fprintf(stderr,"pas de Sokoban!\n"); break;
        case NO_GRILLE  : fprintf(stderr,"grille initiale incorrecte!\n"); break;
        case NO_CAISSE  : fprintf(stderr,"Il n'y a pas de caisse!\n"); break;
        case NO_EQUAL   : fprintf(stderr,"Nombre de cibles =/= nombre de caisses!\n"); break;
        default: fprintf(stderr,"code erreur inconnu!\n");
    }
    exit(code);
}

void nouveauJeu(Grille g)
{
    int i, j;
    if(!verif(g))
    {
        error(NO_GRILLE);
        exit(1);
    }
    for(i = 0; i < g.hauteur; i++)
    {
        for(j = 0; j < g.largeur; j++)
        {
            if(g.grille[i][j] == SOKOBAN || g.grille[i][j] == CAISSE) g.grille[i][j] = VIDE;
        }
    }
}

Boolean verif(Grille g)
{
    int i, cible = 0, caisse = 0, j;
    for(i = 0; i < g.hauteur; i++){
        if(strlen(g.grille[i]) != g.largeur) return 0;
        for(j = 0; j < g.largeur; j++)
        {
            if(g.grille[i][j] == CAISSE) caisse++;
            if(g.grille[i][j] == CIBLE) cible++;
        }
    }
    if(caisse < 1)
    {
        error(NO_CAISSE);
        exit(1);
    }
    if(caisse != cible)
    {
        error(NO_EQUAL);
        exit(1);
    }
    return 1;
}

int compte(Grille g, char c)
{
    int i, j, res = 0;
    for(i = 0; i < g.hauteur; i++)
    {
        for(j = 0; j < g.largeur; j++)
        {
            if(g.grille[i][j] == c) res++;
        }
    }
    return res;
}

void aide()
{
    printf("\n#### Legende : ####\n\n");
    printf("## Grille : ##\nMUR = #\nCAISSE = O\nCIBLE = o\nSOKOBAN = S\nVIDE = .\n");
    printf("## Commande : ##\nHAUT = h\nBAS = b\nGAUCHE = g\nDROITE = d\nAIDE = a\nQUITTER = q\n");
}

Position pas(Position pos_depart, Commande cmd)
{
    Position position;
    position.x = pos_depart.x;
    position.y = pos_depart.y;
    switch (cmd) {
        case HAUT    : position.y -= 1; break;
        case BAS     : position.y += 1; break;
        case GAUCHE  : position.x -= 1; break;
        case DROITE  : position.x += 1; break;
        default: error(NO_GRILLE);
    }
    return position;
}

Boolean possible(Grille g, Position pos)
{
    if((pos.x > g.largeur) || (pos.x < 0) || (pos.y > g.hauteur) || (pos.y < 0) || g.grille[pos.y][pos.x] == MUR) printf("Il y a un mur devant vous!\n");
    else if(g.grille[pos.y][pos.x] == VIDE || g.grille[pos.y][pos.x] == CIBLE) return true;
    return false;
}

void deplace(Grille jeu, Position pos_a, Position pos_b, Grille init)
{
    jeu.grille[pos_b.y][pos_b.x] = jeu.grille[pos_a.y][pos_a.x];
    jeu.grille[pos_a.y][pos_a.x] = init.grille[pos_a.y][pos_a.x];
}

Position joue(Grille jeu, Commande dir, Position depart, Grille init)
{
    Position position, caisse;
    position = pas(depart, dir);
    if(possible(jeu, position))
    {
        deplace(jeu, depart, position, init);
        return position;
    }
    else
    {
        caisse = pas(position, dir);
        if(jeu.grille[position.y][position.x] == CAISSE && possible(jeu, caisse))
        {
            deplace(jeu, position, caisse, init);
            deplace(jeu, depart, position, init);
            return position;
        }
    }
    return depart;
}

Boolean gagne(Grille jeu, Position soko, Grille init)
{
    int i, j;
    for(i = 0; i < jeu.hauteur; i++){
        for(j = 0; j < jeu.largeur; j++)
        {
            if(init.grille[i][j] == CIBLE)
            {
                if(jeu.grille[i][j] != CAISSE) return false;
                else if((soko.x == j) && (soko.y == i)) return false;
            }
        }
    }
    return true;
}

Grille creerGrille(int hauteur, int largeur)
{
    Grille init;
    int i;
    init.hauteur = hauteur;
    init.largeur = largeur;
    init.grille = (Ligne *) malloc(sizeof(Ligne *) * init.hauteur);

    for(i = 0 ; i < init.hauteur; i++) init.grille[i] = (char *) malloc(sizeof(char *) * init.largeur + 2);

    return init;
}

Grille copieGrille(Grille g)
{
    int i;
    Grille init = creerGrille(g.hauteur, g.largeur);

    for(i = 0; i < g.hauteur; i++) memcpy(init.grille[i], g.grille[i], g.largeur + 1);

    return init;
}
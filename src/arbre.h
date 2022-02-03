#ifndef ARBRE_H
#define ARBRE_H

/****************************************************
 * struct ARB : Structure de l'arbre                *
 *    mot : Pointeur vers un tableau de caractere   *
 *          dynamiquement allouer                   *
 *    gauche : Pointeur vers la noeud 'au dessous'  *
 *             et a gauche                          *
 *    droite : Pointeur vers La noeud 'au dessous'  *
 *             et a droite                          *
 *    nbr_occur : Nombre d'occurence du mot dans    *
 *                le texte                          *
 *    nbr_ligne : Un tableau des lignes d'occurence *
 *                du mot                            *
 ****************************************************/
struct ARB {
  char *mot;
  struct ARB *gauche;
  struct ARB *droite;
  int nbr_occur;
  int *nbr_ligne;
};


char *lire_mot(const char *, int *);

struct ARB *construire_arbre(const char *, const int *, int);

#endif

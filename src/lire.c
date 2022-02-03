#include<stdio.h>
#include<stdlib.h>

/*Ceci sert uniquement à vérifier si les prototypes
 et les définitions de fonctions sont compatibles */
#include "lire.h"

/*************************************************************************
 *  lire_tableau :  Renvoie un tableau de caractères rempli              *
 *                  de caractères d'un fichier texte 'file_name'         *
 *                                                                       *
 *  ATTENTION ! :   Cette fonction peut renvoyer un résultat inattendu   *
 *                  en raison de caractères cachés dans le fichier texte *
 *************************************************************************/
char *lire_tableau(char *file_name, int *nbr_ligne) {

    int file_size, i = 0;
    FILE *fp = fopen(file_name, "r");
    char *T, c;

    *nbr_ligne = 1;

    if ( fp == NULL ) {
      printf("\nErreur lors de l'ouverture du fichier!");
      exit(EXIT_FAILURE);
    }

    // Déterminer la longueur du fichier texte en octets (un octet par caractère)
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    T = (char *)malloc(file_size);

    if ( T == NULL ) {
      printf("\nmalloc a échoué @ lire_tableau!");
      exit(EXIT_FAILURE);
    }

    /* Cette boucle a deux objectifs: remplir le tableau T
       et déterminer le nombre de lignes dans le fichier 'file_name' */
    while ( ( c = fgetc(fp) ) != EOF ) {

        if ( c == '\n' ) (*nbr_ligne)++;
        T[i++] = c;

    }

    // Ajouter le caractère nul à la fin du tableau
    T[i] = '\0';

    // Fermeture du pointeur FILE - pas nécessaire
    fclose(fp);

    return T;
}

/******************************************************************************
 *  construire_tableau_ligne :  Renvoie un tableau L d'entiers où L[i]        *
 *                              correspond à la position du premier caractère *
 *                              de la i-ième ligne dans un fichier texte.     *
 ******************************************************************************/
int *construire_tableau_ligne(const char *T, int max_ligne) {

  int *L = (int *)malloc(sizeof(int)*max_ligne), j = 2;

  // Vérification de la fonction malloc
  if ( L == NULL ) {
    printf("\nmalloc a échoué @ construire_tableau_ligne!");
    exit(EXIT_FAILURE);
  }

  // Valeur arbitraire de L[0]
  L[0] = -1;
  L[1] = 0;

  for ( int i = 0; j <= max_ligne; i++) {
    if ( T[i] == '\n' ) {
        L[j++] = i + 1;
    }
  }

  return L;
}

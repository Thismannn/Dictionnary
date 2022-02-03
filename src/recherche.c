#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

/*Ceci sert uniquement à vérifier si les prototypes
 et les définitions de fonctions sont compatibles */
#include "recherche.h"

#include "arbre.h"


/*********************************************************************************
 *  chercher_ligne_mot : Renvoie la ligne dans laquelle se trouve 'mot'          *
 *                       à partir de sa position de départ 'p' dans le tableau T *
 *********************************************************************************/
int chercher_ligne_mot(const int *L, int debut_mot, int max_ligne) {

  for ( int j = 1; j < max_ligne + 1; j++) {
    if ( L[j] > debut_mot) {
      return j-1;
    }
  }
  return max_ligne;
}

/*****************************************************************************************
 *  recherche_mot_tableau : Modifie 'occur' au nombre d'occurrences de 'mot' dans        *
 *                          le tableau 'T'                                               *
 *                          Renvoie un tableau des lignes dans lesquelles 'mot' apparaît *
 *****************************************************************************************/
int *recherche_mot_tableau(const char *mot, const char *T, const int *L, int *occur, int max_ligne) {

  int i, T_length = strlen(T), mot_length = strlen(mot);
  int *H, mot_lignes[max_ligne], ligne, k = 0, nbr_mot = 0;

  // Parcourir la chaîne de caractère T
  for ( int j = 0; j < T_length; j++) {

    /*Si le premier caractère de 'mot' correspond à un caractère de 'T',
     nous vérifions le reste du mot */
    if ( mot[0] == toupper(T[j]) ) {

      ++j;
      for ( i = 1; (i < mot_length) && (j < T_length); j++, i++) {

        if ( (mot[i] != toupper(T[j])) ) {
          break;
        }
      }

      // Cette condition implique qu'on a trouver un `mot`
      if ( (i == mot_length) && (!isalpha(T[j])) ) {                // ADDED THIS LINE TO CORRECT A WORD DETECTION PROBLEM
        nbr_mot++;
        ligne = chercher_ligne_mot(L, j - mot_length, max_ligne);

        /*  La raison de cette 'if' est d'éviter le cas où 'mot' pourrait se produire
            plus d'une fois dans la même ligne */
        if (k == 0) {
          mot_lignes[k] = ligne;
          k++;
        } else if ( ligne != mot_lignes[k - 1] ) {
          mot_lignes[k] = ligne;
          k++;
        }

        --j;
      }

    }

  } // FIN BOUCLE FOR

  // Modifier le nombre d'occurrences à partir du pointeur 'occur'
  *occur = nbr_mot;

  // Allocation dynamique du pointeur à retourner
  H = (int *)malloc(sizeof(int)*(k + 1));

  // Vérification si malloc a bien fonctionné
  if (H == NULL) {
      printf("malloc a échoué @ recherche_mot_tableau!");
      exit(-1);
  }

  for ( int j = 0; j < k; j++) {
    H[j] = mot_lignes[j];
  }

  // Une astuce pour connaître la fin d'un tableau d'entiers
  H[k] = -1;

  return H;
}

/***********************************************************************************************
 *  print_lignes : Afficher le numéro et le contenu de chaque ligne où un certain mot apparaît *
 ***********************************************************************************************/
 void print_lignes(const char *T, const int *L, const int *mot_lignes, int max_ligne) {

   int j, k;

   for ( int i = 0; mot_lignes[i] > 0; i++) {

     k = mot_lignes[i];

     // Affichage des numéros de ligne
     printf("%d", k);
     putchar('\t');

     // Affichage du contenu de la k-ième ligne
     if ( k != max_ligne) {

       for ( j = L[k]; j < L[k + 1]; j++) {
         putchar(T[j]);
       }

     // Cette 'else' est pour afficher la dernière ligne de T
     } else {

       for( j = L[k]; T[j] != EOF; j++) {
         putchar(T[j]);
       }
       return;
     }
     putchar('\n');

   } // FIN BOUCLE FOR
 }


 /*************************************************************************
  * recherche_mot : Affiche le nombre d'occurrence du 'mot' dans le texte *
  *                                                                       *
  *                 Afficher le numéro et le contenu de chaque ligne      *
  *                 où 'mot' apparaît                                     *
  * affichage : si 0 alors on fait le calcule mais sans affichage du      *
  *             resultat, sinon, on affiche le resultat du calcule        *
  *************************************************************************/
 void recherche_mot_arbre(const char *mot, struct ARB *premier_noeud, const char *T, const int *L, int max_ligne, bool affichage) {

   /* Le but de cette boucle est de trouver le pointeur, s'il existe,
      qui pointe vers une structure ARB contenant le mot correspondant.
      Nous traduisons le cas où il n'existe pas par un pointeur nul */
   while ( premier_noeud != NULL ) {

     if ( strcmp(mot, premier_noeud -> mot) < 0 ) {

       premier_noeud = premier_noeud -> gauche;

     } else if ( strcmp(mot, premier_noeud -> mot) > 0 ) {

       premier_noeud = premier_noeud -> droite;

     } else {
       break;
     }

   } // FIN BOUCLE WHILE

   if (affichage) {
    // Si 'mot' n'existe pas dans l'arbre
    if ( premier_noeud == NULL ) {
      printf("\n\"%s\" n\'existe pas dans le fichier !", mot);
      return;
    }

    printf("\n\"%s\" existe dans le fichier. \n\n", mot);
    printf("Nombre d'occurence : \t%d\n", premier_noeud -> nbr_occur);

    printf("\nNumeros -> Contenu:\n\n");
    print_lignes(T, L, premier_noeud -> nbr_ligne, max_ligne);
  }
 }

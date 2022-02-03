#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

/*Ceci sert uniquement à vérifier si les prototypes
 et les définitions de fonctions sont compatibles */
#include "arbre.h"
#include "recherche.h"

/***************************************************************
 * lire_mot : Lire un mot du tableau T                         *
 *                                                             *
 *            Renvoie un pointeur qui pointe vers une chaîne   *
 *            correspondant à un mot alloué dynamiquement      *
 *                                                             *
 *            Modifie un entier à la nouvelle position de      *
 *            départ pour le prochain appel read_word          *
 *                                                             *
 ***************************************************************/
char *lire_mot(const char *T, int *p) {

   char mot[30], *mot_finale;
   int length = strlen(T);
   short j = 0;

   /* Passer en revue tous les caractères non alphabétiques jusqu'à
      ce qu'un premier caractère soit rencontré ou que la fin du tableau soit atteinte*/
   while ( (!isalpha(T[*p])) && (*p < length) ) {
     (*p)++;
   }

   /* S'il n'y a pas de mots, ou si nous avons atteint la fin du tableau
      nous retournons un pointeur nul */
   if (*p == length) {
     return NULL;
   }

   mot[j++] = toupper(T[(*p)++]);

   // Copiez les caractères dans un tableau intermédiaire
   for ( ;*p < length; (*p)++ ) {
     if ( !isalpha(T[*p]) ) {
       break;
     }
     mot[j++] = toupper(T[*p]);
   }
   mot[j] = '\0';

   /* Allocation dynamique afin d'éviter de toujours renvoyer un tableau
      de longueur fixe */
   mot_finale = (char *)malloc(strlen(mot) + 1);
   if (mot_finale == NULL) {
     printf("NULL failed !");
     exit(-1);
   }

   // Remplir le tableau alloué dynamiquement avec les caractères du 'mot'
   strcpy(mot_finale, mot);

   return mot_finale;
 }

/******************************************************************
 *  construire_noeud : Construit un nœud selon la structure ARB   *
 ******************************************************************/
struct ARB *construire_noeud(char *mot, struct ARB *gauche, struct ARB *droite, int nbr_occur, int *nbr_ligne) {

  struct ARB *nouveau_noeud;

  nouveau_noeud = (struct ARB *)malloc(sizeof(struct ARB));

  if ( nouveau_noeud == NULL ) {
    printf("Malloc failed @ construire_noeud !");
    exit(-1);
  }

  nouveau_noeud -> mot = mot;
  nouveau_noeud -> gauche = gauche;
  nouveau_noeud -> droite = droite;
  nouveau_noeud -> nbr_ligne = nbr_ligne;
  nouveau_noeud -> nbr_occur = nbr_occur;
}


/*************************************************************************
 * construire_arbre : Construire l'arbre binaire à partir d'un tableau   *
 *                    de caractères T et un tableau d'entier L           *
 *                                                                       *
 *                    Renvoie un pointeur vers le premier nœud du arbre  *
 *                                                                       *
 *************************************************************************/
struct ARB *construire_arbre(const char *T, const int *L, int max_ligne) {


  struct ARB *premier_noeud, *nouveau_noeud, *noeud;
  char *ch;
  int position = 0, *nbr_ligne, nbr_occur;

  ch = lire_mot(T, &position);
  nbr_ligne = recherche_mot_tableau(ch, T, L, &nbr_occur, max_ligne);

  // Construction du premier nœud contenant le premier mot
  premier_noeud = construire_noeud(ch, NULL, NULL, nbr_occur, nbr_ligne);

    /* Maintenant, nous construisons le nœud du mot suivant
       et nous déterminons sa position appropriée */

    // Le but de cette boucle est de parcourir TOUS les mots du tableau T
    while ( (ch = lire_mot(T, &position)) != NULL ) {

      nbr_ligne = recherche_mot_tableau(ch, T, L, &nbr_occur, max_ligne);
      nouveau_noeud = construire_noeud(ch, NULL, NULL, nbr_occur, nbr_ligne);

      // Cette boucle vise à déterminer où nous allons positionner le nouveau nœud créé
      noeud = premier_noeud;

      for (;;) {
        if ( strcmp(ch, noeud -> mot) < 0 ) {

          if ( noeud -> gauche == NULL ) {
            noeud -> gauche = nouveau_noeud;
            break;
          }
          noeud = noeud -> gauche;

        } else if ( strcmp(ch, noeud -> mot) > 0 ) {

          if ( noeud -> droite == NULL ) {
            noeud -> droite = nouveau_noeud;
            break;
          }
          noeud = noeud -> droite;

        } else {

          // Ce dernier 'else' vise à éviter la multiplication des mots dans l'arbre
          break;

        }

      }
    } // FIN BOUCLE WHILE


  return premier_noeud;
}

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "lire.h"
#include "arbre.h"
#include "recherche.h"
#include "chrono.h"

char *mot_majuscule(char *);

int main(int argc, char *argv[]) {

  struct ARB *arbre;
  int *L, max_ligne;
  float t, total_time;
  char *T, *mot_maj;

  if ( argc == 1 ) {

      printf("\nVous devez entrer le nom de fichier à lire!");
      exit(EXIT_FAILURE);

  } else if ( argc == 2 ) {   // choisissez un mot distinct 1000 et recherchez chacun dans l'arbre

    struct ARB *noeud;
    char *mots[1000];
    bool gauche_droite;       // false -> gauche, true -> droite
    bool passer_choisir;      // false -> passer, true -> choisir
    bool exists;              // false -> le mot n'a pas été choisi auparavant
    int i = 0;

    // construction des tables T et L
    chrono_reset();
    T = lire_tableau(argv[1], &max_ligne);
    L = construire_tableau_ligne(T, max_ligne);
    t = chrono_lap();
    total_time += t;

          printf("\n-----------------------------------------------------------------------------\n");
          printf("Temps (lecture de fichier + construction L et T) : \t%.6fs", t);
          printf("\n-----------------------------------------------------------------------------\n");

    // construction de l'arbre
    chrono_reset();
    arbre = construire_arbre(T, L, max_ligne);
    t = chrono_lap();
    total_time += t;

          printf("\n-----------------------------------------------------------------------------\n");
          printf("Temps (construction arbre) : \t%.6fs", t);
          printf("\n-----------------------------------------------------------------------------\n");


    // remplir mots[] avec 1000 noms arbitraires DIFFÉRENTS choisit de l'arbre
    chrono_reset();
    noeud = arbre;

    /*  configuration de la fonction rand pour éviter d'obtenir le même résultat
        à chaque exécution du programme */
    srand((unsigned)time(NULL));

    do {

          exists = false;       // on suppose que le mot suivant n'existe pas déjà dans les mots[]

          /*  si on atteint une racine de l'arbre sans stocker 1000 mots
              on recommence à partir de la tête de l'arbre */
          if ( noeud == NULL ) noeud = arbre;

          // configurer passer_choisir arbitrairement sur vrai ou faux
          passer_choisir = rand() % 2;

          // si on obtient 'choisir', on choisit le nœud courant
          if ( passer_choisir ) {

            // cette boucle s'assure que nous choisissons des mots distincts
            for ( int k = 0; k < i; k++) {
              if ( mots[k] == noeud -> mot ) {
                exists = true;
                break;
              }
            } // FIN BOUCLE FOR

            if ( !exists ) {
              mots[i] = noeud -> mot;
              printf("\nmot %4d:\t\t%s", i+1, mots[i]);
              i++;
            }

          } // FIN IF
          gauche_droite = rand() % 2;

          /*  quel que soit le résultat de «existe», nous choisissons arbitrairement
              de passer au nœud inférieur gauche ou droit */
          if ( gauche_droite )  noeud = noeud -> droite;
          else  noeud = noeud -> gauche;

    } while ( i < 1000 );

    t = chrono_lap();
    total_time += t;


          printf("\n-----------------------------------------------------------------------------\n");
          printf("Temps (construction tableau 1000 mot arbitraire) : \t%.6fs", t);
          printf("\n-----------------------------------------------------------------------------\n");

      chrono_reset();
    /*  en recherchant les 1000 mots choisis arbitrairement dans l'arbre,
        le temps d'exécution devrait être remarquablement élevé, étant donné
        que nous n'allons pas afficher le résultat de chaque recherche */
    for ( i = 0; i < 1000; i++) recherche_mot_arbre(mots[i], arbre, T, L, max_ligne, false);
    t = chrono_lap();

    total_time += t;

          printf("\n-----------------------------------------------------------------------------\n");
          printf("Temps (recherche 1000 mots) : \t%.6fs", t);
          printf("\n-----------------------------------------------------------------------------\n");

  } else {

    // construction des tables T et L
    chrono_reset();
    T = lire_tableau(argv[1], &max_ligne);
    L = construire_tableau_ligne(T, max_ligne);
    t = chrono_lap();
    total_time += t;

          printf("\n-----------------------------------------------------------------------------\n");
          printf("Temps (lecture de fichier + construction L et T) : \t%.6fs", t);
          printf("\n-----------------------------------------------------------------------------\n");

    // construction de l'arbre
    chrono_reset();
    arbre = construire_arbre(T, L, max_ligne);
    t = chrono_lap();
    total_time += t;

          printf("\n-----------------------------------------------------------------------------\n");
          printf("Temps (construction arbre) : \t%.6fs", t);
          printf("\n-----------------------------------------------------------------------------\n");

    /*  Cette boucle vise à trouver chaque mot de ligne de commande dans l'arbre binaire
        dans cette cas, on affiche le résultat */
    for ( int i = 2; i < argc; i++) {

      chrono_reset();

      mot_maj = mot_majuscule(argv[i]);

      recherche_mot_arbre(mot_maj, arbre, T, L, max_ligne, 1);
      t = chrono_lap();

      free(mot_maj);

      total_time += t;

        printf("\n-----------------------------------------------------------------------------\n");
        printf("Temps (recherche mot %s) : \t%.6fs", argv[i], t);
        printf("\n-----------------------------------------------------------------------------\n");

    } // FIN BOUCLE FOR

  } // FIN ELSE

        // Affichage du temps d'exécution total
        printf("\n-----------------------------------------------------------------------------\n");
        printf("Temps totale : \t%.6fs", total_time);
        printf("\n-----------------------------------------------------------------------------\n");

  return 0;
}

char *mot_majuscule(char *mot) {
  int mot_length = strlen(mot);
  char *mot_maj = malloc(mot_length + 1);

  if (mot_maj == NULL) {
    printf("\nmalloc a échoué @ mot_majuscule!");
    exit(EXIT_FAILURE);
  }

  for ( int i = 0; i < mot_length; i++) mot_maj[i] = toupper(mot[i]);

  return mot_maj;
}

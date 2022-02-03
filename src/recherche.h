#ifndef RECHERCHE_H
#define RECHERCHE_H

#include<stdbool.h>
#include "arbre.h"

void recherche_mot_arbre(const char *, struct ARB *, const char *, const int *, int, bool);

int *recherche_mot_tableau(const char *, const char *, const int *, int *, int);

#endif

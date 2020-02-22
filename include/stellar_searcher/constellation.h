#ifndef CONSTELLATION_H
#define CONSTELLATION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stellar_searcher/stellarCoordinate.h"

typedef struct {
  char name[64];
  StellarCoordinate *stars;
  int len;
} Constellation;

Constellation* ConstellationCreate();
void ConstellationInit(Constellation *cs, char name[], StellarCoordinate *stars, int len);
void ConstellationDestroyStars(Constellation *cs);
void ConstellationDestroy(Constellation *cs);

void ConstellationSetName(Constellation *cs, char name[]);
void ConstellationSetLen(Constellation *cs, int len);

char* ConstellationGetName(Constellation *cs);
StellarCoordinate* ConstellationGetStars(Constellation *cs);
int ConstellationGetLen(Constellation *cs);

void ConstellationAdd(Constellation *cs, StellarCoordinate *star);

void ConstellationPrint(Constellation *cs);

#endif

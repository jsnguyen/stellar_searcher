#ifndef CONSTELLATION_H
#define CONSTELLATION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stellar_searcher/stellarCoordinate.h"

typedef struct {
  char name[64];
  StellarCoordinate *stars;
  int len_s;
  int *pointingOrder;
  int len_po;
} Constellation;

Constellation* ConstellationCreate();
void ConstellationInit(Constellation *cs, char name[], StellarCoordinate *stars, int len_s, int *pointingOrder, int len_po);
void ConstellationDestroyStars(Constellation *cs);
void ConstellationDestroyPointingOrder(Constellation *cs);
void ConstellationDestroy(Constellation *cs);

void ConstellationSetName(Constellation *cs, char name[]);
void ConstellationSetLenS(Constellation *cs, int len_s);
void ConstellationSetLenPO(Constellation *cs, int len_s);

char* ConstellationGetName(Constellation *cs);
StellarCoordinate* ConstellationGetStars(Constellation *cs);
int ConstellationGetLenS(Constellation *cs);
int ConstellationGetLenPO(Constellation *cs);

void ConstellationAdd(Constellation *cs, StellarCoordinate *star);

void ConstellationPrint(Constellation *cs);

#endif

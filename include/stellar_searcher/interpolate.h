#ifndef INTERPOLATE_H
#define INTERPOLATE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stellar_searcher/threeVector.h"
#include "stellar_searcher/stellarCoordinate.h"
#include "stellar_searcher/constellation.h"

double GetGreatCircleDistance(StellarCoordinate *a, StellarCoordinate *b);
void SphericalLinearInterpolation(StellarCoordinate *a, StellarCoordinate *b, StellarCoordinate* points, int nPoints);

void InterpolateConstellation(Constellation *c, StellarCoordinate* points, int nPointsBetweenStars);

#endif

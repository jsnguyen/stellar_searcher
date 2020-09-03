#ifndef STELLARCOORDINATE_H
#define STELLARCOORDINATE_H

#define PI 3.141592653589

#define DEG2RAD PI/180.0
#define RAD2DEG 180.0/PI
#define RAD2HR  12.0/PI

#include <stdio.h>
#include <string.h>
#include "stellar_searcher/threeVector.h"
#include "stellar_searcher/matrix.h"
#include "stellar_searcher/celestialTime.h"
#include "stellar_searcher/dateTime.h"
#include "sofa.h"

typedef enum{
  CS_EQUATORIAL,
  CS_HADEC,
  CS_AZALT,
  CS_ECLIPTIC,
  CS_GALACTIC,
  CS_SUPERGALACTIC
} CS_TYPE;

typedef enum{
  EPOCH_J2000,
  EPOCH_JNOW
} EPOCH_TYPE;

typedef enum{
  RAD,
  DEG,
  HRDEG
} UNIT;

/*
 * EVERYTHING USES DECIMAL DEGREES FOR CONSISTENCY
 */

typedef struct {
    double lon,lat; // ra,dec 
    DateTime dt;

    CS_TYPE cs;
    EPOCH_TYPE epoch;
} StellarCoordinate;

StellarCoordinate* StellarCoordinateCreate();
void StellarCoordinateInit(StellarCoordinate *sc, double lon, double lat, DateTime dt, CS_TYPE type, EPOCH_TYPE epoch);
void StellarCoordinateDestroy();

void StellarCoordinateCopy(StellarCoordinate *a, StellarCoordinate *b);

double StellarCoordinateGetLon(StellarCoordinate *sc);
double StellarCoordinateGetLat(StellarCoordinate *sc);
DateTime StellarCoordinateGetDateTime(StellarCoordinate *sc);
CS_TYPE StellarCoordinateGetCoordinateSystemType(StellarCoordinate *sc);
EPOCH_TYPE StellarCoordinateGetEpochType(StellarCoordinate *sc);

void StellarCoordinateSet(StellarCoordinate *sc, double lon, double lat, DateTime dt, CS_TYPE type, EPOCH_TYPE epoch);

void StellarCoordinateSetLon(StellarCoordinate *sc, double lon);
void StellarCoordinateSetLat(StellarCoordinate *sc, double lat);
void StellarCoordinateSetDateTime(StellarCoordinate *sc, DateTime dt);
void StellarCoordinateSetCoordinateSystemType(StellarCoordinate *sc, CS_TYPE type);
void StellarCoordinateSetEpochType(StellarCoordinate *sc, EPOCH_TYPE epoch);

// Conversions 
void StellarCoordinateEqToHoriz(StellarCoordinate *sc, DateTime dt, double g_lon, double g_lat, StellarCoordinate *out);

void StellarCoordinateEqToHaDec(StellarCoordinate *sc, DateTime dt, double g_lon, double g_lat, StellarCoordinate *out);

void StellarCoordinateJ2000ToJNow(StellarCoordinate *in, StellarCoordinate *out);

void StellarCoordinatePrintDecimal(StellarCoordinate *sc, UNIT unit);

void MakeCoordinateToVector(double lo, double la, ThreeVector *tv);
void MakeVectorToCoordinate(ThreeVector *tv, double a[2]);

#endif

#ifndef STELLARCOORDINATE_H
#define STELLARCOORDINATE_H

#define PI 3.14159265

#define J2000 2000

#include <stdio.h>
#include <string.h>
#include "stellar_searcher/threeVector.h"
#include "stellar_searcher/matrix.h"
#include "stellar_searcher/celestialTime.h"

typedef enum{
  CS_EQUATORIAL,
  CS_AZALT,
  CS_HADEC,
  CS_ECLIPTIC,
  CS_GALACTIC,
  CS_SUPERGALACTIC
} CS_TYPE;

typedef enum{
  EPOCH_J2000,
  EPOCH_JNOW
} EPOCH_TYPE;

typedef enum{
  NO_ATM_CORR,
  ATM_CORR
} ATM_CORR_TYPE;

/*
 * EVERYTHING USES DECIMAL DEGREES FOR CONSISTENCY
 */

typedef struct {
    double lon,lat; // ra,dec 
    double epoch_yr; // units of decimal years

    CS_TYPE cs;
    EPOCH_TYPE epoch;
    ATM_CORR_TYPE atm_corr;
} StellarCoordinate;

StellarCoordinate* StellarCoordinateCreate();
void StellarCoordinateInit(StellarCoordinate *sc, double lon, double lat, double epoch_yr, CS_TYPE type, EPOCH_TYPE epoch, ATM_CORR_TYPE atm_corr);
void StellarCoordinateDestroy();

void StellarCoordinateCopy(StellarCoordinate *a, StellarCoordinate *b);

double StellarCoordinateGetLon(StellarCoordinate *sc);
double StellarCoordinateGetLat(StellarCoordinate *sc);
double StellarCoordinateGetEpochYear(StellarCoordinate *sc);
CS_TYPE StellarCoordinateGetCoordinateSystemType(StellarCoordinate *sc);
EPOCH_TYPE StellarCoordinateGetEpochType(StellarCoordinate *sc);
ATM_CORR_TYPE StellarCoordinateGetAtmosphericCorrectionType(StellarCoordinate *sc);

void StellarCoordinateSet(StellarCoordinate *sc, double lon, double lat, double epoch_yr, CS_TYPE type, EPOCH_TYPE epoch, ATM_CORR_TYPE atm_corr);

void StellarCoordinateSetLon(StellarCoordinate *sc, double lon);
void StellarCoordinateSetLat(StellarCoordinate *sc, double lat);
void StellarCoordinateSetEpochYear(StellarCoordinate *sc, double epoch_yr);
void StellarCoordinateSetCoordinateSystemType(StellarCoordinate *sc, CS_TYPE type);
void StellarCoordinateSetEpochType(StellarCoordinate *sc, EPOCH_TYPE epoch);
void StellarCoordinateSetAtmosphericCorrectionType(StellarCoordinate *sc, ATM_CORR_TYPE atm_corr);

// Conversions 
void StellarCoordinateEqToHoriz(StellarCoordinate *sc, double lst, double lat, StellarCoordinate *out);
void StellarCoordinateEqToHaDec(StellarCoordinate *sc, double q, StellarCoordinate *out);

void StellarCoordinateEqToHorizWithCorrection(StellarCoordinate *sc, double lst, double lat, StellarCoordinate *out);
void StellarCoordinateEqToHaDecWithCorrection(StellarCoordinate *sc, double lst, double lat, StellarCoordinate *out);

void StellarCoordinateJ2000ToJNow(StellarCoordinate *in, StellarCoordinate *out);

void StellarCoordinatePrintDecimal(StellarCoordinate *sc);
void StellarCoordinatePrintEq(StellarCoordinate *sc);
void StellarCoordinatePrintHoriz(StellarCoordinate *sc);
void StellarCoordinatePrintHaDec(StellarCoordinate *sc);

void MakeCoordinateToVector(double lo, double la, ThreeVector *tv);
void MakeStellarCoordinateToVector(StellarCoordinate *sc, ThreeVector *tv);
void MakeVectorToCoordinate(ThreeVector *tv, double a[2]);

void MakeEqToHaDec(Matrix *a, double lst);

void MakeHaDecToHoriz(Matrix *a, double lat);
void MakeHorizToHaDec(Matrix *a, double lat);

void MakeEqToGal(Matrix *a);

void MakeHorizToEq(Matrix *a, double lst, double lat);
void MakeEqToHoriz(Matrix *a, double lst, double lat);

void MakePrecessionMatrix(Matrix *a, double JD);
void MakeNutationMatrix(Matrix *a, double JD);

double GetAtmosphericRefractionCorrection(double alt);


#endif

#include "stellar_searcher/matrix.h"
#include "stellar_searcher/threeVector.h"
#include "stellar_searcher/celestialTime.h"
#include "stellar_searcher/stellarCoordinate.h"
#include "stellar_searcher/dateTime.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Checking the location of Sirius_a from J2000 to JNow and JNow w/ atmospheric correction and between equatorial and altaz coordinate systems

int main(){

  double tLat = 33*DEG2RAD;
  double tLon = -106*DEG2RAD;
  printf("(lat,lon): %f, %f\n", tLat*RAD2DEG, tLon*RAD2DEG);

  DateTime dt;
  SetDateTime(&dt, 2018,1,7,0,0,0);

  double JDN = GetJDN(dt);
  double fracJD = GetFractionalJD(dt);
  printf("JD: %f\n", JDN+fracJD);

  DateTime J2000;
  SetDateTime(&J2000, 2000,1,1,12,0,0);

  StellarCoordinate Sirius_a;
  StellarCoordinateInit(&Sirius_a,101.28394*DEG2RAD,-16.7225*DEG2RAD,J2000,CS_EQUATORIAL,EPOCH_J2000);

  printf("equatorial\n");
  StellarCoordinatePrintDecimal(&Sirius_a, RAD);
  StellarCoordinatePrintDecimal(&Sirius_a, DEG);

  StellarCoordinate Sirius_a_hadec;

  printf("equatorial -> hadec\n");
  StellarCoordinateEqToHaDec(&Sirius_a, dt, tLon, tLat, &Sirius_a_hadec);
  StellarCoordinatePrintDecimal(&Sirius_a_hadec, RAD);
  StellarCoordinatePrintDecimal(&Sirius_a_hadec, HRDEG);

  StellarCoordinate Sirius_a_horiz;

  printf("equatorial -> horiz\n");
  StellarCoordinateEqToHoriz(&Sirius_a, dt, tLon, tLat, &Sirius_a_horiz);
  StellarCoordinatePrintDecimal(&Sirius_a_horiz, RAD);
  StellarCoordinatePrintDecimal(&Sirius_a_horiz, DEG);

  return 0;
}

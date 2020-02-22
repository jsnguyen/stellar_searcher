#include "stellar_searcher/matrix.h"
#include "stellar_searcher/threeVector.h"
#include "stellar_searcher/celestialTime.h"
#include "stellar_searcher/stellarCoordinate.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Checking the location of Sirius_a from J2000 to JNow and JNow w/ atmospheric correction and between equatorial and altaz coordinate systems

int main(){

  double tLat = -77;
  double tLon = 39;

  //double JD = getCurrentJD();
  double JD = 2458388.0;
  double h_LAST = GetLAST(JD,tLon);
  double d_LAST = (h_LAST / 24.0) * 360.0;

  printf("JD: %f\n",JD);
  printf("LAST: %f\n",d_LAST);
  printf("\n");

  StellarCoordinate Sirius_a;
  StellarCoordinateInit(&Sirius_a,101.49660,-16.7449,J2000,CS_EQUATORIAL,EPOCH_J2000,NO_ATM_CORR);

  printf("equatorial\n");
  StellarCoordinatePrintDecimal(&Sirius_a);
  StellarCoordinatePrintEq(&Sirius_a);

  StellarCoordinate *Sirius_a_horiz;
  Sirius_a_horiz = StellarCoordinateCreate();

  printf("equatorial -> horiz\n");
  StellarCoordinateEqToHoriz(&Sirius_a, d_LAST, tLat, Sirius_a_horiz);
  StellarCoordinatePrintDecimal(Sirius_a_horiz);
  StellarCoordinatePrintHoriz(Sirius_a_horiz);

  StellarCoordinate *Sirius_a_hadec;
  Sirius_a_hadec = StellarCoordinateCreate();

  printf("equatorial -> hadec\n");
  StellarCoordinateEqToHaDec(&Sirius_a, d_LAST, Sirius_a_hadec);
  StellarCoordinatePrintDecimal(Sirius_a_hadec);
  StellarCoordinatePrintHaDec(Sirius_a_hadec);

  printf("horiz -> hadec\n");
  StellarCoordinateEqToHaDec(Sirius_a_horiz, tLat, Sirius_a_hadec);
  StellarCoordinatePrintDecimal(Sirius_a_hadec);
  StellarCoordinatePrintHaDec(Sirius_a_hadec);

  StellarCoordinate *Sirius_a_horiz_corr;
  Sirius_a_horiz_corr = StellarCoordinateCreate();

  printf("eq -> horiz with correction\n");
  StellarCoordinateEqToHorizWithCorrection(&Sirius_a, d_LAST, tLat, Sirius_a_horiz_corr);
  StellarCoordinatePrintDecimal(Sirius_a_horiz_corr);
  StellarCoordinatePrintHoriz(Sirius_a_horiz_corr);

  StellarCoordinate *Sirius_a_hadec_corr;
  Sirius_a_hadec_corr = StellarCoordinateCreate();

  printf("eq -> hadec with correction\n");
  StellarCoordinateEqToHaDecWithCorrection(&Sirius_a, d_LAST, tLat, Sirius_a_hadec_corr);
  StellarCoordinatePrintDecimal(Sirius_a_hadec_corr);
  StellarCoordinatePrintHaDec(Sirius_a_hadec_corr);

  printf("-------------------\n");
  StellarCoordinateDestroy(Sirius_a_horiz);
  StellarCoordinateDestroy(Sirius_a_hadec);
  StellarCoordinateDestroy(Sirius_a_horiz_corr);
  StellarCoordinateDestroy(Sirius_a_hadec_corr);

  return 0;
}

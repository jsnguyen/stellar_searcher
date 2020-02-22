#include <stdio.h>
#include <stdlib.h>
#include "stellar_searcher/constellation.h"
#include "stellar_searcher/interpolate.h"
#include "stellar_searcher/stellarCoordinate.h"

// Short example for using the epoch conversion from J2000 to JNow

int main(){

  StellarCoordinate sc,out;

  StellarCoordinateInit(&sc,
                        DecimalHoursToDecimalDegrees(HMSToDecimalHours(11,3,43.42)),
                        DMSToDecimalDegrees(61,45,6.3),
                        J2000,
                        CS_EQUATORIAL,
                        EPOCH_J2000,
                        NO_ATM_CORR);

  StellarCoordinateInit(&out,
                        0,
                        0,
                        J2000,
                        CS_EQUATORIAL,
                        EPOCH_J2000,
                        NO_ATM_CORR);

  printf("J2000.000:         ");
  StellarCoordinatePrintEq(&sc);
  StellarCoordinateJ2000ToJNow(&sc,&out);
  printf("J%.3f: ",out.epoch_yr);
  StellarCoordinatePrintEq(&out);
}

#include <stdio.h>
#include <stdlib.h>
#include "stellar_searcher/constellation.h"
#include "stellar_searcher/interpolate.h"
#include "stellar_searcher/stellarCoordinate.h"

// Example for loading and interpolating the Big Dipper constellation natively with classes

int main(){
  Constellation c;
  ConstellationInit(&c,"Big Dipper",NULL,0);

  StellarCoordinate AUMa,BUMa,GUMa,DUMa,EUMa,ZUMa,EtUMa;

  StellarCoordinateInit(&AUMa,
                        DecimalHoursToDecimalDegrees(HMSToDecimalHours(11,3,43.67152)),
                        DMSToDecimalDegrees(61,45,3.7249),
                        J2000,
                        CS_EQUATORIAL,
                        EPOCH_J2000,
                        NO_ATM_CORR);

  StellarCoordinateInit(&BUMa,
                        DecimalHoursToDecimalDegrees(HMSToDecimalHours(11,1,50.47564)),
                        DMSToDecimalDegrees(56,22,56.7339),
                        J2000,
                        CS_EQUATORIAL,
                        EPOCH_J2000,
                        NO_ATM_CORR);

  StellarCoordinateInit(&GUMa,
                        DecimalHoursToDecimalDegrees(HMSToDecimalHours(11,53,49.84732)),
                        DMSToDecimalDegrees(53,41,41.1350),
                        J2000,
                        CS_EQUATORIAL,
                        EPOCH_J2000,
                        NO_ATM_CORR);

  StellarCoordinateInit(&DUMa,
                        DecimalHoursToDecimalDegrees(HMSToDecimalHours(12,15,25.56063)),
                        DMSToDecimalDegrees(57,1,57.4156),
                        J2000,
                        CS_EQUATORIAL,
                        EPOCH_J2000,
                        NO_ATM_CORR);

  StellarCoordinateInit(&EUMa,
                        DecimalHoursToDecimalDegrees(HMSToDecimalHours(12,54,1.74959)),
                        DMSToDecimalDegrees(55,57,37.3627),
                        J2000,
                        CS_EQUATORIAL,
                        EPOCH_J2000,
                        NO_ATM_CORR);

  StellarCoordinateInit(&ZUMa,
                        DecimalHoursToDecimalDegrees(HMSToDecimalHours(13,23,55.54048)),
                        DMSToDecimalDegrees(54,55,31.2671),
                        J2000,
                        CS_EQUATORIAL,
                        EPOCH_J2000,
                        NO_ATM_CORR);

  StellarCoordinateInit(&EtUMa,
                        DecimalHoursToDecimalDegrees(HMSToDecimalHours(13,47,32.43776)),
                        DMSToDecimalDegrees(49,18,47.7602),
                        J2000,
                        CS_EQUATORIAL,
                        EPOCH_J2000,
                        NO_ATM_CORR);

  ConstellationAdd(&c,&AUMa);
  ConstellationAdd(&c,&BUMa);
  ConstellationAdd(&c,&GUMa);
  ConstellationAdd(&c,&DUMa);
  ConstellationAdd(&c,&EUMa);
  ConstellationAdd(&c,&ZUMa);
  ConstellationAdd(&c,&EtUMa);
  //ConstellationPrint(&c);

  int nPoints = 5;
  StellarCoordinate points[nPoints];

  // Interpolated points between two stars
  SphericalLinearInterpolation(&ZUMa,&EtUMa,points,nPoints);

  printf("Printing interpolated points between ZUMa and EtMa\n");
  for(int i=0;i<nPoints;i++){
    StellarCoordinatePrintDecimal(&points[i]);
  }

  int totalPointsConstellation = (nPoints+1)*(c.len-1)+1; // +1 for extra point at the end to hold the endpoint
  StellarCoordinate pointsB[totalPointsConstellation];

  // Interpolated points for a whole constellation
  InterpolateConstellation(&c,pointsB,nPoints);

  printf("Printing interpolated points for whole constellation\n");
  for(int i=0;i<totalPointsConstellation;i++){
    StellarCoordinatePrintDecimal(&pointsB[i]);
    //printf("%f,%f\n",pointsB[i].lon,pointsB[i].lat);
  }

  ConstellationDestroyStars(&c);

  return 0;
}

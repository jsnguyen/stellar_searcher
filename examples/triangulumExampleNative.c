#include <stdio.h>
#include <stdlib.h>
#include "stellar_searcher/constellation.h"
#include "stellar_searcher/interpolate.h"
#include "stellar_searcher/stellarCoordinate.h"

// Example for loading and interpolating the Triangulum constellation natively with classes

int main(){
  Constellation c;
  ConstellationInit(&c,"Triangulum",NULL,0); // Initialize

  DateTime J2000;
  SetDateTime(&J2000, 2000,1,1,12,0,0);

  int nStars = 6;
  StellarCoordinate triangulumStars[nStars]; // Array for holding the stars

  // Initialize all of the stars by hand
  StellarCoordinateInit(&triangulumStars[0],
                        HMSToRad('+',1,53,4.90),
                        DMSToRad('+',29,34,45.8),
                        J2000,
                        CS_EQUATORIAL,
                        EPOCH_J2000);

  StellarCoordinateInit(&triangulumStars[1],
                        HMSToRad('+',2,2,57.97),
                        DMSToRad('+',33,17,2.9),
                        J2000,
                        CS_EQUATORIAL,
                        EPOCH_J2000);

  StellarCoordinateInit(&triangulumStars[2],
                        HMSToRad('+',2,9,32.52),
                        DMSToRad('+',34,59,14.6),
                        J2000,
                        CS_EQUATORIAL,
                        EPOCH_J2000);

  StellarCoordinateInit(&triangulumStars[3],
                        HMSToRad('+',2,17,2.42),
                        DMSToRad('+',34,13,29.4),
                        J2000,
                        CS_EQUATORIAL,
                        EPOCH_J2000);

  StellarCoordinateInit(&triangulumStars[4],
                        HMSToRad('+',2,17,18.84),
                        DMSToRad('+',33,50,50.4),
                        J2000,
                        CS_EQUATORIAL,
                        EPOCH_J2000);

  StellarCoordinateInit(&triangulumStars[5],
                        HMSToRad('+',2,12,22.32),
                        DMSToRad('+',30,18,11.6),
                        J2000,
                        CS_EQUATORIAL,
                        EPOCH_J2000);

  // Add the stars to the constellation
  for(int i=0;i<nStars;i++){
    ConstellationAdd(&c,&triangulumStars[i]);
  }

  int nPointsBetweenStars = 4;
  int totalPointsConstellation = (nPointsBetweenStars+1)*(c.len-1)+1; // +1 for extra point at the end to hold the endpoint
  StellarCoordinate points[totalPointsConstellation];
  InterpolateConstellation(&c,points,nPointsBetweenStars);

  printf("Printing interpolated points for whole constellation\n");
  for(int i=0;i<totalPointsConstellation;i++){
    StellarCoordinatePrintDecimal(&points[i],DEG);
  }

  ConstellationDestroyStars(&c);

  return 0;
}

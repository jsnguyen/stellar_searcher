#include <stdio.h>
#include <stdlib.h>
#include "stellar_searcher/constellation.h"
#include "stellar_searcher/interpolate.h"
#include "stellar_searcher/stellarCoordinate.h"
#include "stellar_searcher/parser.h"
#include "jsmn.h"

// Example for loading and interpolating the Big Dipper constellation using a .json file

int main(){
  Constellation c;
  ConstellationInit(&c,"",NULL,0);
  
  // Read in constellation
  jsonParse(&c,"ursa_major.json");
  ConstellationPrint(&c);

  int nPointsBetweenStars = 5;
  int totalPointsConstellation = (nPointsBetweenStars+1)*(c.len-1)+1; // +1 for extra point at the end to hold endpoint

  StellarCoordinate points[totalPointsConstellation];

  // Interpolates the whole constellation and puts values in points array
  InterpolateConstellation(&c,points,nPointsBetweenStars);

  printf("Printing interpolated points for whole constellation\n");
  for(int i=0;i<totalPointsConstellation;i++){
    StellarCoordinatePrintDecimal(&points[i],DEG);
  }

  ConstellationDestroyStars(&c);
  
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "stellar_searcher/constellation.h"
#include "stellar_searcher/interpolate.h"
#include "stellar_searcher/stellarCoordinate.h"
#include "stellar_searcher/parser.h"

// Example for loading and interpolating the Triangulum constellation using a .json file

int main(){

  Constellation c;
  ConstellationInit(&c,"Triangulum",NULL,0, NULL, 0); // Initialize

  // Loading the .json file
  jsonParse(&c,"triangulum.json");

  int nPointsBetweenStars = 4;
  int totalPointsConstellation = (nPointsBetweenStars+1)*(c.len_s-1)+1; // +1 for extra point at the end to hold the endpoint
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

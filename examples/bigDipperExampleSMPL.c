#include "stellar_searcher/parser.h"

int main(){
  Constellation c;
  ConstellationInit(&c,"",NULL,0,NULL,0);

  ParseSMPL("../data/constellations/ursa_major.smpl",&c);

  int nPointsBetweenStars = 5;
  int totalPointsConstellation = (nPointsBetweenStars+1)*(c.len_s-1); // CHECK THIS NUMBER
  StellarCoordinate points[totalPointsConstellation];

  // Interpolates the whole constellation and puts values in points array
  InterpolateConstellation(&c,points,nPointsBetweenStars);

  printf("Printing interpolated points for whole constellation\n");
  for(int i=0;i<totalPointsConstellation;i++){
    StellarCoordinatePrintDecimal(&points[i],DEG);
  }

  ConstellationDestroyStars(&c);
  ConstellationDestroyPointingOrder(&c);

  return 0;
}

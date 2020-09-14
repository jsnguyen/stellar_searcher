#include "stellar_searcher/parser.h"

int main(){
  
  // initialize and read in constellation
  Constellation c;
  ConstellationInit(&c,"",NULL,0,NULL,0);
  ParseSMPL("../data/constellations/ursa_major.smpl",&c);

  // interpolate between points
  int nPointsBetweenStars = 5;
  int totalPointsConstellation = (nPointsBetweenStars+1)*(c.len_s-1); // CHECK THIS NUMBER
  StellarCoordinate points[totalPointsConstellation];
  InterpolateConstellation(&c,points,nPointsBetweenStars);

  // get the current time
  DateTime now;
  GetCurrentDateTime(&now);

  // geographic longitude and latitude
  double g_lon = 0;
  double g_lat = 0;

  // loop through all interpolated points
  StellarCoordinate newPoint;
  for(int i=0;i<totalPointsConstellation;i++){
    StellarCoordinateEqToHoriz(&points[i], now, g_lon, g_lat, &newPoint);
    points[i] = newPoint;
    StellarCoordinatePrintDecimal(&points[i],DEG); // print horizontal coordinates in degrees from north and the horizontal
  }

  // cleanup
  ConstellationDestroyStars(&c);
  ConstellationDestroyPointingOrder(&c);

  return 0;
}

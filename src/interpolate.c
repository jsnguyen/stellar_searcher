#include "stellar_searcher/interpolate.h"

// Returns decimal degrees
double GetGreatCircleDistance(StellarCoordinate *a, StellarCoordinate *b){
  ThreeVector tva, tvb;
  MakeCoordinateToVector(a->lon,a->lat, &tva);
  MakeCoordinateToVector(a->lon,a->lat, &tvb);
  return 180.0/PI * acos(ThreeVectorDotProduct(&tva, &tvb));
}

// Makes points from a to b including ONLY a and NOT b
// The number nPoints includes the origin point
void SphericalLinearInterpolation(StellarCoordinate *a, StellarCoordinate *b, StellarCoordinate* points, int nPoints){
  ThreeVector tva, tvb;
  MakeCoordinateToVector(a->lon,a->lat, &tva);
  MakeCoordinateToVector(b->lon,b->lat, &tvb);
  double dp = ThreeVectorDotProduct(&tva,&tvb);
  ThreeVector tvc;
  double result[2];

  if(dp > 0.9995){
    printf("ERROR: Points too close to spherically interpolate!\n");
    printf("       Linearly interpolating instead!\n");
    for(int i=0;i<nPoints;i++){
      double n = 1-(double) i / (double) (nPoints);
      tvc.i = (1-n)*tvb.i+n*tva.i;
      tvc.j = (1-n)*tvb.j+n*tva.j;
      tvc.k = (1-n)*tvb.k+n*tva.k;

      MakeVectorToCoordinate(&tvc,result);
      points[i].cs=CS_EQUATORIAL;
      points[i].lon=result[0];
      points[i].lat=result[1];
    }
    return;
  }

  double omega = acos(dp);
  for(int i=0;i<nPoints;i++){
    double n = 1-(double) i / (double) (nPoints);
    tvc.i = sin((1-n)*omega)/sin(omega)*tvb.i + sin(n*omega)/sin(omega)*tva.i;
    tvc.j = sin((1-n)*omega)/sin(omega)*tvb.j + sin(n*omega)/sin(omega)*tva.j;
    tvc.k = sin((1-n)*omega)/sin(omega)*tvb.k + sin(n*omega)/sin(omega)*tva.k;

    MakeVectorToCoordinate(&tvc,result);
    points[i].cs=CS_EQUATORIAL;

    // make angles positive
    while(result[0] < 0){
      result[0]+=360.0;
    }
    while(result[1] < 0){
      result[1]+=360.0;
    }

    points[i].lon=result[0];
    points[i].lat=result[1];
  }
}

// Note that points should have ((nPointsBetweenStars+1)*(c->len)+1)*sizeof(StellarCoordinate) malloc'd memory
// Need one extra point at the end for the final point
void InterpolateConstellation(Constellation *c, StellarCoordinate* points, int nPointsBetweenStars){

  // Actual number of points is the beginning point + the interpolated points to the next star
  // But NOT including the next star itself!
  int actualNPoints=nPointsBetweenStars+1;

  // This means that at the end of the sequence the last star 
  // won't be accounted for, so we copy the last star after
  // the end of the for loop.

  StellarCoordinate tempPoints[actualNPoints];

  for(int i=0;i<c->len-1;i++){
    //printf("Interpolating between %f,%f and %f,%f\n",c->stars[i]->lon,c->stars[i]->lat,c->stars[i+1]->lon,c->stars[i+1]->lat);
    SphericalLinearInterpolation(&c->stars[i],&c->stars[i+1],tempPoints,actualNPoints);

    for(int j=0;j<actualNPoints;j++){
      int n = i*actualNPoints+j;
      StellarCoordinateCopy(&points[n],&tempPoints[j]);
    }
  }

  // tack on the last coordinate at the end
  StellarCoordinateCopy(&points[actualNPoints*(c->len-1)+1-1],&c->stars[c->len-1]);
}

#include "stellar_searcher/celestialTime.h"
#include "stellar_searcher/matrix.h"
#include "stellar_searcher/stellarCoordinate.h"
#include <sofa.h>

// Comparison between my precession/nutation matricies and SOFA's official matricies
// Concluded that mine are good enough
// Also note that my matricies uses an approximation somewhere so they aren't exactly the same

int main(){
  double prec[3][3];
  double nut[3][3];
  double JD;
  JD = GetCurrentJD();
  printf("JD: %f\n", JD);

  iauPmat06(JD,0,prec);
  iauNum00a(JD,0,nut);

  Matrix precession;
  MatrixSet(&precession, prec);
  MatrixPrint(&precession);

  Matrix nutation;
  MatrixSet(&nutation, nut);
  MatrixPrint(&nutation);

  StellarCoordinate sc,out;

  StellarCoordinateInit(&sc,
                        DecimalHoursToDecimalDegrees(HMSToDecimalHours(11,3,43.42)),
                        DMSToDecimalDegrees(61,45,6.3),
                        (int) CS_EQUATORIAL);

  StellarCoordinateInit(&out,
                        0,
                        0,
                        (int) CS_EQUATORIAL);
  //printf("J2000:         ");
  //StellarCoordinatePrintEq(&sc);
  StellarCoordinateJ2000ToJNow(&sc,&out); // enable MatrixPrint functions here to see the precession/nutation matricies
  //printf("Current Epoch: ");
  //StellarCoordinatePrintEq(&out);


  return 0;
}

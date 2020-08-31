#include "stellar_searcher/celestialTime.h"

/*
Refer to:
http://aa.usno.navy.mil/faq/docs/GAST.php
for the various equations used to calculate JD, GMST, GAST, LMST, LAST.
For precession/nutation calculations:
https://www.cv.nrao.edu/~rfisher/Ephemerides/earth_rot.html#nut
Also see Explanation of the Astronomical Almanac for a lot of this stuff...
*/

// Julian Day Number
int GetJDN(DateTime dt){

  int i;
  double JDN0, JDN;
  i = iauCal2jd( dt.Y, dt.M, dt.D, &JDN0, &JDN);
  return JDN + JDN0;

}


// Julian Day
// This number is not as accurate as two separate numbers...
double GetJD(DateTime dt){
  return GetJDN(dt) + GetFractionalJD(dt);
}

double GetFractionalJD(DateTime dt){
  return 0.5 + dt.h/24.0 + dt.m/(24.0*60.0) + dt.s/(24.0*60.0*60.0);
}

double GetJulianYear(DateTime dt){
  DateTime JD0;
  SetDateTime(&JD0, 2000, 1, 1, 12, 0, 0);
  return 2000.0+(GetJD(dt)-GetJD(JD0))/365.25;
}

void GetSplitUTC(DateTime dt, double *UTC1, double *UTC2){
  // Get UTC split into two dates... UTC1+UTC2 = UTC
  iauDtf2d("UTC", dt.Y, dt.M, dt.D, dt.h, dt.m, dt.s, UTC1, UTC2);
}

// Greenwich Mean Sidereal Time in decimal hours
double GetGMST(DateTime dt){

  // Get UTC split into two dates... UTC1+UTC2 = UTC
  double UTC1,UTC2;
  GetSplitUTC(dt, &UTC1, &UTC2);

  // Get UT1 time split into two dates... UT11 + UT12 = UT1
  // Requires a split UTC time as well to calculate UT1
  double UT11, UT12;
  iauUtcut1(UTC1, UTC2, DUT1, &UT11, &UT12);

  double TT1, TT2;
  iauUt1tt(UT11, UT12, DT, &TT1, &TT2);

  double GMST = iauGmst06(UT11, UT12, TT1, TT2);

  return GMST;
}

// Greenwich Apparent Sidereal Time in decimal hours
// Corrected for nutation (more accurate that GMST)
// Seems to be about ~3 seconds off?
double GetGAST(DateTime dt){

  // Get UTC split into two dates... UTC1+UTC2 = UTC
  double UTC1,UTC2;
  iauDtf2d("UTC", dt.Y, dt.M, dt.D, dt.h, dt.m, dt.s, &UTC1, &UTC2);

  // Get UT1 time split into two dates... UT11 + UT12 = UT1
  // Requires a split UTC time as well to calculate UT1
  double UT11, UT12;
  iauUtcut1(UTC1, UTC2, DUT1, &UT11, &UT12);

  double TT1, TT2;
  iauUt1tt(UT11, UT12, DT, &TT1, &TT2);

  double GAST = iauGst06a(UT11, UT12, TT1, TT2);

  return GAST;
}

// Local Mean Sidereal Time in decimal hours
double GetLMST(DateTime dt, double lon){

  double LMST = GetGMST(dt) + ((lon/360.0) * 24.0);

  if (LMST<0.0){
    LMST = LMST+24.0;
  }

  return LMST;
}

// Local Apparent Sidereal Time in decimal hours
// Corrected for nutation (more accurate that LMST)
double GetLAST(DateTime dt, double lon){

  double LAST = GetGAST(dt) + ((lon/360.0) * 24.0);

  if (LAST<0.0){
    LAST = LAST+24.0;
  }

  return LAST;
}

// degrees minutes seconds to radians
double DMSToRad(char sign, int d, int m, double s){
  double rad;
  iauAf2a(sign, d, m, s, &rad);
  return rad;
}

// hours minutes seconds to radians
double HMSToRad(char sign, int h, int m, double s){
  double rad;
  iauTf2a(sign, h, m, s, &rad);
  return rad;
}

void PrintDMS(double rad){
  char sign;
  int dmsf[4];
  iauA2af(9, rad, &sign, dmsf);
  printf("%c%id %im %i.%is\n",sign,dmsf[0],dmsf[1],dmsf[2],dmsf[3]);
}

void PrintHMS(double rad){
  char sign;
  int hmsf[4];
  iauA2tf(9, rad, &sign, hmsf);
  printf("%c%ih %im %i.%is\n",sign,hmsf[0],hmsf[1],hmsf[2],hmsf[3]);
}

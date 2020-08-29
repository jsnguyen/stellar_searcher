#include "stellar_searcher/celestialTime.h"
#include "sofa.h"

/*
Refer to:
http://aa.usno.navy.mil/faq/docs/GAST.php
for the various equations used to calculate JD, GMST, GAST, LMST, LAST.
For precession/nutation calculations:
https://www.cv.nrao.edu/~rfisher/Ephemerides/earth_rot.html#nut
*/

// Julian Day Number
int GetCurrentJDN(){

  time_t rawtime;
  time(&rawtime);

  struct tm * ptm;
  ptm = gmtime(&rawtime);

  int Y = ptm->tm_year+1900;
  int M = ptm->tm_mon+1;
  int D = ptm->tm_mday;

  int JDN = GetJDN(Y,M,D);

  return JDN;
}

// Julian Day Number
int GetJDN(int Y, int M, int D){

  int i;
  double JDN0, JDN;
  i = iauCal2jd( Y, M, D, &JDN0, &JDN);
  return JDN + JDN0;

}

double GetFractionalJD(int h, int m, int s){
  return 0.5 + h/24.0 + m/(24.0*60.0) + s/(24.0*60.0*60.0);
}

// Julian Day
double GetCurrentJD(){
  time_t rawtime;
  time(&rawtime);

  struct tm * ptm;
  ptm = gmtime(&rawtime);

  int h = ptm->tm_hour;
  int m = ptm->tm_min;
  int s = ptm->tm_sec;

  double JD = GetCurrentJDN() + GetFractionalJD(h,m,s);

  return JD;
}

// Julian Day
double GetJD(int h, int m, double s, int Y, int M, int D){
  return GetJDN(Y,M,D) + GetFractionalJD(h,m,s);
}

double GetJulianYear(int h, int m, double s, int Y, int M, int D){
  return 2000.0+(GetJD(h,m,s,Y,M,D)-GetJD(12,0,0,2000,1,1))/365.25;
}

double GetCurrentJulianYear(){
  return 2000.0+(GetCurrentJD()-GetJD(12,0,0,2000,1,1))/365.25;
}

// Greenwich Mean Time in decimal hours
// Seems to be about ~0.5 seconds off?
double GetGMT(){
  time_t rawtime;
  time(&rawtime);

  struct tm * ptm;
  ptm = gmtime(&rawtime);

  double decimalHours = HMSToDecimalHours((double) ptm->tm_hour,(double) ptm->tm_min, (double) ptm->tm_sec);

  return decimalHours;
}

// Greenwich Mean Sidereal Time in decimal hours
double GetGMST(int Y, int M, int D, int h, int m, int s){

  // Get UTC split into two dates... UTC1+UTC2 = UTC
  double UTC1,UTC2;
  iauDtf2d("UTC", Y, M, D, h, m, s, &UTC1, &UTC2);

  // See: https://datacenter.iers.org/eop.php
  // This is true from 02 May 2019, 0h UTC, onwards
  double DUT1 = -0.2;

  // !!! NOTICE, NEED RIGOROUS WAY OF FINDING DUT1 FOR DATES PREVIOUS TO THIS AS WELL !!!
  // Get UT1 time split into two dates... UT11 + UT12 = UT1
  // Requires a split UTC time as well to calculate UT1
  double UT11, UT12;
  iauUtcut1(UTC1, UTC2, DUT1, &UT11, &UT12);

  // !!! NOTICE, NEED RIGOROUS WAY OF FINDING DT FOR DATES PREVIOUS TO THIS AS WELL !!!
  // USNO website for DT reference seems to be down for a bit...
  double DT = 69.36; // Good on 2020-01-01... but this number changes over time unpredictably!
  double TT1, TT2;
  iauUt1tt(UT11, UT12, DT, &TT1, &TT2);

  double GMST = iauGmst06(UT11, UT12, TT1, TT2);

  return GMST*180.0/PI;
}

double GetCurrentGMST(){

  time_t rawtime;
  time(&rawtime);

  struct tm * ptm;
  ptm = gmtime(&rawtime);

  int Y = ptm->tm_year+1900;
  int M = ptm->tm_mon+1;
  int D = ptm->tm_mday;
  int h = ptm->tm_hour;
  int m = ptm->tm_min;
  int s = ptm->tm_sec;

  return GetGMST(Y, M, D, h, m, s);

}

// Greenwich Apparent Sidereal Time in decimal hours
// Corrected for nutation (more accurate that GMST)
// Seems to be about ~3 seconds off?
double GetGAST(double JD){

  double D = JD - 2451545.0;
  double o = 125.04 - 0.052954*D;
  double l = 280.47 + 0.98565*D;
  double e = 23.4393 - 0.0000004*D;
  double p =(-0.000319*sin(o*(PI/180.0))) - (0.000024*sin(2*l*(PI/180.0))) ;

  // Equation of the Equinoxes
  double eqeq = p*cos(e*(PI/180.0));
  double GAST = 0;//GetGMST(JD)+eqeq;

  GAST = fmod(GAST,24.0);

  return GAST;
}

// Local Mean Sidereal Time in decimal hours
double GetLMST(double JD, double longitude){

  double LMST = 0;//GetGMST(JD)+((longitude/360.0) * 24.0);

  if (LMST<0.0){
    LMST = LMST+24.0;
  }

  return LMST;
}

// Local Apparent Sidereal Time in decimal hours
// Corrected for nutation (more accurate that LMST)
double GetLAST(double JD, double longitude){

  double LAST = GetGAST(JD)+((longitude/360.0) * 24.0);

  if (LAST<0.0){
    LAST = LAST+24.0;
  }

  return LAST;
}

// Degrees Minutes Seconds
double DMSToDecimalDegrees(double d, double m, double s){
  double a;

  double md = m/(60.0);
  double sd = s/(60.0*60.0);

  if(d < 0){
    md = md*-1;
    sd = sd*-1;
  }

  a = d+md+sd;

  return a;
}

// Hours Minutes Seconds
double HMSToDecimalHours(double h, double m , double s){
  double a;

  double md = m/(60.0);
  double sd = s/(60.0*60.0);

  if(h < 0){
    md = md*-1;
    sd = sd*-1;
  }
  
  a = h+md+sd;

  return a;
}

// decimal degrees to Degrees Minutes Seconds
void PrintDecimalDegreesToDMS(double a){

  int d = (int) a % 360;

  double aa = fabs(a);
  int m = (int) ((aa-(int) aa) * 60.0);
  double s = ((aa-(int) aa)-(m/60.0)) * 60.0*60.0;

  printf("%dd %d\' %f\"\n",d,m,s);
}

// decimal hours to h:m:s
void PrintDecimalHoursToHMS(double a){

  int h = (int) a % 24;

  double aa = fabs(a);
  double m0 = (aa - (int) aa)*60;
  int m = (int) m0;

  double s = (m0 - (int) m0)*60;

  printf("%ih %im %fs\n",h,m,s);
}

// decimal degrees to Degrees Minutes Seconds
void DecimalDegreesToDMSStr(double a, char *out){

  int d = (int) a;

  double aa = fabs(a);
  int m = (int) ((aa-(int) aa) * 60.0);
  double s = ((aa-(int) aa)-(m/60.0)) * 60.0*60.0;

  sprintf(out,"%dd %d\' %f\"",d,m,s);
}

void DecimalHoursToHMSStr(double a, char *out){

  int h = (int) a % 24;

  double aa = fabs(a);
  double m0 = (aa - (int) aa)*60;
  int m = (int) m0;

  double s = (m0 - (int) m0)*60;

  sprintf(out,"%ih %im %fs",h,m,s);
}

double DecimalDegreesToDecimalHours(double a){
  double decimalHours;
  decimalHours = a/360.0 * 24.0;
  return decimalHours;
}

double DecimalHoursToDecimalDegrees(double a){
  double decimalDegrees;
  decimalDegrees = a/24.0 * 360.0;
  return decimalDegrees;
}

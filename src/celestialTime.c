#include "stellar_searcher/celestialTime.h"

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

  int JDN = (1461 * (Y + 4800 + (M - 14)/12))/4 +(367 * (M - 2 - 12 * ((M - 14)/12)))/12 - (3 * ((Y + 4900 + (M - 14)/12)/100))/4 + D - 32075;

  return JDN;
}

// Julian Day Number
int GetJDN(int Y, int M, int D){

  int JDN = (1461 * (Y + 4800 + (M - 14)/12))/4 +(367 * (M - 2 - 12 * ((M - 14)/12)))/12 - (3 * ((Y + 4900 + (M - 14)/12)/100))/4 + D - 32075;

  return JDN;
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

  double JD = GetCurrentJDN() + (h-12.0)/24.0 + m/(24.0*60.0) + s/(24.0*60.0*60.0);

  return JD;
}

// Julian Day
double GetJD(int h, int m, double s, int Y, int M, int D){
  double JD = GetJDN(Y,M,D) + (h-12.0)/24.0 + m/(24.0*60.0) + s/(24.0*60.0*60.0);
  return JD;
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
// Seems to be about ~3 seconds off?
double GetGMST(double JD){

  double D = JD - 2451545.0;

  //double GMST = 6.697374558 + 0.06570982441908*D0 + 1.00273790935*H ; // Other formulation
  double GMST = 18.697374558 + 24.06570982441908*D;

  GMST = fmod(GMST,24.0);

  return GMST;
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
  double GAST = GetGMST(JD)+eqeq;

  GAST = fmod(GAST,24.0);

  return GAST;
}

// Local Mean Sidereal Time in decimal hours
double GetLMST(double JD, double longitude){

  double LMST = GetGMST(JD)+((longitude/360.0) * 24.0);

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

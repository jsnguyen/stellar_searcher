#include "stellar_searcher/stellarCoordinate.h"

#define PI 3.14159265

/*
 * EVERYTHING USES DECIMAL DEGREES FOR CONSISTENCY
 */

StellarCoordinate* StellarCoordinateCreate(){
  StellarCoordinate *sc=malloc(sizeof(StellarCoordinate));
  return sc;
}

void StellarCoordinateInit(StellarCoordinate *sc, double lon, double lat, double epoch_yr, CS_TYPE type, EPOCH_TYPE epoch, ATM_CORR_TYPE atm_corr){
  sc->lon=lon;
  sc->lat=lat;
  sc->epoch_yr=epoch_yr;

  sc->cs=type;
  sc->epoch=epoch;
  sc->atm_corr=atm_corr;
}

void StellarCoordinateDestroy(StellarCoordinate *sc){
  free(sc);
}

// Copies b into a
void StellarCoordinateCopy(StellarCoordinate *a, StellarCoordinate *b){
  a->lon = b->lon;
  a->lat = b->lat;
  a->epoch_yr = b->epoch_yr;

  a->cs = b->cs;
  a->epoch = b->epoch;
  a->atm_corr= b->atm_corr;
}

double StellarCoordinateGetLon(StellarCoordinate *sc){
  return sc->lon;
}

double StellarCoordinateGetLat(StellarCoordinate *sc){
  return sc->lat;
}

double StellarCoordinateGetEpochYear(StellarCoordinate *sc){
  return sc->epoch_yr;
}

CS_TYPE StellarCoordinateGetCoordinateSystemType(StellarCoordinate *sc){
  return sc->cs;
}

EPOCH_TYPE StellarCoordinateGetEpochType(StellarCoordinate *sc){
  return sc->epoch;
}

ATM_CORR_TYPE StellarCoordinateGetAtmosphericCorrectionType(StellarCoordinate *sc){
  return sc->atm_corr;
}

void StellarCoordinateSet(StellarCoordinate *sc, double lon, double lat, double epoch_yr, CS_TYPE type, EPOCH_TYPE epoch, ATM_CORR_TYPE atm_corr){
  sc->lon=lon;
  sc->lat=lat;
  sc->epoch_yr=epoch_yr;

  sc->cs=type;
  sc->epoch=epoch;
  sc->atm_corr=atm_corr;
}

void StellarCoordinateSetLon(StellarCoordinate *sc, double lon){
  sc->lon = lon;
}

void StellarCoordinateSetLat(StellarCoordinate *sc, double lat){
  sc->lat = lat;
}

void StellarCoordinateSetEpochYear(StellarCoordinate *sc, double epoch_yr){
  sc->epoch_yr = epoch_yr;
}

void StellarCoordinateSetCoordinateSystemType(StellarCoordinate *sc, CS_TYPE type){
  sc->cs = type;
}

void StellarCoordinateSetEpochType(StellarCoordinate *sc, EPOCH_TYPE epoch){
  sc->epoch = epoch;
}

void StellarCoordinateSetAtmosphericCorrectionType(StellarCoordinate *sc, ATM_CORR_TYPE atm_corr){
  sc->atm_corr= atm_corr;
}

/*
Equatorial to Horizontal
Uses terrestrial latitude
*/
void StellarCoordinateEqToHorizSOFA(StellarCoordinate *sc, double lst, double lat, StellarCoordinate *out){
  sc.lon
  sc.lat

  double pm_ra = 0;
  double pm_dec = 0;
  double parallax = 0;
  double radial_velocity = 0;

  GetSplitUTC

  iauAtco13(sc.lon, sc.lat,
            pm_ra, pm_dec, parallax, radial_velocity,

            double utc1, double utc2, double dut1,
            double elong, double phi, double hm, double xp, double yp,
            double phpa, double tc, double rh, double wl,
            double *aob, double *zob, double *hob,
            double *dob, double *rob, double *eo)

void StellarCoordinateEqToHoriz(StellarCoordinate *sc, double lst, double lat, StellarCoordinate *out){
  sc.lon
  sc.lat

  double pm_ra = 0;
  double pm_dec = 0;
  double parallax = 0;
  double radial_velocity = 0;

  iauAtco13(sc.lon, sc.lat,
            pm_ra, pm_dec, parallax, radial_velocity,

            double utc1, double utc2, double dut1,
            double elong, double phi, double hm, double xp, double yp,
            double phpa, double tc, double rh, double wl,
            double *aob, double *zob, double *hob,
            double *dob, double *rob, double *eo)

  Matrix eqToHoriz;
  MakeEqToHoriz(&eqToHoriz,lst,lat);

  ThreeVector tv;
  MakeCoordinateToVector(sc->lon,sc->lat,&tv);

  ThreeVector res;
  MatrixMultiplyThreeVector(&eqToHoriz,&tv,&res);

  double coord[2];
  MakeVectorToCoordinate(&res,coord);

  out->lon=coord[0];
  out->lat=coord[1];
  out->cs=CS_AZALT;

}

/*
Equatorial/Horizontal/Horizontal Corrected to HaDec
Note that if you use Horizontal Corrected you get HaDec Corrected
q can be LST or latitude
Careful here, needs to know before hand whether q is local sidereal time to latitude
Make sure that argument is correctly local sidereal time for equatorial or latitude for horizontal
Convention says that output should be in decimal hours BUT I use decimal degrees
*/
void StellarCoordinateEqToHaDec(StellarCoordinate *sc, double q, StellarCoordinate *out){

  Matrix toHaDec;

  ThreeVector tv;
  MakeCoordinateToVector(sc->lon,sc->lat,&tv);

  ThreeVector res;

  double coord[2];

  if(sc->cs == CS_EQUATORIAL){
    // uses local sidereal time
    MakeEqToHaDec(&toHaDec,q);
  }

  else if(sc->cs == CS_AZALT){
    // uses latitude
    MakeHorizToHaDec(&toHaDec,q);
  }

  MatrixMultiplyThreeVector(&toHaDec,&tv,&res);

  MakeVectorToCoordinate(&res,coord);
  while(coord[0]<0){
    coord[0]+=360.0;
  }

  out->lon=coord[0];
  out->lat=coord[1];
  out->cs=CS_HADEC;

}

// Equatorial to Azimuth/Altitude with Correction
void StellarCoordinateEqToHorizWithCorrection(StellarCoordinate *sc, double lst, double lat, StellarCoordinate *out){

  StellarCoordinateEqToHoriz(sc, lst, lat, out);

  out->atm_corr=ATM_CORR;
  out->lat += GetAtmosphericRefractionCorrection(out->lat);

}

// Equatorial to Hour Angle/Declination with Correction
void StellarCoordinateEqToHaDecWithCorrection(StellarCoordinate *sc, double lst, double lat, StellarCoordinate *out){

  StellarCoordinate temp;
  StellarCoordinateEqToHorizWithCorrection(sc, lst, lat, &temp);
  StellarCoordinateEqToHaDec(&temp, lat, out);

  out->cs=CS_HADEC;
  out->atm_corr=ATM_CORR;

}

void StellarCoordinateJ2000ToJNow(StellarCoordinate *in, StellarCoordinate *out){

  ThreeVector tv;
  MakeCoordinateToVector(in->lon,in->lat,&tv);

  Matrix precession;
  MakePrecessionMatrix(&precession,GetCurrentJD());
  // MatrixPrint(&precession);

  Matrix nutation;
  MakeNutationMatrix(&nutation,GetCurrentJD());
  // MatrixPrint(&nutation);

  ThreeVector resN;
  MatrixMultiplyThreeVector(&nutation,&tv,&resN);

  ThreeVector resP;
  MatrixMultiplyThreeVector(&precession,&resN,&resP);

  double coord[2];
  MakeVectorToCoordinate(&resP,coord);

  out->lon=coord[0];
  out->lat=coord[1];
  out->epoch_yr=GetCurrentJulianYear();
  out->epoch=EPOCH_JNOW;

}

void StellarCoordinatePrintDecimal(StellarCoordinate *sc){
  char modifier[9];

  if(sc->cs == CS_EQUATORIAL){
    strcpy(modifier,"(ra,dec)");
  }

  else if(sc->cs == CS_AZALT){
    strcpy(modifier,"(az,alt)");
  }

  else if(sc->cs == CS_HADEC){
    strcpy(modifier,"(ha,dec)");
  }

  printf("%d %s: (%f,%f)\n",sc->cs,modifier,sc->lon,sc->lat);

}

void StellarCoordinatePrintEq(StellarCoordinate *sc){
  char modifier[]="(ra,dec)";
  char outa[32],outb[32];
  DecimalHoursToHMSStr(DecimalDegreesToDecimalHours(sc->lon),outa);
  DecimalDegreesToDMSStr(sc->lat,outb);
  printf("%d %s: (%s,%s)\n",sc->cs,modifier,outa,outb);
}

void StellarCoordinatePrintHoriz(StellarCoordinate *sc){
  char modifier[]="(az,alt)";
  char outa[32],outb[32];
  DecimalDegreesToDMSStr(sc->lon,outa);
  DecimalDegreesToDMSStr(sc->lat,outb);
  printf("%d %s: (%s,%s)\n",sc->cs,modifier,outa,outb);
}

void StellarCoordinatePrintHaDec(StellarCoordinate *sc){
  char modifier[]="(ha,dec)";
  char outa[32],outb[32];
  DecimalHoursToHMSStr(DecimalDegreesToDecimalHours(sc->lon),outa);
  DecimalDegreesToDMSStr(sc->lat,outb);
  printf("%d %s: (%s,%s)\n",sc->cs,modifier,outa,outb);
}

/*
 * TRANSFORMATION MATRIX DEFINITIONS AND MISC FUNCTIONS BELOW
 */

void MakeCoordinateToVector(double lo, double la, ThreeVector *tv){

  double lon = lo*(PI/180.0);
  double lat = la*(PI/180.0);

  double i = cos(lat)*cos(lon);
  double j = cos(lat)*sin(lon);
  double k = sin(lat);

  ThreeVectorSet(tv,i,j,k);
}

void MakeStellarCoordinateToVector(StellarCoordinate *sc, ThreeVector *tv){

  double lon = sc->lon*(PI/180.0);
  double lat = sc->lat*(PI/180.0);

  double i = cos(lat)*cos(lon);
  double j = cos(lat)*sin(lon);
  double k = sin(lat);

  ThreeVectorSet(tv,i,j,k);
}

void MakeVectorToCoordinate(ThreeVector *tv, double a[2]){

  a[0]=(180.0/PI)*atan2(tv->j,tv->i);
  a[1]=(180.0/PI)*asin(tv->k);

}

// Equatorial To Hour Angle and Declination
// lst is in decimal degrees
void MakeEqToHaDec(Matrix *a, double lst){

  double l = lst*(PI/180.0);

  double setter[3][3];
  setter[0][0]=cos(l);
  setter[0][1]=sin(l);
  setter[0][2]=0;
  setter[1][0]=sin(l);
  setter[1][1]=-cos(l);
  setter[1][2]=0;
  setter[2][0]=0;
  setter[2][1]=0;
  setter[2][2]=1;

  MatrixSet(a,setter);
}

// Hour Angle and Declination to Horizontal
// Latitude is in decimal degrees
void MakeHaDecToHoriz(Matrix *a, double lat){

  double l = lat*(PI/180);

  double setter[3][3];
  setter[0][0]=-sin(l);
  setter[0][1]=0;
  setter[0][2]=cos(l);
  setter[1][0]=0;
  setter[1][1]=-1;
  setter[1][2]=0;
  setter[2][0]=cos(l);
  setter[2][1]=0;
  setter[2][2]=sin(l);

  MatrixSet(a,setter);
}

// Hour Angle and Declination to Horizontal
// Latitude is in decimal degrees
void MakeHorizToHaDec(Matrix *a, double lat){

  Matrix b;

  MakeHaDecToHoriz(&b,lat);
  MatrixGetInverse(&b,a);
}

// Equatorial to Galactic
void MakeEqToGal(Matrix *a){

  double setter[3][3];
  setter[0][0]= -0.054876;
  setter[0][1]= -0.873437;
  setter[0][2]= -0.483835;
  setter[1][0]=  0.494109;
  setter[1][1]= -0.444830;
  setter[1][2]=  0.746982;
  setter[2][0]= -0.867666;
  setter[2][1]= -0.198076;
  setter[2][2]=  0.455984;

  MatrixSet(a,setter);
}

void MakeHorizToEq(Matrix *a, double lst, double lat){
  Matrix b,c;

  MakeEqToHaDec(&b,lst);
  MakeHaDecToHoriz(&c,lat);

  MatrixMultiplyMatrix(&b,&c,a);
}

void MakeEqToHoriz(Matrix *a, double lst, double lat){
  Matrix b;

  MakeHorizToEq(&b,lst,lat);
  MatrixGetInverse(&b,a);
}

// See Explanatory Supplement to the Astronomical Almanac, 3rd Ed., p.216
void MakePrecessionMatrix(Matrix *a, double JD){
  double setter[3][3];

  int nSeries=6;
  // Units of numbers here are arcseconds per century
  double zeta_a_series[]  = { 2.650545, 2306.083227,  0.2988499,  0.01801828, -5.971e-6 , -3.173e-7};
  double z_a_series[]     = {-2.650545, 2306.077181,  1.0927348,  0.01826837, -2.8596e-5, -2.904e-7};
  double theta_a_series[] = {0        , 2004.191903, -0.4294934, -0.04182264, -7.089e-6 , -1.274e-7};

  // Julian centuries SINCE J2000
  double julianCenturies=(JD-2451545.0)/(365.25*100.0);

  double zeta_a=0, z_a=0, theta_a=0;
  for(int i=0;i<nSeries;i++){
    zeta_a  += zeta_a_series[i]  * pow(julianCenturies,i);
    z_a     += z_a_series[i]     * pow(julianCenturies,i);
    theta_a += theta_a_series[i] * pow(julianCenturies,i);
  }

  double arcsecondsToDegrees=1.0/(60.0*60.0);
  double degToRad = PI/180.0;
  z_a     *= arcsecondsToDegrees*degToRad;
  theta_a *= arcsecondsToDegrees*degToRad;
  zeta_a  *= arcsecondsToDegrees*degToRad;

  setter[0][0] =  cos(z_a)*cos(theta_a)*cos(zeta_a) - sin(z_a)*sin(zeta_a);
  setter[0][1] = -cos(z_a)*cos(theta_a)*sin(zeta_a) - sin(z_a)*cos(zeta_a);
  setter[0][2] = -cos(z_a)*sin(theta_a);
  setter[1][0] =  sin(z_a)*cos(theta_a)*cos(zeta_a) + cos(z_a)*sin(zeta_a);
  setter[1][1] = -sin(z_a)*cos(theta_a)*sin(zeta_a) + cos(z_a)*cos(zeta_a);
  setter[1][2] = -sin(z_a)*sin(theta_a);
  setter[2][0] =  sin(theta_a)*cos(zeta_a);
  setter[2][1] = -sin(theta_a)*sin(zeta_a);
  setter[2][2] =  cos(theta_a);

  MatrixSet(a,setter);
}

void MakeNutationMatrix(Matrix *a, double JD){
  double setter[3][3];

  // (delta JD), number of Julian days since 2451545.0
  double dJD = JD-2451545.0;
  // Julian centuries SINCE J2000
  double julianCenturies=(JD-2451545.0)/(365.25*100.0);

  double degToRad = PI/180.0;

  // Approximation of dPsi and dEpsilon
  double dPsi     =  degToRad*(-0.0048*sin((125.0-0.05295*dJD)*degToRad) - 0.0004*sin((200.9-1.97129*dJD)*degToRad));
  double dEpsilon =  degToRad*( 0.0026*cos((125.0-0.05295*dJD)*degToRad) + 0.0002*cos((200.9+1.97129*dJD)*degToRad));

  int nCoeff=6;
  double coeffs[] = { DMSToDecimalDegrees(23 , 26,  21.40600  ),
                      DMSToDecimalDegrees(0  , 0 , -46.836769 ),
                      DMSToDecimalDegrees(0  , 0 , -0.0001831 ),
                      DMSToDecimalDegrees(0  , 0 ,  0.00200340),
                      DMSToDecimalDegrees(0  , 0 , -5.76e-7   ),
                      DMSToDecimalDegrees(0  , 0 , -4.34e-8   ) };

  double epsilonA=0;
  for(int i=0;i<nCoeff;i++){
    epsilonA += coeffs[i]*pow(julianCenturies,i);
    //printf("coeff[%d]: %f\n",i,coeffs[i]);
  }
  epsilonA *= degToRad;
  //printf("epsilonA: %f\n",epsilonA);
  //printf("dEpsilon: %f\n",dEpsilon);

  double epsilon = (epsilonA + dEpsilon);
  //printf("epsilon: %f\n",epsilon);

  setter[0][0] =  cos(dPsi);
  setter[0][1] = -sin(dPsi)*cos(epsilonA);
  setter[0][2] = -sin(dPsi)*sin(epsilonA);
  setter[1][0] =  sin(dPsi)*cos(epsilon);
  setter[1][1] =  cos(dPsi)*cos(epsilon)*cos(epsilonA) + sin(epsilon)*sin(epsilonA);
  setter[1][2] =  cos(dPsi)*cos(epsilon)*sin(epsilonA) - sin(epsilon)*cos(epsilonA);
  setter[2][0] =  sin(dPsi)*sin(epsilon);
  setter[2][1] =  cos(dPsi)*sin(epsilon)*cos(epsilonA) - cos(epsilon)*sin(epsilonA);
  setter[2][2] =  cos(dPsi)*sin(epsilon)*sin(epsilonA) + cos(epsilon)*cos(epsilonA);


  MatrixSet(a,setter);
}

double GetAtmosphericRefractionCorrection(double altitude){
  double correction;
  correction = (1/tan((altitude + 7.31/(altitude+4.4))*(PI/180.0)))/(60.0);
  return correction;
}

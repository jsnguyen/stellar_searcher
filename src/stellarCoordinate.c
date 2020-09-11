#include "stellar_searcher/stellarCoordinate.h"

/*
 * EVERYTHING USES RADIANS FOR CONSISTENCY
 */

StellarCoordinate* StellarCoordinateCreate(){
  StellarCoordinate *sc=malloc(sizeof(StellarCoordinate));
  return sc;
}

void StellarCoordinateInit(StellarCoordinate *sc, double lon, double lat, DateTime dt, CS_TYPE type, EPOCH_TYPE epoch){
  sc->lon=lon;
  sc->lat=lat;
  sc->dt=dt;

  sc->cs=type;
  sc->epoch=epoch;
}

void StellarCoordinateDestroy(StellarCoordinate *sc){
  free(sc);
}

// Copies b into a
void StellarCoordinateCopy(StellarCoordinate *a, StellarCoordinate *b){
  a->lon = b->lon;
  a->lat = b->lat;
  a->dt = b->dt;

  a->cs = b->cs;
  a->epoch = b->epoch;
}

double StellarCoordinateGetLon(StellarCoordinate *sc){
  return sc->lon;
}

double StellarCoordinateGetLat(StellarCoordinate *sc){
  return sc->lat;
}

DateTime StellarCoordinateGetDateTime(StellarCoordinate *sc){
  return sc->dt;
}

CS_TYPE StellarCoordinateGetCoordinateSystemType(StellarCoordinate *sc){
  return sc->cs;
}

EPOCH_TYPE StellarCoordinateGetEpochType(StellarCoordinate *sc){
  return sc->epoch;
}

void StellarCoordinateSet(StellarCoordinate *sc, double lon, double lat, DateTime dt, CS_TYPE type, EPOCH_TYPE epoch){
  sc->lon=lon;
  sc->lat=lat;
  sc->dt=dt;

  sc->cs=type;
  sc->epoch=epoch;
}

void StellarCoordinateSetLon(StellarCoordinate *sc, double lon){
  sc->lon = lon;
}

void StellarCoordinateSetLat(StellarCoordinate *sc, double lat){
  sc->lat = lat;
}

void StellarCoordinateSetDateTime(StellarCoordinate *sc, DateTime dt){
  sc->dt = dt;
}

void StellarCoordinateSetCoordinateSystemType(StellarCoordinate *sc, CS_TYPE type){
  sc->cs = type;
}

void StellarCoordinateSetEpochType(StellarCoordinate *sc, EPOCH_TYPE epoch){
  sc->epoch = epoch;
}

/*
Equatorial to Horizontal
Uses terrestrial latitude
*/
void StellarCoordinateEqToHoriz(StellarCoordinate *sc, DateTime dt, double g_lon, double g_lat, StellarCoordinate *out){

  StellarCoordinate inter;
  StellarCoordinateEqToHaDec(sc, dt, g_lon, g_lat, &inter);

  double alt;
  double az;

  iauHd2ae(inter.lon , inter.lat, g_lat,
           &az, &alt);

  out->lon = az;
  out->lat = alt;
  out->dt = dt;
  out->cs = CS_AZALT;
  out->epoch = EPOCH_JNOW;
}

/*
Equatorial/Horizontal/Horizontal Corrected to HaDec
Note that if you use Horizontal Corrected you get HaDec Corrected
q can be LST or latitude
Careful here, needs to know before hand whether q is local sidereal time to latitude
Make sure that argument is correctly local sidereal time for equatorial or latitude for horizontal
Convention says that output should be in decimal hours BUT I use decimal degrees
*/
void StellarCoordinateEqToHaDec(StellarCoordinate *sc, DateTime dt, double g_lon, double g_lat, StellarCoordinate *out){
  double pm_ra = 0;
  double pm_dec = 0;
  double parallax = 0;
  double radial_velocity = 0;

  double UTC1, UTC2;
  GetSplitUTC(dt, &UTC1, &UTC2);

  double height = 0;
  double xp = 0;
  double yp = 0;

  double pressure = 1013.25; // mbar
  double temperature = 20; // celsius

  double relative_humidity = 0;
  double wavelength = 0.6; // micrometers

  double az, zenith_distance, ha, dec, ra, eq_of_origins;

  iauAtco13(sc->lon, sc->lat,
            pm_ra, pm_dec, parallax, radial_velocity,
            UTC1, UTC2, DUT1,
            g_lon, g_lat, height, xp, yp,
            pressure, temperature, relative_humidity , wavelength,
            &az, &zenith_distance, &ha,
            &dec, &ra, &eq_of_origins);

  out->lon = ha;
  out->lat = dec;
  out->dt = dt;
  out->cs = CS_HADEC;
  out->epoch = EPOCH_JNOW;

}

void StellarCoordinateJ2000ToJNow(StellarCoordinate *in, StellarCoordinate *out){
  return;
}

void StellarCoordinatePrintDecimal(StellarCoordinate *sc, UNIT unit){
  char modifier[9];

  // radians by default
  double lonFactor = 1;
  double latFactor = 1;

  if (unit == DEG){
    lonFactor = RAD2DEG;
    latFactor = RAD2DEG;
  }

  else if (unit == HRDEG){
    lonFactor= RAD2HR;
    latFactor= RAD2DEG;
  }

  if(sc->cs == CS_EQUATORIAL){
    strcpy(modifier,"(ra,dec)");
  }

  else if(sc->cs == CS_AZALT){
    strcpy(modifier,"(az,alt)");
  }

  else if(sc->cs == CS_HADEC){
    strcpy(modifier,"(ha,dec)");
  }

  printf("%d %s: (%f,%f)\n",sc->cs,modifier,sc->lon*lonFactor,sc->lat*latFactor);

}

void MakeCoordinateToVector(double lo, double la, ThreeVector *tv){

  double lon = lo*(PI/180.0);
  double lat = la*(PI/180.0);

  double i = cos(lat)*cos(lon);
  double j = cos(lat)*sin(lon);
  double k = sin(lat);

  ThreeVectorSet(tv,i,j,k);
}

void MakeVectorToCoordinate(ThreeVector *tv, double a[2]){

  a[0]=(180.0/PI)*atan2(tv->j,tv->i);
  a[1]=(180.0/PI)*asin(tv->k);

}

void StellarCoordinateSetJ2000(StellarCoordinate *sc){
  DateTime J2000;
  SetDateTime(&J2000, 2000,1,1,12,0,0);
  sc->dt = J2000;
  sc->epoch = EPOCH_J2000;
}

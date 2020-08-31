#include "stellar_searcher/dateTime.h"

void GetCurrentDateTime(DateTime *dt){
  time_t rawtime;
  time(&rawtime);

  struct tm * ptm;
  ptm = gmtime(&rawtime);

  int Y = ptm->tm_year+1900;
  int M = ptm->tm_mon+1;
  int D = ptm->tm_mday;
  int h = ptm->tm_hour;
  int m = ptm->tm_min;
  int s = ptm->tm_sec; // gmtime gives the seconds in integer values only

  SetDateTime(dt, Y, M, D, h, m, s);
}

void SetDate(DateTime *dt, int Y, int M, int D){
  dt->Y = Y;
  dt->M = M;
  dt->D = D;
}

void SetTime(DateTime *dt, int h, int m, int s){
  dt->h = h;
  dt->m = m;
  dt->s = s;
}

void SetDateTime(DateTime *dt, int Y, int M, int D, int h, int m, double s){
  SetDate(dt, Y, M, D);
  SetTime(dt, h, m, s);
}

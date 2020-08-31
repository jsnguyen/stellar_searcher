#ifndef DATETIME_H 
#define DATETIME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int Y, M, D;
  int h, m;
  double s;
} DateTime;

void GetCurrentDateTime(DateTime *dt);
void SetDate(DateTime *dt, int Y, int M, int D);
void SetTime(DateTime *dt, int h, int m, int s);
void SetDateTime(DateTime *dt, int Y, int M, int D, int h, int m, double s);

#endif

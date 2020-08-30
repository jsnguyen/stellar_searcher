#ifndef CELESTIALTIME_H
#define CELESTIALTIME_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "sofa.h"

#define PI 3.14159265

// !!! NOTICE, NEED RIGOROUS WAY OF FINDING DUT1 FOR DATES PREVIOUS TO THIS AS WELL !!!
// See: https://datacenter.iers.org/eop.php
// This is true from 02 May 2019, 0h UTC, onwards
#define DUT1 -0.2

  // !!! NOTICE, NEED RIGOROUS WAY OF FINDING DT FOR DATES PREVIOUS TO THIS AS WELL !!!
  // USNO website for DT reference seems to be down for a bit...
#define DT 69.36 // Good on 2020-01-01... but this number changes over time unpredictably!

typedef struct {
  int Y, M, D;
  int h, m;
  double s;
} DateTime;

void GetCurrentDateTime(DateTime *dt);
void SetDate(DateTime *dt, int Y, int M, int D);
void SetTime(DateTime *dt, int h, int m, int s);
void SetDateTime(DateTime *dt, int Y, int M, int D, int h, int m, double s);

int GetJDN(DateTime dt);
double GetFractionalJD(DateTime dt);

double GetJD(DateTime dt);
double GetJulianYear(DateTime dt);

void GetSplitUTC(DateTime dt, double *UTC1, double *UTC2);

double GetGMST(DateTime dt);
double GetGAST(DateTime dt);

double GetLMST(DateTime dt, double lon);
double GetLAST(DateTime dt, double lon);

double DMSToRad(char sign, int d, int m, double s);
double HMSToRad(char sign, int h, int m, double s);

void PrintDMS(double rad);
void PrintHMS(double rad);

#endif

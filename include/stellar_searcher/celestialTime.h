#ifndef CELESTIALTIME_H
#define CELESTIALTIME_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265

int GetCurrentJDN();
int GetJDN(int Y, int M, int D);
double GetCurrentJD();
double GetJD(int h, int m, double s, int Y, int M, int D);

double GetJulianYear(int h, int m, double s, int Y, int M, int D);
double GetCurrentJulianYear();

double GetGMT();
double GetGMST(double JD);
double GetGAST(double JD);
double GetLMST(double JD, double lon);
double GetLAST(double JD, double lon);

double DMSToDecimalDegrees(double d, double m, double s);
double HMSToDecimalHours(double h, double m , double s);

void PrintDecimalDegreesToDMS(double a);
void PrintDecimalHoursToHMS(double a);

void DecimalDegreesToDMSStr(double a, char *out);
void DecimalHoursToHMSStr(double a, char *out);

double DecimalDegreesToDecimalHours(double a);
double DecimalHoursToDecimalDegrees(double a);

#endif

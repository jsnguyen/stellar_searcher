#ifndef THREEVECTOR_H
#define THREEVECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double i,j,k;
} ThreeVector;

ThreeVector* ThreeVectorCreate();
void ThreeVectorSetZero(ThreeVector *tv);
void ThreeVectorSet(ThreeVector *tv, double i, double j, double k);
void ThreeVectorDestroy(ThreeVector *tv);

void ThreeVectorSetI (ThreeVector *tv, double i);
void ThreeVectorSetJ (ThreeVector *tv, double j);
void ThreeVectorSetK (ThreeVector *tv, double k);

double ThreeVectorGetI(ThreeVector *tv);
double ThreeVectorGetJ(ThreeVector *tv);
double ThreeVectorGetK(ThreeVector *tv);

void ThreeVectorAdd(ThreeVector *tv, ThreeVector *tvb, ThreeVector *tvc);
void ThreeVectorSub(ThreeVector *tv, ThreeVector *tvb, ThreeVector *tvc);

double ThreeVectorDotProduct(ThreeVector *tva, ThreeVector *tvb);

double ThreeVectorMagnitude(ThreeVector *tv);

void ThreeVectorPrint(ThreeVector *tv);

char* ThreeVectorStr(ThreeVector *tv, char *out);

#endif

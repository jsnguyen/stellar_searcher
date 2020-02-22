#include "stellar_searcher/threeVector.h"

ThreeVector* ThreeVectorCreate(){
  ThreeVector *tv = malloc(sizeof(ThreeVector));
  return tv;
}

void ThreeVectorSetZero(ThreeVector *tv){
  tv->i=0;
  tv->j=0;
  tv->k=0;
}

void ThreeVectorSet(ThreeVector *tv, double i, double j, double k){
  tv->i=i;
  tv->j=j;
  tv->k=k;
}

void ThreeVectorDestroy(ThreeVector *tv){
  free(tv);
}

void ThreeVectorSetI (ThreeVector *tv, double i){
  tv->i=i;
}

void ThreeVectorSetJ (ThreeVector *tv, double j){
  tv->j=j;
}

void ThreeVectorSetK (ThreeVector *tv, double k){
  tv->k=k;
}

double ThreeVectorGetI(ThreeVector *tv){
  return tv->i;
}

double ThreeVectorGetJ(ThreeVector *tv){
  return tv->j;
}

double ThreeVectorGetK(ThreeVector *tv){
  return tv->k;
}

void ThreeVectorAdd(ThreeVector *tva, ThreeVector *tvb, ThreeVector *tvc){
  tvc->i = tva->i + tvb->i;
  tvc->j = tva->j + tvb->j;
  tvc->k = tva->k + tvb->k;
}

void ThreeVectorSub(ThreeVector *tva, ThreeVector *tvb, ThreeVector *tvc){
  tvc->i = tva->i - tvb->i;
  tvc->j = tva->j - tvb->j;
  tvc->k = tva->k - tvb->k;
}


double ThreeVectorDotProduct(ThreeVector *tva, ThreeVector *tvb){
  return tva->i*tvb->i + tva->j*tvb->j + tva->k*tvb->k;
}

double ThreeVectorMagnitude(ThreeVector *tv){
  return sqrt((tv->i*tv->i) + (tv->j*tv->j) + (tv->k*tv->k));
}

void ThreeVectorPrint(ThreeVector *tv){
  printf("( %f,%f,%f )\n", tv->i, tv->j, tv->k);
}

char* ThreeVectorStr(ThreeVector *tv, char *out){
  sprintf(out,"( %3.f, %3.f, %3.f )",tv->i, tv->j, tv->k);
  return out;
}

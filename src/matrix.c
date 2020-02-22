#include "stellar_searcher/matrix.h"

Matrix* MatrixCreate(){
  Matrix *a = malloc(sizeof(Matrix));
  return a;
}

void MatrixDestroy(Matrix *a){
  free(a);
}

void MatrixSetZero(Matrix *a){
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      a->data[i][j] = 0;
    }
  }
}

void MatrixSet(Matrix *a, double m[3][3]){
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      a->data[i][j] = m[i][j];
    }
  }
}

double MatrixGetEntry(Matrix *a, int i, int j){
  return a->data[i][j];
}

void MatrixMultiplyMatrix(Matrix *a, Matrix *b, Matrix *c){

  c->data[0][0] = a->data[0][0]*b->data[0][0]+a->data[0][1]*b->data[1][0]+a->data[0][2]*b->data[2][0];
  c->data[0][1] = a->data[0][0]*b->data[0][1]+a->data[0][1]*b->data[1][1]+a->data[0][2]*b->data[2][1];
  c->data[0][2] = a->data[0][0]*b->data[0][2]+a->data[0][1]*b->data[1][2]+a->data[0][2]*b->data[2][2];

  c->data[1][0] = a->data[1][0]*b->data[0][0]+a->data[1][1]*b->data[1][0]+a->data[1][2]*b->data[2][0];
  c->data[1][1] = a->data[1][0]*b->data[0][1]+a->data[1][1]*b->data[1][1]+a->data[1][2]*b->data[2][1];
  c->data[1][2] = a->data[1][0]*b->data[0][2]+a->data[1][1]*b->data[1][2]+a->data[1][2]*b->data[2][2];

  c->data[2][0] = a->data[2][0]*b->data[0][0]+a->data[2][1]*b->data[1][0]+a->data[2][2]*b->data[2][0];
  c->data[2][1] = a->data[2][0]*b->data[0][1]+a->data[2][1]*b->data[1][1]+a->data[2][2]*b->data[2][1];
  c->data[2][2] = a->data[2][0]*b->data[0][2]+a->data[2][1]*b->data[1][2]+a->data[2][2]*b->data[2][2];

}

void MatrixMultiplyThreeVector(Matrix *a, ThreeVector *b, ThreeVector *c){

  c->i = a->data[0][0]*b->i + a->data[0][1]*b->j + a->data[0][2]*b->k;
  c->j = a->data[1][0]*b->i + a->data[1][1]*b->j + a->data[1][2]*b->k;
  c->k = a->data[2][0]*b->i + a->data[2][1]*b->j + a->data[2][2]*b->k;

}

double MatrixGetDeterminant(Matrix *matA){
  double det;

  double a = matA->data[0][0];
  double b = matA->data[0][1];
  double c = matA->data[0][2];
  double d = matA->data[1][0];
  double e = matA->data[1][1];
  double f = matA->data[1][2];
  double g = matA->data[2][0];
  double h = matA->data[2][1];
  double i = matA->data[2][2];

  double A =  (e*i - f*h);
  double B = -(d*i - f*g);
  double C =  (d*h - e*g);

  det = a*A + b*B + c*C;

  return det;
}

void MatrixGetInverse(Matrix *matA, Matrix *matB){

  double det = MatrixGetDeterminant(matA);

  double a = matA->data[0][0];
  double b = matA->data[0][1];
  double c = matA->data[0][2];
  double d = matA->data[1][0];
  double e = matA->data[1][1];
  double f = matA->data[1][2];
  double g = matA->data[2][0];
  double h = matA->data[2][1];
  double i = matA->data[2][2];

  double A =  (e*i - f*h) * (1/det);
  double B = -(d*i - f*g) * (1/det);
  double C =  (d*h - e*g) * (1/det);
  double D = -(b*i - c*h) * (1/det);
  double E =  (a*i - c*g) * (1/det);
  double F = -(a*h - b*g) * (1/det);
  double G =  (b*f - c*e) * (1/det);
  double H = -(a*f - c*d) * (1/det);
  double I =  (a*e - b*d) * (1/det);

  matB->data[0][0] = A;
  matB->data[0][1] = D;
  matB->data[0][2] = G;
  matB->data[1][0] = B;
  matB->data[1][1] = E;
  matB->data[1][2] = H;
  matB->data[2][0] = C;
  matB->data[2][1] = F;
  matB->data[2][2] = I;

}

void MatrixPrint(Matrix *a){
  printf("(( %f, %f, %f) \n",a->data[0][0],a->data[0][1],a->data[0][2]);
  printf(" ( %f, %f, %f) \n",a->data[1][0],a->data[1][1],a->data[1][2]);
  printf(" ( %f, %f, %f))\n",a->data[2][0],a->data[2][1],a->data[2][2]);
}

char* MatrixStr(Matrix *a, char* out){
  sprintf(out,"(( %f, %f, %f) \n ( %f, %f, %f) \n ( %f, %f, %f))\n",a->data[0][0],a->data[0][1],a->data[0][2],a->data[1][0],a->data[1][1],a->data[1][2],a->data[2][0],a->data[2][1],a->data[2][2]);
  return out;
}

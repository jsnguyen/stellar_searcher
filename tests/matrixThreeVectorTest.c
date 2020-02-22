#include <stdlib.h>
#include <stdio.h>
#include "stellar_searcher/matrix.h"
#include "stellar_searcher/threeVector.h"

// Tests for the matrix and threeVector classes

int main(){

  char out[256];

  ThreeVector *a=ThreeVectorCreate();
  ThreeVector *b=ThreeVectorCreate();
  ThreeVector *c=ThreeVectorCreate();
  ThreeVectorSet(a,1,1,1);
  ThreeVectorSet(b,2,2,2);
  ThreeVectorSetZero(c);

  printf("Given: vector a = (1,1,1), vector b = (2,2,2)\n");
  ThreeVectorPrint(a);
  ThreeVectorPrint(b);
  printf("\n");

  ThreeVectorAdd(a,b,c);
  ThreeVectorStr(c,out);
  printf("a+b -> %s\n",out);

  printf("a dotted with b -> %f\n",ThreeVectorDotProduct(a,b));

  printf("magnitude of a -> %f\n",ThreeVectorMagnitude(a));

  printf("\n");

  Matrix *aa = MatrixCreate();

  double bb[3][3];
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      bb[i][j]=1;
    }
  }

  Matrix *cc=MatrixCreate();
  MatrixSet(cc,bb);
   
  printf("Given: matrix aa is all zeros, matrix bb is all ones\n");
  MatrixStr(aa,out);
  printf("aa -> \n%s\n",out);
  MatrixStr(cc,out);
  printf("cc == bb -> \n%s\n",out);

  MatrixMultiplyThreeVector(cc,a,c);
  ThreeVectorStr(c,out);
  printf("cc x a -> %s\n",out);
  printf("\n");

  bb[0][0]= 7;
  bb[0][1]= 2;
  bb[0][2]= 1;
  bb[1][0]= 0;
  bb[1][1]= 3;
  bb[1][2]= -1;
  bb[2][0]= -3;
  bb[2][1]= 4;
  bb[2][2]= 2;

  MatrixSet(cc,bb);
  MatrixStr(cc,out);
  printf("set cc to weird values -> \n%s\n",out);

  Matrix *dd=MatrixCreate();
  MatrixGetInverse(cc,dd);

  MatrixStr(dd,out);
  printf("inverse of cc -> \n%s\n",out);

  Matrix *ee=MatrixCreate();
  MatrixMultiplyMatrix(cc,dd,ee);
  MatrixStr(ee,out);
  printf("cc x cc_inverse -> \n%s\n",out);

  ThreeVectorDestroy(a);
  ThreeVectorDestroy(b);
  ThreeVectorDestroy(c);
  MatrixDestroy(aa);
  MatrixDestroy(cc);
  MatrixDestroy(dd);
  MatrixDestroy(ee);

  return 0;
}

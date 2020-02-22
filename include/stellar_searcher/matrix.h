#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include "stellar_searcher/threeVector.h"

typedef struct {
    double data[3][3];
} Matrix;

Matrix* MatrixCreate();
void MatrixDestroy(Matrix *a);

void MatrixSetZero(Matrix *a);
void MatrixSet(Matrix *a, double m[3][3]);

double MatrixGetEntry(Matrix *a, int i, int j);

void MatrixMultiplyMatrix(Matrix *a, Matrix *b, Matrix *c);
void MatrixMultiplyThreeVector(Matrix *a, ThreeVector *b, ThreeVector *c);

double MatrixGetDeterminant(Matrix *a);
void MatrixGetInverse(Matrix *matA, Matrix *matB);

void MatrixPrint(Matrix *a);
char* MatrixStr(Matrix *a, char* out);

#endif

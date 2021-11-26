#ifndef MATRIX_H
#define MATRIX_H

#include "matrixio.h"
#include <math.h>
#include <stdbool.h>

void sum(Matrix *A, Matrix const *B);
void sub(Matrix *A, Matrix const *B);
void multx(Matrix* A, double const x);
void mult(Matrix *A, Matrix const *B);

double det(Matrix const A);
void trans(Matrix *A);
Matrix inv(Matrix const *A);

void gauss(Matrix *A); 
static void gauss_vege(Matrix *A, int i);
int rang(Matrix const* A);

#endif

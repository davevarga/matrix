#ifndef MATRIXIO_H
#define MATRIXIO_H

#include <stdio.h>
#include "debugmalloc.h"

typedef struct Matrix {
	double **elm;
	int nrw, nclmn;
}Matrix;

void mprintf(Matrix A);
void mscanf(FILE *fp, Matrix* A);
//void linequasion(FILE)
void mfree(Matrix A);

#endif
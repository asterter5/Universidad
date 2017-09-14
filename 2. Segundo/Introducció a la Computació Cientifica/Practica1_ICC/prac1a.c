#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "prac1funs.c"
int resLinf(int n, double **L, double *b, double *x, double tol);
int resLsup(int n, double **L, double *b, double *x, double tol);
void prodMatVec(int m, int n, double **A, double *x, double *y);
void prodMatMat(int m, int n, int p, double **A, double **B, double **C);

/*
 * Autor: Astor Prieto
 * niUB: 16445586
 *
 */

int main(void) {
	int res;
	int n, i, j;
	double **L, *b, *x, tol;
	tol = pow(10,-6);
	
	/*printf("----- TEST FUNCTION resLinf() -----\n");*/
	printf("----- TEST FUNCTION resLsup() -----\n");

	printf("Dim(Matrix_A)  = \n");
	scanf("%d",&n);
	
	b = (double*)malloc(n*sizeof(double));
	x = (double*)malloc(n*sizeof(double));

	L = (double**)malloc(n*sizeof(double*));
	for (i = 0; i < n; ++i)	{
		L[i] = (double*)malloc(n*sizeof(double));
		if (L[i] == NULL){
			printf("Out of memory. \n");
			exit(2);
		}
	}

	if ((L == NULL) || (b == NULL) || (x == NULL)) {
		printf ("Out of memory.\n");
		exit(1);
	}

	for (i=0; i<n; i++) {
		printf("Matrix (A) values at (%d): \n", (i+1));
		for (j=0; j<n; j++) {
			scanf("%lf",&L[i][j]);
		}
	}

	printf("Vector (b) values: \n");
	for (i=0; i<n; i++) {
		scanf("%lf", &b[i]);
	}

	/*res = resLinf(n, L, b, x, tol);*/
	res = resLsup(n, L, b, x, tol);
	
	if (res != 0) {
		printf("Not solvable.\n");
	} else {
		printf("Succesfully solved. Solution: \n");
		for (i = 0; i < n; i++) {
			printf("x[%d] = %22.15e \n", i, x[i]);
		}
	}
	return 0;
}



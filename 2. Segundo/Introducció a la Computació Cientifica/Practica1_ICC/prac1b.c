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

int ldlt(int n, double **A, double *v, double tol) {
	int i, j, k;
	double aux1, aux2;
	double **A_diagonal, **A_lateral, *v_aux1, *v_aux2;

	aux1 = 0.0;
	aux2 = 0.0;
	
	v_aux1 = (double*)malloc(n*sizeof(double));
	v_aux2 = (double*)malloc(n*sizeof(double));
	
	A_diagonal = (double**)malloc(n*sizeof(double*));
	for (i = 0; i < n; ++i)	{
		A_diagonal[i] = (double*)malloc(n*sizeof(double));
		if (A_diagonal[i] == NULL){
			printf("Out of memory. \n");
			exit(1);
		}
	}

	A_lateral = (double**)malloc(n*sizeof(double*));
	for (i = 0; i < n; ++i)	{
		A_lateral[i] = (double*)malloc(n*sizeof(double));
		if (A_lateral[i] == NULL){
			printf("Out of memory. \n");
			exit(1);
		}
	}

	if ((A_diagonal == NULL) || (A_lateral == NULL) || (v_aux1 == NULL) || (v_aux2 == NULL)) {
		printf ("Out of memory.\n");
		exit(1);
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			A_diagonal[i][j] = 0;
			A_lateral[i][j] = 0;
		}
	}
	
	/* Calculating Matrixes L and D. */
	for (i = 0; i < n; i++) {

		/* Saving the Matrix D. */
		aux1 = 0.0;
		for (j = 0; j < n; j++) {
			aux1 += (pow(A_lateral[j][i], 2))*A_diagonal[j][j];
		}
		A_diagonal[i][i] = A[i][i] - aux1;
		A_lateral[i][i] = 1;
	
		/* Saving the Matrix L. */
		for (j = i + 1; j < n; j++) {
			aux2 = 0.0;
			for (k = 0; k < n; k++) {
				aux2 += A_lateral[k][j]*A_lateral[k][i]*A_diagonal[k][k];
			} 
			A_lateral[i][j] = (A[i][j] - aux2)/A_diagonal[i][i];
		}
	}

	/* Doing Lz = b, saving solution in v_aux1. */
	for (i = 0; i < n; i++) {
		v_aux1[i] = v[i];

		for (j = 0; j < i; j++) {
			v_aux1[i] = v_aux1[i] - A_lateral[j][i] * v_aux1[j]; 
		}
		
		if (A_lateral[i][i] == 0) {
			printf("Not solvable.\n");
			return 1; 
		} else {
			v_aux1[i] = v_aux1[i]/A_lateral[i][i];
		}
	}

	/* Doing Dy = z, saving solution in v_aux2. */
	for (i = 0; i < n; i++) {
		v_aux2[i] = v_aux1[i];

		for (j = 0; j < i; j++) {
			v_aux2[i] = v_aux2[i] - A_diagonal[j][i] * v_aux2[j]; 
		}
		
		if (A_diagonal[i][i] == 0) {
			printf("Not solvable.\n");
			return 1; 
		} else {
			v_aux2[i] = v_aux2[i]/A_diagonal[i][i];
		}
	} 

	/* Now you have the L-Matrix saved in "A", and the y-vector saved in "v". */
	for (i = 0; i < n; i++) {
		v[i] = v_aux2[i];
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			A[j][i] =  A_lateral[j][i];
		}
	} return 0;
}

int main(void) {
	int res;
	int n, i, j;
	double **A, *x, *y, tol;
	tol = pow(10,-9);
	
	printf("Dim(Matrix_A)  = \n");
	scanf("%d",&n);

	x = (double*)malloc(n*sizeof(double));
	y = (double*)malloc(n*sizeof(double));

	A = (double**)malloc(n*sizeof(double*));
	for (i = 0; i < n; ++i) {
		A[i] = (double*)malloc(n*sizeof(double));
		if (A[i] == NULL) {
			printf("Out of memory. \n");
			exit(1);
		}
	}

	if ((A == NULL) || (x == NULL) || (y == NULL)) {
		printf ("Out of memory.\n");
		exit(1);
	}

	for (i = 0; i < n; i++) {
		printf("Matrix (A) values at (%d): \n", (i+1));
		for (j = 0; j < n; j++) {
			scanf("%lf",&A[i][j]);
		}
	}

	printf("Vector (b) values: \n");
	for (i = 0; i < n; i++) {
		scanf("%lf", &x[i]);
	}

	res = ldlt(n, A, x, tol);
	
	if (res != 0) {
		printf("Not solvable. \n");
	} 

	/* Solving L_tx = y. */
	res = resLsup(n, A, x, y, tol);

	if (res != 0) {
		printf("Not solvable. \n");
	} else {
		printf("Succesfully solved. Solution: \n");
		for (i = 0; i < n; i++) {
			printf("x[%d] = %22.15e \n", i, y[i]);
		}
	}
	return 0;
}

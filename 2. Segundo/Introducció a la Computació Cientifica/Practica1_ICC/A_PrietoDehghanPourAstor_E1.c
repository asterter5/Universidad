#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int resLinf(int n, double **L, double *b, double *x, double tol);
int resLsup(int n, double **L, double *b, double *x, double tol);
void prodMatVec(int m, int n, double **A, double *x, double *y);
void prodMatMat(int m, int n, int p, double **A, double **B, double **C);

int resLinf(int n, double **L, double *b, double *x, double tol) {
	int i, j;
	
	for (i = 0; i < n; i++) {
		x[i] = b[i];

		/*Multiplicar filas y restarlas.*/
		for (j = 0; j < i; j++) {
			x[i] = x[i] - L[i][j] * x[j]; 
		}
		
		/*No se puede calcular.*/
		if (L[i][i] == 0) {
			printf("Not solvable.\n");
			return 1; 
		} else {
			x[i] = x[i]/L[i][i];
		}
	} return 0;
}

int resLsup(int n, double **L, double *b, double *x, double tol) {
	int i, j;
	double **L_trans;
	
	L_trans = (double**)malloc(n*sizeof(double*));
	for (i = 0; i < n; ++i)	{
		L_trans[i] = (double*)malloc(n*sizeof(double));
		if (L_trans[i] == NULL){
			printf("Out of memory. \n");
			exit(1);
		}
	}
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			L_trans[j][i] = L[i][j];
		}
	}

	for (i = n-1; i >= 0; i--) {
		x[i] = b[i];

		/*Multiplicar filas y restarlas.*/
		for (j = n-1; j > i; j--) {
			x[i] = x[i] - L_trans[j][i] * x[j];
		}
		
		/*No se puede calcular.*/
		if (L[i][i] == 0) {
			printf("Not solvable.\n");
			return 1;
		} else {
			x[i] = x[i]/L_trans[i][i];
		}
	} return 0;
}

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

	printf("> MATRIX D: \n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%+.12le \n", A_diagonal[i][j]);
		} printf("\n");
	}

	printf("> MATRIX L: \n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%+.12le \n", A_lateral[i][j]);
		} printf("\n");
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

/*
 * Autor: Astor Prieto
 * niUB: 16445586
 *
 */

int main(void) {
	int res;
	int n, i, j;
	double h;
	double **A, *x, *y, tol;
	tol = pow(10,-10);
	h = 16.445586; /* niUB */
	n = 6;

	printf("Dim(Matrix_A)  = %d \n", n);

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

	n = 6;
	for (i = 0; i < n; i++) {
		A[i][i] = h/2;
	}

	n = 5;
	for (i = 0; i < n; i++) {
		A[i][i+1] = h + i;
		A[i+1][i] = h + i;
	}

	n = 4;
	for (i = 0; i < n; i++) {
		A[i][i+2] = h - i;
		A[i+2][i] = h - i;
	}

	n = 6;
	printf("Matrix (A) values: \n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%+.12le \n", A[i][j]);
		} printf("\n");
	}

	printf("Vector (x) values: \n");
	for (i = 0; i < n; i++) {
		x[i] = 100;
		printf("%22.15e ", x[i]);
	} printf("\n");

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

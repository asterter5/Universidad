#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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

void prodMatVec(int n, int m, double **A, double *x, double *y) {
	int i, j;
	double aux;
	
	aux = 0.0;
	/* "n" has to be the dim of Matrix A, and "m" has to be the elements in vector x. */
	for (i = 0; i < n; i++) {
		aux = 0.0;
		for (j = 0; j < m; j++){
			aux = aux + A[j][i]*x[j];
		} 
		y[i] = aux;
	}
}

void prodMatMat(int n, int m, int p, double **A, double **B, double **C) {
	int i, j, i_aux, j_aux;
	double aux;

	aux = 0.0;
	i_aux = 0, j_aux = 0;
	/* "n" has to be the number of rows in A, and "m" the number of collumns in B. */
	for (i = 0; i < n; i++) {
		aux = 0.0;
		for (j = 0; j < m; j++) {
			aux = aux + A[i][j]*B[j][i];
			
		} 
		C[i_aux][j_aux] = aux;

		if (j_aux >= m) {
			i_aux = i_aux + 1;
			j_aux = 0;
		} else {
			j_aux = j_aux +1;
		}
	}
}

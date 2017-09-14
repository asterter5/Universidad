#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "prac2funs_2.h"

/* AUTOR: Astor Prieto, niUB: 16445586, DNI: 39427935R */

double F(double x) {
    double F;
    F = pow(x, 3) + 3 * pow(x, 2) + x + 1;
    return F;
}

double dF(double x) {
    double dF;
    dF = 3 * pow(x, 2) + 6 * x + 1;
    return dF;
}

int main(void) {
    int itMax, n, i, j;
    double a, b, C;
    double tol = pow(10, -6);
    double *x, *A;

    printf("Indica el valor del inici 'a': \n");
    scanf("%lf", &a);
    
    printf("Indica el valor del final 'b': \n");
    scanf("%lf", &b);

    printf("Indica el valor del coeficient 'C': \n");
    scanf("%lf", &C);
    
    printf("Indica el valor maxim de subintervals 'N': \n");
    scanf("%d", &n);

    printf("Indica el valor maxim de iteracions: \n");
    scanf("%d", &itMax);

    x = (double *) malloc (itMax*sizeof(double));
    if (x == NULL) {
        exit(1);
    }

    A = (double *) malloc (n*sizeof(double));
    if (A == NULL) {
        exit(2);
    }

    A[0] = a;
    A[n] = b;
    for (i = 1; i < n; i++) {
        A[i] = a + i*((b - a)/n);
    }

    for (i = 1; i < (n + 1); i++) {
        if (((F(A[i-1])-C)*(F(A[i])-C)) < 0) {
            x[0] = 0.5*(A[i-1] + A[i]);
            Newton(x, tol, itMax, C);
            printf("Zeros trobats a [%f, %f]:\n", A[i-1], A[i]);
            for (j = 1; j < n; j++) {
                if (x[j] == 0 && x[j-1] != 0) {
                    printf("x[0] = %f\n", x[j-1]);
                }
            }
        } 
    }
    return 0;
}

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "prac2funs_1.h"
#include "prac2funs_2.h"
 
/* AUTOR: Astor Prieto, niUB: 16445586, DNI: 39427935R */
 
double f(double x) {
    double f;
 
    f = sin(x) - cos((2*x));
 
    return f;
}
 
double F(double x) {
    double F;
 
    F = sin(x) - cos((2*x));
 
    return F;
}
 
double dF(double x) {
    double dF;
 
    dF = cos(x) + 2*sin((2*x));
 
    return dF;
}
 
int main(void) {
    int nMax = 30;
    int itMax = 10;
    int cont = 1;
    double C = 0.86;
    double tol = pow(10, -11);

    int N = 15;
    int i, j;
    double a, b, x_1, x_2, T_n;
    double *x, *A;

    x = (double *) malloc (itMax*sizeof(double));
    if (x == NULL) {
        exit(1);
    }

    A = (double *) malloc (N*sizeof(double));
    if (A == NULL) {
        exit(2);
    }

    x_1 = 0;
    x_2 = 0;

    a = 0;
    b = 1;

    A[0] = a;
    A[N] = b;
    for (i = 1; i < N; i++) {
        A[i] = a + i*((b - a)/N);
    }

    printf("Usant 'C' valor: %f\n", C);

    x[0] = 0.5*(A[i-1] + A[i]);
    Newton(x, tol, itMax, C);
    printf("Zero trobat a [%f, %f]:\n", A[i-1], A[i]);
    for (j = 1; j < N; j++) {
        if (x[j] == 0 && x_1 == 0) {
            printf("x[1] = %f\n", x[j-1]);
            x_1 = x[j-1];
        }
    }

    a = 2;
    b = 3;

    A[0] = a;
    A[N] = b;
    for (i = 1; i < N; i++) {
        A[i] = a + i*((b - a)/N);
    }

    x[0] = 0.5*(A[i-1] + A[i]);
    Newton(x, tol, itMax, C);
    printf("Zero trobat a [%f, %f]:\n", A[i-1], A[i]);
    for (j = 1; j < N; j++) {
        if (x[j] == 0 && x_2 == 0) {
            printf("x[2] = %f\n", x[j-1]);
            x_2 = x[j-1];
        }
    }
    
    printf("x_1 = %f, x_2 = %f\n", x_1, x_2);
    for (N = 2; N < pow(2, nMax); N = pow(2, cont)) {
        T_n = trapezis(N,  x_1,  x_2);
        cont++;
    }

    printf("Valor 'N': %d\n", N);
    printf("Integral Aproximada: %f\n", T_n);
    return 0;
}

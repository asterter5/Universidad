#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "prac2funs_1.h"
#include "prac2funs_2.h"

/* AUTOR: Astor Prieto, niUB: 16445586, DNI: 39427935R */

double f(double x) {
	double f;

	f = pow(sin(y), 2);

	return f;
}

double F(double x) {
	int N, nMax;
	double T_n = 0;
	double T_aux = 0;
	double tol = pow(10, -8);
	int cont = 1;

	for (N = 2; N < pow(2, nMax); N = pow(2, cont)) {
        T_n = trapezis(N,  -x,  x);
        if (fabs(T_n - T_aux) < tol) {
            printf("Integral Aproximada: %f\n", T_n);
            return T_n;
        }
        T_aux = T_n;
        cont++;
    }

    printf("Error al calcular la integral aproximada.\n");
    return 1.0;
}

double dF(double x) {
	double dF;

	dF = f(x) + f(-x);

	return dF;
}

int main(void) {
	int N, nMax;
    int cont = 1;
    double C, T_n;
    double T_aux = 0;
    
    printf("Indica el valor 'C': \n");
    scanf("%lf", &C);

    return -1;
}
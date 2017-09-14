#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "prac2funs_2.h"

/* AUTOR: Astor Prieto, niUB: 16445586, DNI: 39427935R */

double F(double x);
double dF(double x);

int Newton(double *x, double tol, int itMax, double c) {
    int i;

    for (i = 0; i < itMax; i++) {
        x[i+1] = x[i] - ((F(x[i]) - c)/dF(x[i]));
        
        if (fabs(F(x[i]) - c) < tol) {
            return 0;
        }
    }
    return 1;
}

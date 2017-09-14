#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "prac2funs_1.h"

/* AUTOR: Astor Prieto, niUB: 16445586, DNI: 39427935R */

double f(double x){
    double f;
    f = 2*x + 2;
    return f;
}

int main(void) {
    int N, nMax;
    int cont = 1;
    double a, b, T_n;
    double T_aux = 0;
    double tol = pow(10, -3);
    
    printf("Indica el valor del inici 'a': \n");
    scanf("%lf", &a);
    
    printf("Indica el valor del final 'b': \n");
    scanf("%lf", &b);
    
    printf("Indica el valor maxim de subintervals 'N': \n");
    scanf("%d", &nMax);

    for (N = 2; N < pow(2, nMax); N = pow(2, cont)) {
        T_n = trapezis(N,  a,  b);
        if (fabs(T_n - T_aux) < tol) {
            printf("Integral Aproximada: %f\n", T_n);
            return 0;
        }
        T_aux = T_n;
        cont++;
    }

    printf("Error al calcular la integral aproximada.\n");
    return -1;
}

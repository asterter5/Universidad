#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "prac2funs_1.h"

/* AUTOR: Astor Prieto, niUB: 16445586, DNI: 39427935R */

double f(double x);

double trapezis(int N, double a, double b){
    double h, sum, Tn;
    int i;
    
    h = (b - a) / N;
    sum = 0;
        
    for (i = 1; i < (N - 1); i++) { 
        sum = sum + f(a + i*h);
    }
    
    Tn = ((0.5 * f(a)) + sum + (0.5 * f(b))) * h;
    return Tn;
}

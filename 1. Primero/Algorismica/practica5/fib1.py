import math
import time

def fib(n):
    if n == 1:
        return 1
    if n == 0:
        return 0
    return fib(n-1) + fib(n-2)

def fib1():
    x = input("Quin numero vols de la succecio de Fibonacci: ")
    t1 = time.clock()
    n = fib(x)
    t2 = time.clock()
    print "El teu numero es: ", n
    print "El temps de proces ha estat %0.3f ms" % ((t2-t1)*1000)

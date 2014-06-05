import time

def fermatp():
    n = input("Introdueix el teu enter per a comprovar: ")
    t1 = time.clock()
    a = [2, 3, 5]
    cond = False
    for i in a:
        if (i**(n-1)%n == 1):
            cond = True
    if cond:
        print "Si Primer."
    else:
        print "No Primer."
    t2 = time.clock()
    print "El temps de proces ha estat %0.3f ms" % ((t2-t1)*1000)

import time

def factorp():
    n = input("Introdueix el teu enter a comprovar: ")
    t1 = time.clock()
    cond = False
    for i in range(2, n):
        if n%i == 0:
            cond = True
    if cond:
        print "No primer."
    else:
        print "Si Primer."
    t2 = time.clock()
    print "El temps de proces ha estat %0.3f ms" % ((t2-t1)*1000)
    

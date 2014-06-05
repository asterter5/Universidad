# practica5.py
#
# autor: Astor Prieto (aprietde10)

import time
import math

def fib(n):
    if n == 1: 
        return 1
    if n == 0:
        return 0
    return fib(n-1) + fib(n-2) #si n es mes gran que 1, la funcio es va cridant a ella mateixa fins a arribar a 1 o 0.

def fib1():
    x = input("Quin numero vols de la succecio de Fibonacci: ")
    t1 = time.clock()
    n = fib(x) #cridem a la funcio fib, i calculem el temps que triga el proces.
    t2 = time.clock()
    print "El teu numero es: ", n
    print "El temps de proces ha estat %0.3f ms" % ((t2-t1)*1000)

def mcd():
    m, n = input("Introdueix dos enters separats per una coma: ")
    while m: #nem calculant fins que m arriba a 0.
        m, n = n%m, m 
    print "El M.C.D es: ", n

def era1():
    n = input("Introdueix el teu enter N mes gran: ")
    listA = range(2, n + 1) #creem una llista des de 2 fins a n amb tots els possibles primers.
    listB = [] #creem una llista buida on inserim els primers menors a la arrel de n.
    m = listA[0] #mirem el primer nombre de la llista primera
    while m < math.sqrt(n): 
        for i in listA: 
            if i%m == 0: #mirem per a cada element de la primera llista i eliminem els seus multiples
                listA.remove(i)
        listB.append(m) #si el element m es primer, el afegim a la llista b
        m = listA[0] #prenem el seguent valor de la llista com a primer

    print listB + listA #imprimim els valors que ens han quedat

def era2(): #AQUEST CODI ESTA INCOMPLERT, PER AIXO NO ESTA EXECUTAT.
    n = 1000 #no trobo forma de optimitzar el codi per a 10.000.000
    listA = range(2, n + 1)
    m = listA[0]
    while m < math.sqrt(n):
        for i in listA:
            if i%m == 0:
                listA.remove(i)
        m = m + 1
    print listA

def factorp():
    n = input("Introdueix el teu enter a comprovar: ")
    t1 = time.clock()
    cond = False #fem que vagi calculant mentre no comprovi la condicio de primer
    for i in range(2, n):
        if n%i == 0: #mirem per a que valor de i es divisible entre n
            cond = True
    if cond:
        print "No primer." #imprimim si es primer
    else:
        print "Si Primer." #si la condicio no es compleix no es primer
    t2 = time.clock()
    print "El temps de proces ha estat %0.3f ms" % ((t2-t1)*1000)
    
def fermatp():
    n = input("Introdueix el teu enter per a comprovar: ")
    t1 = time.clock()
    a = [2, 3, 5] #canviem els numeros per a comprovar, prenent el 2, 3 i 5 unicament
    cond = False
    for i in a:
        if (i**(n-1)%n == 1): #de la mateixa forma que el anterior, comprovem si la condicio es compleix, pero amb el teorema petit de Fermat
            cond = True
    if cond:
        print "Si Primer."
    else:
        print "No Primer."
    t2 = time.clock()
    print "El temps de proces ha estat %0.3f ms" % ((t2-t1)*1000)
    
fib1()
mcd()
era1()
factorp()
fermatp()

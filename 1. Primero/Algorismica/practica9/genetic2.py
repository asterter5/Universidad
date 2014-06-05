import random
import math
import time

AVAL = 0

# Definim la funcio davaluacio.
def puntf(r):
# Transformem els bits en un valor real x a linterval [-6,6]
    sum=0.0
    for i in range(len(r)):
        sum = sum + r[i]*(2**i)
    x = -6.0 + sum * (12.0/(2.0**(len(r))-6.0))
    return x

def cost2(r):
    # Avaluem el cromosoma x
    global AVAL
    l = len(r)/2
    x = puntf(r[:l])
    y = puntf(r[l:])
    z = (200 - ((x**2 + y - 11)**2 - (x + y**2 - 7)**2))
    AVAL += 1
    return z

# Definim el creuament
def creuament(r1,r2):
    i=random.randint(1,len(r1)-2)
    return r1[:i]+r2[i:], r2[:i]+r1[i:]

# Definim la mutacio amb probabilitat mutprob per cada bit
def mutacio(r,mutprob):
    for i in range(len(r)):
        if random.random()<mutprob: 
            if r[i]==0: r[i]=1
            else: r[i]=0
    return r

# Creem la poblacio inicial
def initpop(n,long):
    # Generem una poblacio de n cromosomes de longitud long. 
    import random
    pop = [[0] * long for x in range(n)]
    for i in range(n):
        for j in range(long):
            if random.random()>0.5: pop[i][j] += 1 
    return pop

# Definim el proces de seleccio estandard
def seleccio_std(pop,cost2,start=0):
    popsize=len(pop)
    # Calculem el valor minim de la funcio davaluacio   
    c=[cost2(v) for v in pop[start:]]
    minim = min(c)  
    # Normalitzem els valors de manera que el pitjor 
    # individu tingui un valor 0.01
    if minim<0.0: 
        for i in range(len(c)): 
            c[i] = c[i] + abs(minim) + 0.01
    else: 
        for i in range(len(c)): 
            c[i] = c[i] - minim + 0.01
    # Calculem la suma de tots els valors de la funcio davaluacio
    sum=0.0
    for i in range(len(c)): sum = sum + c[i]
    # Triem lindividu de forma proporcional al seu valor dadaptacio 
    ran=random.random()*sum
    i = 0
    sum2=c[0]
    while ran > sum2: 
        i += 1
        sum2=sum2+c[i]
    # Retornem lindividu seleccionat
    return i+start

# Definim lalgorisme genetic 
# Restriccio: popsize ha desser un nombre parell
def genetic2(cost2, cromsize=44, popsize=50, mutprob=0.01, maxiter=150):
    t1 = time.clock()
    # Generem la poblacio inicial
    pop=initpop(popsize, cromsize)
    # Iterem fins al nombre de generacions
    for cont in range(maxiter):
        # Avaluem la generacio i lordenem
        scores = [(cost2(v),v) for v in pop]
        scores.sort(reverse=True)
        ranked=[v for (s,v) in scores]
        # Afegim els dos millors cromosomes a la seguent generacio
        newpop=[0]*popsize
        newpop[0],newpop[1]=ranked[0],ranked[1]
        # Seleccionem les parelles 
        for i in range(0,popsize,2):        
            ind1=seleccio_std(ranked,cost2,i)
            ranked[i],ranked[ind1]=ranked[ind1],ranked[i]
            ind2=seleccio_std(ranked,cost2,i+1)
            ranked[i+1],ranked[ind2]=ranked[ind2],ranked[i+1]
        # Creuem les parelles i generem els fills
        new=[0]*popsize
        for i in range(0,popsize,2): 
            new[i],new[i+1] = creuament(ranked[i],ranked[i+1])
        # Mutem
        mut=[0]*popsize
        for i in range(popsize):
            mut[i]=mutacio(new[i],mutprob)
        # Afegim els pares (excepte els dos millors) a la generacio
        mut = mut + ranked[2:]
        # Seleccionem la resta d'individus per la seguent generacio
        for i in range(2,popsize):
            newpop[i]=mut[seleccio_std(mut,cost2,i)]
        pop=newpop
    t2 = time.clock()
    print "f(x, y): ", scores[0][0]
    print "x: ", puntf((scores[0][1])[len(scores[0][1]):])
    print "y: ", puntf((scores[0][1])[:len(scores[0][1])])
    print "Avaluacions: ", AVAL
    print ((t2 - t1) * 1000), " ms."

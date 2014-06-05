import math

def era1():
    n = input("Introdueix el teu enter N mes gran: ")
    listA = range(2, n + 1)
    listB = []
    m = listA[0]
    while m < math.sqrt(n):
        for i in listA:
            if i%m == 0:
                listA.remove(i)
        listB.append(m)
        m = listA[0]

    print listB + listA

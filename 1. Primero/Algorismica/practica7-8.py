# practica7-8.py
#
# autor: Astor Prieto (aprietde10)

def negatius(n): 
    pos = [] #creem dues llistes, una per els enters positius
    neg = [] #i una altra per els enters negatius
    for i in n: #iterem per a cada element de la llista original
        if i < 0:
            neg.append(i) #si es negatiu, el posem a la segona llista
        else:
            pos.append(i) #si es positiu, a la primera
    print (neg + pos) #imprimim la concatenacio de les dues noves llistes
a = [1, -2, 3, -4, -3, 5, -6];
negatius(a);


def exponent(a, n):
    if (n < 2): #si el exponent es mes petit que 2
        return a #retorna "a"^1, 
    expn = a * exponent(a, (n-1)) #cada recursio restem 1 al exponent
    return expn #i el multipliquem per la base.
print exponent(3,5)


def reverse(string):
    if len(string) == 2: #si el string te nomes dos caracters
        newStr = string[1] + string[0] #els canviem de ordre
        return newStr
    half = (len(string)/2)
    res = reverse(string[half:]) + reverse(string[:half]) #dividim el string en 2
    return res #i concatenem el final del string invertit amb el principi.
print reverse("hola, com estas?")


def length(L):
    return length2(L, 0) #cridem a una funcio que pren un parametre 0 per a comptador
    
def length2(L, x):
    if L == []:
        return x #diem que si la llista esta buida, retorni el valor de la llista
    return length2(L[:-1], x+1) #per a cada recursio, restem el ultim valor a la llista i sumem 1 al comptador
llista = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
print "len(L) = ", length(llista)


def isMember(x, L):
    if L == []:
        return "N", x #si la llista restant es la buida, no es trobat
    if (L[0] == x):
        return "Y", L[0] #si el element 0 de la llista es el buscat, si es trobat
    return isMember(x, L[1:]) #per a cada recursio, treiem el primer valor de la llista per a la nova llista
elem = 5
llist = [1, 2, 3, 4, 5, 6, 7, 8, 9]
print isMember(elem, llist)


def max_llista(L):
    if (len(L) <= 1): #quan la llista te nomes un enter, retorna el enter
        return L[0]
    else: #sino, mitjansant recursio, va executant la funcio sobre la llista sense el primer elem.
        N = max_llista(L[1:])
    if (N > L[0]): #comparem el primer de la nostra llista amb la recursio guardada a "N"
        return N
    else: #si el maxim esta al primer elem. retornem "L[0]"
        return L[0]
llista = [3, 5, 7, 2, 9, 4]
print max_llista(llista)



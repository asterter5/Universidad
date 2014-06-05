# prova.py
#
# autor: Astor Prieto (aprietde10)

def join_numbers(N, suma): #NO FUNCIONA
    x = N[0]
    if not (isinstance(x, int)):
        return join_numbers(N[:][:], suma)
    return join_numbers(N[1:], suma+x)

def Max_iterativo(L):
    max1 = 0
    max2 = 0 #Creamos dos variables para almacenar los max
    for i in L:
        if max2 < i:
            max2 = i #Hacemos una pasada y guardamos el max en 'max2'
    L.remove(max2) #Lo borramos de la lista
    for i in L:
        if max1 < i:
            max1 = i #De la segunda pasada sacamos el 'max1'
    return max1, max2

def Max_recursivo(L):
    max1 = L[0]
    max2 = L[1] #Los dos elementos restantes de la lista seran los max
    x = min(L) #Tomamos el minimo valor de la lista 'L'
    L.remove(x) #Lo borramos de la lista
    if len(L) == 1:
        return max1, max2 #Cuando solo queden los valores que queremos, return
    return Max_recursivo(L) #Llamamos a la funcion

################################################################################

#a = [1, [2, 3], [[4, 5], 6], 7]
#print join_numbers(a, 0)

a = [3, 5, 1, 7, 2, 9]
print Max_iterativo(a)

a = [3, 5, 1, 7, 2, 9]
print Max_recursivo(a)

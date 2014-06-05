def length(L):
    return length2(L, 0)
    
def length2(L, x):
    if L == []:
        return x
    return length2(L[:-1], x+1)

llista = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
print "len(L) = ", length(llista)

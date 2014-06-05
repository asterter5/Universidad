def max_llista(L):
    if (len(L) <= 1):
        return L[0]
    else:
        N = max_llista(L[1:])
    if (N > L[0]):
        return N
    else:
        return L[0]

llista = [3, 5, 7, 2, 9, 4]
print max_llista(llista)

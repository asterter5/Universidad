def isMember(x, L):
    if L == []:
        return "N", x
    if (L[0] == x):
        return "Y", L[0]
    return isMember(x, L[1:])

elem = 5
llist = [1, 2, 3, 4, 5, 6, 7, 8, 9]
print isMember(elem, llist)

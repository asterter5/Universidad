def exponent(a, n):
    if (n < 2):
        return a
    expn = a * exponent(a, (n-1))
    return expn

print exponent(3,5)

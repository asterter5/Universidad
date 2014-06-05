def mcd():
    m, n = input("Introdueix dos enters separats per una coma: ")
    while m:
        m, n = n%m, m
    print "El M.C.D es: ", n

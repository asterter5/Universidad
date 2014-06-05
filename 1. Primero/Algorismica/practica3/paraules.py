import string

def paraules():
	print "Aquest programa compta el numero de paraules de una frase."
	frase = raw_input("Entra la teva frase aqui: ")
	count = string.count(frase, chr(32))
	print "El numero de paraules de la frase es: ", count + 1
	


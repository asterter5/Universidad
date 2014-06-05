def enters(num):
	suma = 0
	while (num != 0):
		suma = suma + num
		num = num - 1
	print "La suma dels enters es: ", suma

def impares(num):
	impar = 0
	while (num != 0):
		impar = impar + (2*num - 1)
		num = num - 1
	print "La suma dels impars es: ", impar

def diventer(num):
	div = num
	count = 0
	while (div > 1):
		div = div/2
		count = count + 1
	print num, "es pot dividir ", count, " vegades entre 2 abans de arribar a 1."

def suma(num):
	sums = 0
	cond = True
	while (num != 999):
		sums = sums + num
		num = input("Introdueix un altre nombre o <999> per a sortir: ")
		cond = True
	if (num == 999):
		cond = False
	print "La suma dels teus nombres es: ", sums

def mentre():
	num = input("Introdueix el teu nombre N: ")
	enters(num)
	impares(num)
	diventer(num)
	suma(num)

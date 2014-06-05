def futval():
	print "Aquest programa calcula el valor futur de una determinada inversio en un periode de temps."
	principal = input("Entra la inversio inicial: ")
	time = input("Indica el periode en anys: ")
	apr = input("Entra el interes anual, en valor absolut: ")
	for i in range(time):
		principal = principal * (1 + apr)
	print "La quantitat al cap de", time, "anys es:", principal

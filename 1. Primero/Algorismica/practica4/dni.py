def dni():
	print "Aquest programa calcula la teva lletra del DNI en base als numeros del mateix."
	abec = { 0:"T", 1:"R", 2:"W", 3:"A", 4:"G", 5:"M", 6:"Y", 7:"F", 8:"P", 9:"D", 10:"X", 11:"B", 12:"N", 13:"J", 14:"Z", 15:"S", 16:"Q", 17:"V", 18:"H", 19:"L", 20:"C", 21:"K", 22:"E" }
	num = input("Introdueix els numeros del teu dni: ")
	ch = abec[(num % 23)]
	print "La lletra del teu DNI es: ", ch, ", i queda ", num, "-", ch
	

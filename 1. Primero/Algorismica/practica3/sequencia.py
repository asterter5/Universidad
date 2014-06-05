import string

def sequencia():
	file = open("lletra.txt", "r")
	text = file.readlines()
	file.close()
	num = 0
	pas = 0 
	print "Aquest programa compta el nombre de cops que\npodem trobar una 't' seguida de una 'h' en la lletra\nde la 'song'."
	for line in text:
		pas = string.count(line, "th") or string.count(line, "Th")
		num = num + pas 
	print
	print "El nombre de cops que hi ha a la lletra una 't' i una 'h' seguides es: ", num

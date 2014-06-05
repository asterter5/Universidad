import string

def paraula():
	print "Aquest programa cerca una paraula introduida per el usuari\ni compta el nombre de vegades que hi apareix en la lletra\nde la 'song'."
	file = open("lletra.txt", "r")
	text = file.readlines()
	file.close()
	word = raw_input("Introdueix la paraula a cercar: ")
	num = 0
	pas = 0 
	for line in text:
		pas = string.count(line, word) + string.count(line, string.capitalize(word))
		num += pas
	print
	print "El programa ha trobat la teva paraula a la lletra", num, "cops."



# practica3.py
#
# autor: Astor Prieto (aprietde10)

import string

def acro():
	print "Aquest programa transforma frases\nen els seus corresponents acronims."
	frase = raw_input("Entra aqui la teva frase: ") #Demanem una frase al usuari
	words = string.split(frase) #Separem la frase en una llista de paraules
	acro = '' #Inicialitzem una variable on guardarem el acronim
	print "El teu acronim es: "
	for word in words:	
		acro = acro + " " + (word[0]) #Dins el bucle for anem agafant la inicial de cada paraula y la desem en la variable acro
	print string.upper(acro) #Imprimim acro tot en majuscules

def paraules():
	print "Aquest programa compta el numero de paraules de una frase."
	frase = raw_input("Entra la teva frase aqui: ") #Demanem una frase al usuari
	count = string.count(frase, chr(32)) #Comptem el nombre de espais que hi ha en la frase
	print "El numero de paraules de la frase es: ", count + 1 #Imprimim el compte + 1, ja que sera el nombre de paraules
	
def cesar():
	print "Aquest programa codifica amb el xifratge de Cesar una frase."
	frase = raw_input("Introdueix la frase per codificar (sols minuscules i espais):\n")
	n = input("Introdueix un enter per a usar com a clau del xifratge (del 1 al 10): ")
	d = 0 #Amb la frase per codificar i la clau introduides, iniciem una variable on guardarem els caracters canviats
	code = '' #Aqui guardarem el text codificat
	print "La teva frase codificada es: "
	for ch in frase:
		if ch >= chr(65) and ch <= chr(90):
			if ch != chr(32): #Diferenciem els caracters dels espais en blanc
				d = chr(ord(ch) + n)
				if d > chr(90): #Si se supera el valor de la z en ASCII, fem que la funcio resti la distancia fins a la lletra que es vol, fen un bucle en el abecedari
					d = chr(ord(ch) + (n - 26))
				code = code + d
		if ch >= chr(97) and ch <= chr(122):
			if ch != chr(32):
				d = chr(ord(ch) + n)
				if d > chr(122):
					d = chr(ord(ch) + (n - 26))
				code = code + d
		elif ch == chr(32): #Per els espais deixem un lloc en blanc
			code = code + " "
	print code
		
def lyrics():
	file = open("lletra.txt","r")
	code = open("lletra_cesar.txt", "w")
	text = file.readlines()
	file.close()
	n = 5 #Definim constants i obrim el fitxer a utilitzar
	lineNum = 0 #Aqui guardarem el numero de linia
	print "Aquest programa codifica en xifratge de Cesar amb n = 5 la lletra de la 'song'.\nconsulta el fixer lletra_cesar.txt per al resultat."
	for line in text:
		lineNum = lineNum + 1 #Imprimim el numero de linia al comensament
		code.write(str(lineNum) + " - ")
		for ch in line:
			if ch >= chr(97) and ch <= chr(122):
				if ch != chr(32): #Fem el mateix que a la funcio cesar amb cada caracter en particular
					d = chr(ord(ch) + n)
					if d > chr(122):
						d = chr(ord(ch) + (n - 26))
					code.write(d) #Al final guardem el codi al fitxer nou lletra_cesar.txt
			elif ch >= chr(65) and ch <= chr(90): #Dos moduls If per a les majuscules i les minuscules en ASCII
				if ch != chr(32): #Fem el mateix que a la funcio cesar amb cada caracter en particular
					d = chr(ord(ch) + n)
					if d > chr(90):  
						d = chr(ord(ch) + (n - 26))
					code.write(d) #Al final guardem el codi al fitxer nou lletra_cesar.txt
			else:
				code.write(" ")
		code.write("\n")

def sequencia():
	file = open("lletra.txt", "r")
	text = file.readlines()
	file.close()
	num = 0
	pas = 0 #Aquestes dos variables son on guardarem el numero de cops que troba la sequencia en el text
	print "Aquest programa compta el nombre de cops que\npodem trobar una 't' seguida de una 'h' en la lletra\nde la 'song'."
	for line in text:
		pas = string.count(line, "th") or string.count(line, "Th")
		num = num + pas #Sumem al comptador el numero de cops que trobem la sequencia en una linia
	print
	print "El nombre de cops que hi ha a la lletra una 't' i una 'h' seguides es: ", num #Imprimim el resultat i tamquem el fitxer

def paraula():
	print "Aquest programa cerca una paraula introduida per el usuari\ni compta el nombre de vegades que hi apareix en la lletra\nde la 'song'."
	file = open("lletra.txt", "r")
	text = file.readlines()
	file.close()
	word = raw_input("Introdueix la paraula a cercar: ") #Comptara cuants cops apareix la teva paraula al text, tambe si hi surt inclosa a una altra paraula
	num = 0
	pas = 0 #Fem al mateix que al exercici anterior, pero canviem la sequencia per un input que fa el usuari
	for line in text:
		pas = string.count(line, word) + string.count(line, string.capitalize(word))
		num += pas
	print
	print "El programa ha trobat la teva paraula a la lletra", num, "cops."



# practica4.py
#
# autor: Astor Prieto (aprietde10)

import math
import string
import random

def enters(num):
	suma = 0 #Variable on guardem la suma
	while (num != 0): #Bucle que va calculant la suma a suma i disminueix el valor de la variable fins a arribar a 0
		suma = suma + num
		num = num - 1
	print "La suma dels enters es: ", suma

def impares(num):
	impar = 0 #Variable on guardem la suma dels imparells
	while (num != 0): #El mateix bucle que a enters, pero amb el calcul modificat per a trobar els n primers imparells
		impar = impar + (2*num - 1)
		num = num - 1
	print "La suma dels impars es: ", impar

def diventer(num):
	div = num #Guardem la variable de la divisio
	count = 0 #Contador per al nombre de cops que fem la divisio
	while (div > 1): #Bucle que va dividint entre 2 fins a arribar a 1 i augmenta el contador
		div = div/2
		count = count + 1
	print num, "es pot dividir ", count, " vegades entre 2 abans de arribar a 1."

def suma(num):
	sums = 0
	cond = True
	while (num != 999): #Bucle que mentres no entris el 999, vagi demanant nombres
		sums = sums + num
		num = input("Introdueix un altre nombre o <999> per a sortir: ")
		cond = True
	if (num == 999): #Un cop entres el 999, surt del bucle i mostra la suma total
		cond = False
	print "La suma dels teus nombres es: ", sums

def mentre():
	num = input("Introdueix el teu nombre N: ") #Introduim la variable que usarem a les altres funcions
	enters(num) #cridem les funcions pasant num
	impares(num)
	diventer(num)
	suma(num)

def inversio():
	print "Aquest programa calcula el temps (en anys) en el que\nuna inversio cualsevol tarda en doblarse."
	temps = 0 #Contador per als anys
	inv = 1 #inversio arbitraria
	apr = input("Introdueix el interes de la teva inversio (en %): ") 
	while (inv < 2): #Bucle que mentre la inversio no es dobli, sumi el interes entrat i augmenti el contador
		inv = inv * (1 + (apr/100.0))
		temps = temps + 1
	print "El temps que tarda la inversio en doblarse es ", temps, " anys."

def nota():
	notes = { 0:"Suspes", 1:"Suspes", 2:"Suspes", 3:"Suspes", 4:"Suspes", 5:"Aprovat", 6:"Aprovat", 7:"Notable", 8:"Notable", 9:"Excelent", 10:"Matricula" }
	print "Aquest programa troba, segons la teva nota numerica,\nla valoracio de la teva qualificacio."
	nota = input("Introdueix la teva nota: ") #Introduim la nota 
	valor = math.floor(nota) #La arrodonim a la baixa
	if (nota > 10):	#Si entres una nota mes gran que 10, no funciona
		print "No pot ser que hagis tret mes de un 10!"
	else: #Cerquem el valor de la nota al nostre diccionari i la imprimim
		print "La teva valoracio es de", notes[valor]

def dni():
	print "Aquest programa calcula la teva lletra del DNI en base als numeros del mateix."
	abec = { 0:"T", 1:"R", 2:"W", 3:"A", 4:"G", 5:"M", 6:"Y", 7:"F", 8:"P", 9:"D", 10:"X", 11:"B", 12:"N", 13:"J", 14:"Z", 15:"S", 16:"Q", 17:"V", 18:"H", 19:"L", 20:"C", 21:"K", 22:"E" }
	num = input("Introdueix els numeros del teu dni: ") #Entres els numeros del NIF
	ch = abec[(num % 23)] #Trobem amb la resta de la divisio, el caracter qu volem del diccionari
	print "La lletra del teu DNI es: ", ch, ", i queda ", num, "-", ch

def llista():
	print "Aquest programa desordena aleatoriament els elements de\nun string introduit per el usuari."
	nueva = "" #Variable on guardem la llista aleatoria
	frase = raw_input("Introdueix la teva frase: \n")
	abc = list(frase) #guardem en una llista els elements de la frase introduida
	for word in frase:
		for ch in word: #Bucle que per cada paraula i caracter en la frase ens canvii aleatoriament el valor de la llista
			aleatorio = random.randint(1, len(frase) - 1)
			nueva = nueva + abc[aleatorio] #imprimim la nova llista amb els caracters aleatoris
	print nueva

def otan():
	print "Aquest programa transforma un string al alfabet fonetic de la OTAN."
	frase = raw_input("Introdueix la teva frase: \n") #Introduim una string a canviar
	frase = string.upper(frase) #Primer la posem tota en majuscules
	nueva = "" #Variable on guardem la string de sortida
	odict = {"A":"Alpha", "B":"Bravo", "C":"Charlie", "D":"Delta", "E":"Echo", "F":"Foxtrot", "G":"Golf", "H":"Hotel", "I":"India", "J":"Juliet", "K":"Kilo", "L":"Lima", "M":"Mike", "N":"November", "O":"Oscar", "P":"Papa", "Q":"Quebec", "R":"Romeo", "S":"Sierra", "T":"Tango", "U":"Uniform", "V":"Victor", "W":"Whiskey", "X":"Xray", "Y":"Yankee", "Z":"Zulu", " ":" " }
	for word in frase:
		for ch in word: #De la misma forma que a llista, per a cada caracter a la frase
			nueva += (odict[ch] + " ") #Canviem els caracters per a les paraules desitjades del alfabet de la OTAN
	print nueva

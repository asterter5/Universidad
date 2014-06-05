import math

def nota():
	notes = { 0:"Suspes", 1:"Suspes", 2:"Suspes", 3:"Suspes", 4:"Suspes", 5:"Aprovat", 6:"Aprovat", 7:"Notable", 8:"Notable", 9:"Excelent", 10:"Matricula" }
	print "Aquest programa troba, segons la teva nota numerica,\nla valoracio de la teva qualificacio."
	nota = input("Introdueix la teva nota: ")
	valor = math.floor(nota)
	if (nota > 10):	
		print "No pot ser que hagis tret mes de un 10!"
	else:
		print "La teva valoracio es de", notes[valor]
	

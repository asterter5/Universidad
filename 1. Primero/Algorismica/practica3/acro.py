import string

def acro():
	print "Aquest programa transforma frases\nen els seus corresponents acronims."
	frase = raw_input("Entra aqui la teva frase: ")
	words = string.split(frase)
	acro = ''
	print "El teu acronim es: "
	for word in words:	
		acro = acro + " " + (word[0])
	print string.upper(acro)


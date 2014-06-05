import random
import string

def llista():
	print "Aquest programa desordena aleatoriament els elements de\nun string introduit per el usuari."
	nueva = ""
	frase = raw_input("Introdueix la teva frase: \n")
	abc = list(frase)
	for word in frase:
		for ch in word:
			aleatorio = random.randint(1, len(frase) - 1)
			nueva = nueva + abc[aleatorio]
	print nueva

import string

def otan():
	print "Aquest programa transforma un string al alfabet fonetic de la OTAN."
	frase = raw_input("Introdueix la teva frase: \n")
	frase = string.upper(frase)
	nueva = ""
	odict = {"A":"Alpha", "B":"Bravo", "C":"Charlie", "D":"Delta", "E":"Echo", "F":"Foxtrot", "G":"Golf", "H":"Hotel", "I":"India", "J":"Juliet", "K":"Kilo", "L":"Lima", "M":"Mike", "N":"November", "O":"Oscar", "P":"Papa", "Q":"Quebec", "R":"Romeo", "S":"Sierra", "T":"Tango", "U":"Uniform", "V":"Victor", "W":"Whiskey", "X":"Xray", "Y":"Yankee", "Z":"Zulu", " ":" " }
	for word in frase:
		for ch in word:
			nueva += (odict[ch] + " ")
	print nueva

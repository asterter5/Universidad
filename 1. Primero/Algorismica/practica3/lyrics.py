def lyrics():
	file = open("lletra.txt","r")
	code = open("lletra_cesar.txt", "w")
	text = file.readlines()
	file.close()
	n = 5 
	lineNum = 0
	print "Aquest programa codifica en xifratge de Cesar amb n = 5 la lletra de la 'song'.\nconsulta el fixer lletra_cesar.txt per al resultat."
	for line in text:
		lineNum = lineNum + 1
		code.write(str(lineNum) + " - ")
		for ch in line:
			if ch >= chr(97) and ch <= chr(122):
				if ch != chr(32): 
					d = chr(ord(ch) + n)
					if d > chr(122):
						d = chr(ord(ch) + (n - 26))
					code.write(d) 
			elif ch >= chr(65) and ch <= chr(90):
				if ch != chr(32):
					d = chr(ord(ch) + n)
					if d > chr(90):
						d = chr(ord(ch) + (n - 26))
					code.write(d)
			else:
				code.write(" ")
		code.write("\n")

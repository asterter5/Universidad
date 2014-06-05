import string

def cesar():
	print "Aquest programa codifica amb el xifratge de Cesar una frase."
	frase = raw_input("Introdueix la frase per codificar (sols minuscules i espais):\n")
	n = input("Introdueix un enter per a usar com a clau del xifratge (del 1 al 10): ")
	d = 0
	code = ''
	print "La teva frase codificada es: "
	for ch in frase:
		if ch >= chr(65) and ch <= chr(90):
			if ch != chr(32):
				d = chr(ord(ch) + n)
				if d > chr(90) or :
					d = chr(ord(ch) + (n - 26))
				code = code + d
		if ch >= chr(97) and ch <= chr(122):
			if ch != chr(32):
				d = chr(ord(ch) + n)
				if d > chr(122) or :
					d = chr(ord(ch) + (n - 26))
				code = code + d
		elif ch == chr(32):
			code = code + " "
	print code
		

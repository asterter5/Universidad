# practica6.py
#
# autor: Astor Prieto (aprietde10)

import time

def dna():
	secuencias = ["AGATACATTAGACAATAGAGATGTGGTC", "GTCAGTCTGGCCTTGCCATTGGTGCCACCA", "TACCGAGAAGCTGGATTACAGCATGTACCATCAT"] #las tres sequencias que nos pide el enunciado
	text = open("HUMAN-DNA.txt", "r") #el documento donde encontramos el genoma humano
	lines = text.readlines()
	text.close()
	n = -1 #iterador para saltar de una secuencia a otra
	for seq in secuencias: #repetimos el algoritmo por cada secuencia
		t1 = time.clock() #incializamos el reloj
		dist_ed = 1000
		n += 1
		for line in lines: #calculamos la distancia de edicion por cada linea del genoma
			seq_length = len(seq) + 1
			line_length = len(line) + 1
			pos = line_length - seq_length #calculamos la posicion de nuestro string en el texto
			tabla = [[0] * line_length for x in range(seq_length)] #creamos la tabla de Levenshtein
			for i in range(seq_length): 
				tabla[i][0] = i
			for j in range(line_length): 
				tabla[0][j] = 0
			for i in xrange(1, seq_length):
				for j in range(1, line_length):
					delete = tabla[i-1][j] + 2
					insert = tabla[i][j-1] + 2
					substitute = tabla[i-1][j-1]
					if seq[i-1] != line[j-1]: #ponemos todas las operaciones posibles de edicion, con los costes que requiere el enunciado
						substitute += 1
					tabla[i][j] = min(insert, delete, substitute)
			for x in tabla[len(tabla) - 1]: #miramos por cada elemento de la tabla el menor elemento y lo llamamos la Distancia de Edicion
				if x < dist_ed:
					dist_ed = x
		t2 = time.clock() #cerramos el reloj
		print "El patro ", secuencias[n], " es troba a la linia \n", line, ", posicio ", pos, " del cromosoma 2 huma, i la seva distancia de edicio es ", dist_ed #finalmente imprimimos los valores finales
		print "El temps de proces ha estat %0.3f ms" % ((t2-t1)*1000) #no todos los valores son correctos, pues no he encontrado el fallo pero tampoco la solucion
		print

dna()

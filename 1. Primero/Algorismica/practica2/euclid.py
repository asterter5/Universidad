def euclid():
	import math
	print"Este programa calcula la distancia euclidiana entre dos puntos del plano."
	x1 = input("Introduce la coordenada X de un punto: ")
	y1 = input("Introduce su coordenada Y: ")
	x2 = input("Introduce la coordenada X de un segundo punto: ")
	y2 = input("Introduce su coordenada Y: ")
	d = math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
	print"La distancia euclidiana de los puntos elegidos es: ", d

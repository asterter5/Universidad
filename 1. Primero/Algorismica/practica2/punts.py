def punts():
	x1 = input("Defineix la coordenada X de un punt del espai: ")
	y1 = input("Defineix la coordenada Y: ")
	x2 = input("Defineix la coordenada X de un segon punt: ")
	y2 = input("Defineix la coordenada Y: ")
	m = (y2-y1) / (x2-x1)
	print "El pendent de la recta que uneix aquests punts es: ", m

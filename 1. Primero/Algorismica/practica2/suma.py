def suma():
	print"Muestra los numeros menores a 1000\nque son multiplos de 3 y 5 a la vez:"
	sum = 0
	for i in range(1001):
		if i%3 == 0 and i%5 == 0:
			print i
			sum += i
	print "La suma de todos los multiplos\nde 3 y 5 es: ", sum

def factmenor():
	import math
	print"Este programa muestra todos los valores menores que\n6204484017332394393600000 y que son factoriales de algun numero natural: "
	for i in range(50):
		n = math.factorial(i)
		if n < 6204484017332394393600000:
			print n


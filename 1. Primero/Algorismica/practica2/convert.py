# Un programa per pasar de graus Celsius a Fahrenheit
# Escrit per : Astor Prieto.

def convert():
	print "Celsius\t\tFahrenheit "
	for i in range(0,110,10):
		C = i 
		F = 9.0 / 5.0 * C + 32
		print C, "\t\t", F

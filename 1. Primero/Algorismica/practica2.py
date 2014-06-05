# practica2.py
#
# autor: Astor Prieto (aprietde10)

import math

def futval():
	print "Aquest programa calcula el valor futur de una determinada inversio en un periode de temps."
	principal = input("Entra la inversio inicial: ")
	time = input("Indica el periode en anys: ")
	apr = input("Entra el interes anual, en valor absolut: ")
	for i in range(time): 
		principal = principal * (1 + apr)
	print "La quantitat al cap de", time, "anys es:", principal

def convert():
	print "Celsius\t\tFahrenheit "
	for i in range(0,110,10):
		C = i #La variable C (celsius) aumenta con la funcion range.
		F = 9.0 / 5.0 * C + 32
		print C, "\t\t", F

def exp():
	print "Este programa calcula el resultado de las siguientes expresiones: \na = 4.0 / 10.0 + 3.5 * 2.0\nb = 10 % 4 + 6 / 2\nc = abs(4 - 20 / 3) ** 3\nd = sqrt(4.5 - 5.0) + 7 * 3\ne = 3 * 10 / 3 + 10 % 3\nf = 3L ** 3"
	a = 4.0 / 10.0 + 3.5 * 2.0
	b = 10 % 4 + 6 / 2
	c = abs(4 - 20 / 3) ** 3
	e = 3 * 10 / 3 + 10 % 3
	f = 3L ** 3 #Calculamos cada expresion por separado y las mostramos en pantalla.
	print "A", a, "\n", "B", b, "\n", "C", c, "\nD Imposible hacer la raiz de un negativo\n", "E", e, "\n", "F", f

def punts():
	x1 = input("Defineix la coordenada X de un punt del espai (amb un punt darrera): ")
	y1 = input("Defineix la coordenada Y (amb un punt darrera): ") #Definimos un punto del espacio.
	x2 = input("Defineix la coordenada X de un segon punt (amb un punt darrera): ")
	y2 = input("Defineix la coordenada Y (amb un punt darrera): ") #Definimos un segundo punto.
	m = (y2-y1) / (x2-x1) #Calculo del pendiente de la recta que los une.
	print "El pendent de la recta que uneix aquests punts es: ", m

def euclid():
	print"Este programa calcula la distancia euclidiana entre dos puntos del plano."
	x1 = input("Introduce la coordenada X de un punto: ")
	y1 = input("Introduce su coordenada Y: ")
	x2 = input("Introduce la coordenada X de un segundo punto: ")
	y2 = input("Introduce su coordenada Y: ") #Igual que el anterior, definimos dos puntos.
	d = math.sqrt((x2 - x1)**2 + (y2 - y1)**2) #En cambio, la formula es para calcular la distancia euclidiana.
	print"La distancia euclidiana de los puntos elegidos es: ", d

def euclid2():
	print"Este programa calcula la distancia euclidiana entre dos puntos del plano,\ny aproxima el resultado al entero mas cercano."
	x1 = input("Introduce la coordenada X de un punto: ")
	y1 = input("Introduce su coordenada Y: ")
	x2 = input("Introduce la coordenada X de un segundo punto: ")
	y2 = input("Introduce su coordenada Y: ")
	d = math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
	d = round(d, 0) #Exactamente igual que el anterior, pero con la funcion round hacemos que el resultado se redondee.
	print"La aproximacion de la distancia euclidiana de los puntos elegidos es: ", d

def factmenor():
	print"Este programa muestra todos los valores menores que\n6204484017332394393600000 y que son factoriales de algun numero natural: "
	n = 1
	fact = 0
	while fact < 6204484017332394393600000:
		fact = math.factorial(n) #n muestra los factoriales por cada fact del rango.
		n = n+1 #Sumamos 1 en cada paso de n.
		if fact < 6204484017332394393600000:
			print fact #La funcion if solo imprime en pantalla los factoriales menores de nuestro numero.

def suma():
	print"Muestra los numeros menores a 1000\nque son multiplos de 3 y 5 a la vez:"
	sum = 0
	for i in range(1001): #Buscamos cuales son multiplos de 3 y 5 a la vez dentro del rango 1000.
		if i%3 == 0 and i%5 == 0: #Encontramos los multiplos con if y con el resto de la division entre 3 y entre 5.
			print i #Si cumple los requisitos, se imprimen los multiplos de 3 y 5.
			sum += i
	print "La suma de todos los multiplos\nde 3 y 5 es: ", sum #Con la funcion sum hacemos la suma algebraica de todos los multiplos imprimidos en pantalla.

def divisible():
	x = 0
	for x in range(10, 3000): #Usamos una funcion for en la sabemos que cabe el divisible que buscamos.
		if x%2 == 0 and x%3 == 0 and x%4 == 0 and x%5 == 0 and x%6 == 0 and x%7 == 0 and x%8 == 0 and x%9 == 0 and x%10 == 0: #Con if y el operador modulo, encontramos el divisible mas pequenyo de todos nuestros numeros a la vez y lo imprimimos.
			print "El divisible de 2, 3, 4, 5,\n6, 7, 8, 9 i 10 mes petit es: ", x


def inversio():
	print "Aquest programa calcula el temps (en anys) en el que\nuna inversio cualsevol tarda en doblarse."
	temps = 0
	inv = 1
	apr = input("Introdueix el interes de la teva inversio (en %): ")
	while (inv < 2):
		inv = inv * (1 + (apr/100.0))
		temps = temps + 1
	print "El temps que tarda la inversio en doblarse es ", temps, " anys."

# motxilla.py
#
# Autor: Astor Prieto (16445586)

def motxilla(W, values, weighs):

	WM = 0.0
	index = []
	backpack = []

	for i in range(len(values)):
		rs = [float(values[i])/float(weighs[i]), values[i], weighs[i]]
		index.append(rs)

	index = sorted(index, reverse=True)

	for elm in index:
		WM += elm[2]
		if WM < W:
			backpack.append(elm)
		else:
			WM -= elm[2]

	return backpack, WM

# MAIN FUNC

VAL = [10, 30, 25, 30, 15, 50]
PES = [10, 5, 50, 25, 10, 30]
MAX_PES = 100
print motxilla(MAX_PES, VAL, PES)

#
# Com saber si es optima la solucio.
# Aquest algorisme itera dos cops una llista de "n" elements.
# La complexitat per tant sera de O(n^2)
#
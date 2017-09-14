# viatjant.py
#
# Autor: Astor Prieto (16445586)

import networkx as nx

def viatjant(R, start):

	i = None
	mini = None
	suma = 0.0
	visited = []
	current = start
	P = R.copy()

	for node in R.nodes():
		if current not in visited:
			visited.append(current)
			i = R.edges(current, data=True)
			mini = minima(i)
			if not P.has_edge(mini[0], mini[1]):
				i.remove(mini)
				mini = minima(i)
			else:
				P.remove_edge(mini[0], mini[1])
			current = mini[1]
			suma += mini[2]['weight']

	visited.append(start)

	return visited

def minima(edgel):

	val = 1000.0
	res = None

	for i in edgel:
		if i[2]['weight'] < val:
			val = i[2]['weight']
			res = i

	return res

# MAIN FUNC

LIST1 = [('A', 'B', 20.0), ('A', 'C', 42.0), ('A', 'D', 35.0), ('B', 'C', 30.0), ('B', 'D', 34.0), ('C', 'D', 12.0)]
LIST2 = [('A', 'B', 100.0), ('A', 'C', 125.0), ('A', 'D', 100.0), ('A', 'E', 75.0), ('B', 'C', 50.0), ('B', 'D', 75.0), ('B', 'E', 125.0), ('C', 'D', 100.0), ('C', 'E', 125.0), ('D', 'E', 50.0)]
R = nx.Graph()
R.add_weighted_edges_from(LIST2)
print viatjant(R, 'A')

#
# En aquest algorisme, escollim cada cop la arista mes petita entre dos vertex,
# per a trobar la solucio al problema del viatjant de comerc.
# Sempre has de donar un node per al cual comensar, ja que depen del node inici,
# el resultat varia completament, donant altres recorreguts amb altres distancies.
# La complexitat del algorisme es O(n * e), on n son el nombre de ciutats del 
# problema, i e, la quantitat de aristes que te cada node mirat.
#
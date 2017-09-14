# aillats.py
# 
# Autor: Astor Prieto (16445586)

import networkx as nx

def aillats(G):

	i = 0
	l = []

	for n in G:
		if nx.degree(G, n) == 0:
			l.append(n)
			i += 1

	return i, l

# MAIN FUNC

G = nx.Graph()
E = [('A', 'B'), ('A', 'C'), ('A', 'E'), ('B', 'D'), ('C', 'D'), ('C', 'E'), ('D', 'E')]
G.add_edges_from(E)
G.add_node('F')
G.add_node('G')
print aillats(G)

#
# Ordre de un graf fa referencia al nombre de vertex "V" del graf.
# Mida fa la referencia al nombre de aristes "A" del graf.
# El grau de cada node ens diu en nombre de connexions que te amb la resta del graf.
# Si busquem els nodes amb grau(n) = 0, trobem els nodes aillats.
# Nomes fem un recorregut O(n), mirant un cop cada node.
#
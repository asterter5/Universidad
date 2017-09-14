# recorregut.py
#
# Autor: Astor Prieto (16445586)

#
# Pregunta 1.
# Aquest graf, que te una unica component connexa, es llegiria aixi en una taula
# d'adjacencies:
# 1 2 4
# 2 3 5
# 3 2 5
# 4 1
# 5 2 3
# 

#
# Pregunta 2.
# Matriu de adjacencia:
# 0 1 1 0 1
# 1 0 0 1 0
# 1 0 0 1 1
# 0 1 1 0 1
# 1 0 1 1 0
# 
# Llista de adjacencia:
# 1 2 3 5
# 2 1 4
# 3 1 4 5
# 4 2 3 5
# 5 1 3 4
# 

#
# Pregunta 3.
# El ordre de un graf es el nombre de vertex que te.
# La mida es el nombre de aristes que te un graf.
# 

import networkx as nx

def DFS(G):

	for i in G:
		G.node[i]['index'] = i
		G.node[i]['visited'] = 0
		G.node[i]['parent'] = -1

	res =  DFS_visit(G, 1, [])

	return del_rep(res)

def DFS_visit(G, node, res):

	G.node[node]['visited'] = 1
	res.append(G.node[node]['index'])

	for i in G.neighbors(node):
		if not G.node[i]['visited']:
			G.node[i]['parent'] = node
			DFS_visit(G, G.node[i]['index'], res)
		if i == len(G.neighbors(node)) and G.node[node]['parent'] != -1:
			DFS_visit(G, G.node[node]['parent'], res)

	return res

def del_rep(P):

	res = []

	for i in P:
		if not i in res:
			res.append(i)

	return res

# FUNC BFS

def BFS(G):

	for i in G:
		G.node[i]['index'] = i

	return BFS_visit(G, 1)

def BFS_visit(G, node, cua=[1], res=[]):

	res.append(cua.pop(0))

	for i in G.neighbors(node):
		tmp = G.node[i]['index']
		if not(tmp in cua) and not(tmp in res):
			cua.append(G.node[i]['index'])

	if len(cua) > 0:
		BFS_visit(G, cua[0], cua, res)

	return res

# MAIN FUNC

G = nx.read_adjlist("recorregut.dat", nodetype=int)
print DFS(G)
print
print BFS(G)

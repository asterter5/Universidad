# articulats.py
#
# Autor: Astor Prieto (16445586)

import networkx as nx

def articulats(G):

	lst = []

	for i in G:
		tmp = G.copy()
		tmp.remove_node(i)
		lst.append(len(DFS(tmp)))

	if len(del_rep(lst)) > 1:
		return True

	return False

# FUNC DFS

def DFS(G):

	for i in G:
		G.node[i]['index'] = i
		G.node[i]['visited'] = 0
		G.node[i]['parent'] = -1

	bg = G.node[i]['index']
	res =  DFS_visit(G, bg, [])

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

# MAIN FUNC

G = nx.read_adjlist("articulats.dat", nodetype=int)
print articulats(G)

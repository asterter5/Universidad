# gasolineres.py
#
# Autor: Astor Prieto (16445586)

def gasolineres(D, vec):

	res = []
	pas = 0
	mod = 0
	bg = 0

	for i in vec:
		tmp = i - mod
		if tmp <= D:
			if tmp > bg:
				bg = tmp
			else:
				res.append(i)
				pas += 1
		else:
			res.append(vec[vec.index(i) - 1])
			res.append(i)
			mod += tmp
			pas += 1

	return del_rep(res), pas

def del_rep(P):

	res = []

	for i in P:
		if not i in res:
			res.append(i)

	return res

# FUNC MAIN

D = 100
vec = [0, 40, 80, 160, 220, 300]
print gasolineres(D, vec)

# 
# Aquest algorisme, amb complexitat O(n) mira els valors del vector i busca les
# millors aproximacions al valor D sense passarse. Aixi troba els passos en els 
# que ha de parar.
# 
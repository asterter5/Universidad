#!/usr/bin/python
# -*- coding: utf-8 -*-
"""
"""

__author__ = "Astor Prieto"
__email__  = "astorprieto@gmail.com"

import networkx as nx
import sys

def llegir_graf(entrada):
    
    nom = entrada
    G = nx.read_edgelist(nom, nodetype=int, data=(('weight',float),))
    return G

def cota(G, i, n):
    return G.edge[i][n]['weight']

def cota_final(G, sol_op):
    
    cota = 0
    for elm in sol_op:
        cota = cota + G.edge[elm[0]][elm[1]]['weight']
    return cota

def aparellament(G, i, sol_par, sol_op, cMin, cMax):
    
    #print "i =", i
    sol_par.append(i)
    G.node[i]['visited'] = True
    
    for n in G.neighbors(i):
        if (G.node[n]['visited'] == False):
            p = cota(G, i, n) + cMin
            if (cMin < p < cMax):
                if (len(sol_par) == len(G.nodes())):
                    sol_par.append(n)
                    sol_op = sol_par[:]
                    cMax = p
                    sol_par = []
                    return sol_op 
                else:
                    aparellament(G, n, sol_par, sol_op, p, cMax)
                    
    e = sol_par.pop()
    G.node[e]['visited'] = False
                    
def agencia_de_contactes(G):
    
    sol_par = []
    sol_op = []
    weight = []
    cMin = 0
    cMax = 0
    
    for n in G.nodes():
        G.node[n]['visited'] = False
        
    for p in G.edges(data=True):
        weight.append(p[2]['weight'])
    cMin = min(sorted(weight))
    for l in G.edges(data=True):
        cMax = cMax + l[2]['weight']
        
    sol_par.append(1)
    return aparellament(G, 1, sol_par, sol_op, cMin, cMax)

def main(entrada='exemple1.dat'):
    """
    """
    G = llegir_graf(entrada)
    sol_op = agencia_de_contactes(G)
    sol_op = [sol_op[i:i+2] for i in range(1, len(sol_op), 2)]

    print "La millor solucio es:", sol_op
    print "Amb pes:", cota_final(G, sol_op)

# main() METHOD CALL
if __name__ == '__main__':
    main(*sys.argv[1:])

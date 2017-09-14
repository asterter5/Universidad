#!/usr/bin/python
# -*- coding: utf-8 -*-
"""
"""

__author__ = "Astor Prieto"
__email__  = "astorprieto@gmail.com"

import networkx as nx
import sys

def llegir_graf(entrada): #Θ(V + E)
    nom = entrada #Θ(1)
    G = nx.read_edgelist(nom, nodetype=int, data=(('weight',float),)) #Θ(V + E)
    return G

def aparellament(nodes, edges, solucio):
    MyEdge = (0, 0, {100000})
    aux = []

    if len(nodes) == 0:
        return solucio

    for E in edges:
        if E[2] <= MyEdge[2]:
            MyEdge = E

    edges.remove(MyEdge)

    for E in edges:
        if (E[0] == MyEdge[0]) or (E[1] == MyEdge[1]) or (E[0] == MyEdge[1]) or (E[1] == MyEdge[0]):
            aux.append(E)

    for i in aux:
        edges.remove(i)

    nodes.remove(MyEdge[0])
    nodes.remove(MyEdge[1])
    solucio.append(MyEdge)

    return aparellament(nodes, edges, solucio)

def agencia_de_contactes(G):
    sol = []
    nod = G.nodes()
    edg = G.edges(data=True)

    return aparellament(nod, edg, sol)
    

def main(entrada='exemple2.dat'):
    """
    Llegeix l'entrada del problema i fa quelcom amb ella.

    Parameters
    ----------

    entrada: string
        Ruta a l'arxiu d'entrada del problema.
    """
    G = llegir_graf(entrada)
    print "\nLes parelles de nodes son:\n", agencia_de_contactes(G)    
    
# 
# La complexitat de la funció agencia_de_contactes() i aparellament() és de O(E^2)
# 

# Aquest troç és l'encarregat de cridar la funció main amb els paràmetres
# introduïts per consola. No ho podeu modificar.
if __name__ == '__main__':
    main(*sys.argv[1:])

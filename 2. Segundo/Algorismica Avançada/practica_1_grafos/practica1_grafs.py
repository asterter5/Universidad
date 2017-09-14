#!/usr/bin/python
# -*- coding: utf-8 -*-
"""
"""

__author__ = "Astor Prieto"
__email__  = "astorprieto@gmail.com"

from Queue import Queue
import networkx as nx
import sys

def llegir_graf(entrada):
    f = open(entrada, 'r')
    dim = f.readline()
    mat = f.readlines()
    f.close()

    G = nx.Graph()
    nodeCount = 0
    x_coord = 0
    y_coord = 0
    
    for line in mat:
        for char in line:
            if char == '.':
                G.add_node(nodeCount, data="pas")
                nodeCount += 1
            if char == 'X':
                G.add_node(nodeCount, data="wall")
                nodeCount += 1
            if char == '$':
                G.add_node(nodeCount, data="treasure")
                nodeCount += 1

    DIM_Y = dim[:1]
    DIM_X = dim[2:]
    for node in G.nodes():
        if y_coord < (int(DIM_Y)-1):
            if node == 0:
                G.add_edge(node, node+1)
                G.add_edge(node, node+int(DIM_X))
                x_coord += 1
            elif x_coord == (int(DIM_X)-1):
                G.add_edge(node, node+int(DIM_X))
                y_coord += 1
                x_coord = 0
            else:
                G.add_edge(node, node+int(DIM_X))
                G.add_edge(node, node+1)
                x_coord += 1
        else:
            if x_coord < (int(DIM_X)-1):
                G.add_edge(node, node+1)
                x_coord += 1
    
    for node in G.nodes(data=True):
        if node[1]['data'] == 'wall':
            G.remove_node(node[0])

    return G

def grafs_tresor(G, nodoInicial=0):

    for node in G.nodes():
        G.node[node]['dist'] = 9999
      
    G.node[nodoInicial]['dist'] = 0
    cola = Queue()
    cola.put(nodoInicial)
    
    while not cola.empty():
        a = cola.get()
        for vecinos in G.neighbors(a):
            if G.node[vecinos]['dist'] == 9999:
                cola.put(vecinos)
                G.node[vecinos]['dist'] = (G.node[a]['dist'] +1)

def main(entrada='exemple1.dat'):
    """
    Llegeix l'entrada del problema i fa quelcom amb ella.

    Parameters
    ----------

    entrada: string
        Ruta a l'arxiu d'entrada del problema.
    """
    i = 1
    G = llegir_graf(entrada)
    grafs_tresor(G)
    for node in G.nodes(data=True):
        if node[1]['data'] == "treasure":
            if node[1]['dist'] == 9999:
                print "Tresor", i,"al node", node[0], "inaccessible."
                i += 1
            else:
                print "Tresor", i,"al node", node[0], "accessible amb ", node[1]['dist'], "passes."
                i += 1
    print entrada                                                           # Θ(1)

# 
# La complexitat de la funció llegir_graf() és de O(EV+E)
# La complexitat de la funció grafs_tresor() és de O(E) 
#

# Aquest troç és l'encarregat de cridar la funció main amb els paràmetres
# introduïts per consola. No ho podeu modificar.
if __name__ == '__main__':
    main(*sys.argv[1:])

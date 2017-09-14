#!/usr/bin/python
# -*- coding: utf-8 -*-
"""
"""

__author__ = "Astor Prieto"
__email__  = "astorprieto@gmail.com"

import networkx as nx
import sys

def llegir_llista(entrada):
    lista = []

    f = open(entrada, 'r')
    lines = f.readlines()
    f.close()
    
    for line in lines:
        lista.append([int(line.split(',')[0]), int(line.split(',')[1])])
    
    return lista

def motxilla(W, lista):
    K = [0]*(W + 1)
    aux = None

    K[0] = 0
    for w in range(1, (W + 1)):
        for i in range(len(lista)):
            if lista[i][0] <= w:
                aux = K[(w - lista[i][0])] + lista[i][1]
                if aux >= K[w]:
                    K[w] = aux
            print "- ", K[w]

    print K
    return K[W]

def main(entrada='exemple1.dat'):
    """Llegeix l'entrada del problema i fa quelcom amb ella.

    Parameters
    ----------

    entrada: string
        Ruta a l'arxiu d'entrada del problema.
    """
    W = int(input("Input the backpack (W) value: "))
    lista = llegir_llista(entrada)
    max_value = motxilla(W, lista)
    print "Max value in the Backpack: ", max_value


# Aquest troç és l'encarregat de cridar la funció main amb els paràmetres
# introduïts per consola. No ho podeu modificar.
if __name__ == '__main__':
    main(*sys.argv[1:])

# practica7.py (ABB_Astor_Prieto)
#
# Autor: Astor Prieto (niUB16445586)

from S7_Astor_Prieto import User

### CLASS NODO ###
class Node:

    def __init__(self, key = 0, data = None, right = None, left = None):
        self.__key = key
        self.__data = data
        self.__right = right
        self.__left = left

    def getRight(self):
        return self.__right

    def getLeft(self):
        return self.__left

    def setRight(self, node):
        self.__right = node

    def setLeft(self, node):
        self.__left = node

    def hasLSon(self): # Devuelve True si el nodo tiene hijo izquierdo
        if self.__left != None:
            return True
        else:
            return False

    def hasRSon(self): # Devuelve True si el nodo tiene hijo derecho
        if self.__right != None:
            return True
        else:
            return False

### CLASS ARBOL BB ###
class ABB:

    def __init__(self, node = None):
        self.__root = node

    def add(node): # Funcion para introducir un nodo al ABB
        probe = self.__root
        father = None
        self.__add(probe, father, node, node.getKey())

    def __add(self, root, father, node, key): # Funcion privada que lo introduce
        if self.__root = None:
            self.__root = node
        else:
            if root = None:
                father.setLeft(node)
            elif root.getKey > key:
                self.__add(root.getLeft(), root, node, key)
                father.setLeft(node)
            else:
                self.__add(root.getRight(), root, node, key)
                father.setRight(node)

    def postorder(self): # Funcion para mostrar el ABB en postorden
        pass

    def showLeafs(self): # Funcion que muestra una lista con las hojas del ABB
        leafList = []
        self.__showLeafs(leafList, self.__root)

    def __showLeafs(self, leafList, probe): # Funcion privada para showLeafs()
        if probe.hasLSon():
            probe = probe.getLeft()
            self.__showLeafs(leafList, probe)
        elif probe.hasRSon():
            probe = probe.getRight()
            self.__showLeafs(leafList, probe)
        else:
            leafList.append(probe)

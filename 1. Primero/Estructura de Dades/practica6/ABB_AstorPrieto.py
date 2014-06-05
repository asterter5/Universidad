#from Astor_Prieto_ABB_Interface import User

""" CLASS NODE """
class Node:

    def __init__(self, data, left = None, right = None, father = None):
        self.__data = data
        self.__left = left
        self.__right = right
        self.__father = father
    
    def getAll(self):
        return self.__data.getUser()

    def getData(self):
        return self.__data

    def getKey(self):
        return self.__data.getAverage()*100

    def setData(self, data):
        self.__data = data

    def getLeft(self):
        return self.__left

    def setLeft(self, user):
        self.__left = user

    def getRight(self):
        return self.__right

    def setRight(self, user):
        self.__right = user

    def getFather(self):
    	return self.__father

    def setFather(self, user):
    	self.__father = user


""" CLASS ABB """
class ArbolBB:

    def __init__(self):
	self.__root = None

    def search(self, key):
       	return self.__search(key, self.__root)

    def __search(self, key, node):
        if node == None: 
        	return None
        else:
        	if key == node.getKey():
        		return node
        	elif key < node.getKey():
        		return self.__search(node.getLeft(), key)
        	else:
        		return self.__search(node.getRight(), key)

    def add(self, user):
        user = Node(user)
        key = user.getKey()
        self.__add(user, key)

    def __add(self, user, key):
        if self.__root == None:
        	self.__root = user
        else:
        	probe = self.__root
        	if key <= probe.getKey():
        		probe.setLeft(self.__add(probe.getLeft(), key))

        	else:
        		probe.setRight(self.__add(probe.getRight(), key))

    def __hasLSon(self, node):
    	if node.getLeft() != None:
    		return True
    	else:
    		return False

    def __hasRSon(self, node):
    	if node.getRight() != None:
    		return True
    	else:
    		return False

    def __hasSons(self, node):
    	return self.__hasLSon(node) or self.__hasRSon(node)

    def __has2Sons(self, node):
    	return self.__hasLSon(node) and self.__hasRSon(node)

    def __isRoot(self, node):
    	return node.getFather() == None

    def __isLeftSon(self, node):
    	return node.getFather().getLeft() == node

    def __isRightSon(self, node):
    	return node.getFather().getRight() == node

    def remove(self, node):
    	self.__remove(node)

    def __remove(self, node):
    	if not self.__hasSons(node):
    		self.__removeLeaf(node)
    	elif self.__has2Sons(node):
    		self.__removeFather(node)
    	elif self.__hasLSon(node):
    		self.__removeWSon(node, node.getLeft())
    	else:
    		self.__removeWSon(node, node.getRight())

    def __removeLeaf(self, node):
    	if self.__isRoot(node):
    		self.__root = None
    	elif self.__isLeftSon(node):
    		temp = node.getFather().getLeft() 
    		temp = None
    	else:
    		temp = node.getFather().getRight() 
    		temp = None

    def __removeWSon(self, node, son):
    	if self.__isRoot(node):
    		self.__root = son
    		probe = self.__root.getFather() 
    		probe = None
    	elif self.__isLeftSon(node):
    		tnp = node.getFather().getLeft() 
    		tnp = son
    		one = son.getFather() 
    		two = node.getFather()
    		one = two
    	else:
    		tnp = node.getFather().getRight() 
    		tnp = son
    		one = son.getFather() 
    		two = node.getFather()
    		one = two

    def __removeFather(self, node):
    	minNode = self.__srchMinNode(node.getRight())
    	self.__remove(minNode)
    	node.setData(minNode.getData())

    def __srchMinNode(self, node):
    	if node.getLeft() == None:
    		return node
    	else:
    		self.__srchMinNode(node.getLeft())

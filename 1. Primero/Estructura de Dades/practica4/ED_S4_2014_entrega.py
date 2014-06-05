# practica4.py
#
# Autors: Astor Prieto DehghanPour, Laura Ripoll.
#
# coding: utf-8
# S4 Stack  and Queues
# update: 12/03/2014 v.Q16

import string

##############################
# User Class
##############################
class User:
   def __init__(self, uid="None", country="None", mostListenedArtist = ["empty"], artistRelevanceList = ["emptyProducer"]):
      self.__uID = uid
      self.__countr = country
      self.__mostListndArtst = mostListenedArtist
      self.__artRelList = artistRelevanceList

   def getUsrID(self):
      return self.__uID

   def allData(self):
      """ Returns all user data fields generating a concatenated string containing:
      user ID | country | artist most listened | number of times listened | relevance | artist name : relevance | artist name : relevance | etc...
      """
      return self.__uID +" | "+ self.__countr +" | "+ str(self.__mostListndArtst[0]) +" | "+ str(self.__mostListndArtst[1]) +" | "+ str(self.__mostListndArtst[2]) +" | "+ str(self.__artRelList) +" | " 

##############################
# Node, Stack and Queue Classes
##############################
class Node:
   def __init__(self,data = [],next = None):
      self.__data = data
      self.__next = next

   def getVal(self):
      return self.__data

   def setVal(self, val):
      self.__data = val

   def getNext(self):
      return self.__next

   def setNext(self, seg):
      self.__next = seg


class Queue:
   def __init__(self):
      self.__root = None
      self.__seg = None

   def isEmpty(self): 
      if (self.__root == None):
         return True
      else:
         return False

   def printQ(self):
      # Show queue content
      print "-"*10 + "Queue Content: "
      if (self.isEmpty()):
         print "Empty Queue!"
      else:
         actual = self.__root
         while (actual != None):
            print actual.getVal().getUsrID()
            actual = actual.getNext()

   def enqueue(self,node):
      # Add a node to the queue
      if self.isEmpty():
         self.__root = node
         self.__seg = node
      else:
         self.__seg.setNext(node)
         self.__seg = node

   def dequeue(self):      
      # Remove a node from the queue. Return the content of the removed node.
      if self.isEmpty():
         print "Dequeue is not allowed!"
         return User()
      else:
         node = self.__root
         self.__root = self.__root.getNext()
         return node.getVal()


class Stack:
   def __init__(self):
      self.__top = None

   def isEmpty(self):
      if (self.__top == None):
         return True
      else:
         return False
   
   def printStack(self):
      # Show stack content
      print "-"*10 + "Stack Content: "
      actual = self.__top
      if self.isEmpty():
         print "Empty Stack!"
      else:
         while (actual != None):
            print actual.getVal().getUsrID()
            actual = actual.getNext()

   def push(self,node):
      # Add a node to the stack
      if self.isEmpty():
         self.__top = node
      else:
         node.setNext(self.__top)
         self.__top = node

   def pop(self):
      # Remove a node from the stack. Return the content of the removed node.
      if self.isEmpty():
         print "Pop is not allowed!"
         return User()
      else:
         node = self.__top
         self.__top = self.__top.getNext()
         return node.getVal()
 
##############################
# loadUserList Function
##############################
def loadUserList(filename):
   # Create and return a user list as a list of objects of class "User"
   text = open(filename, "r") #Obrim el document
   lines = text.readlines() #I guardem les linies a la variable 'lines'
   text.close()
   newTable = [0 for x in range(100)] #Creem la taula on guardarem la informacio dels usuaris
   i = 0
   
   for users in lines: #Amb aquest bucle for, iterem sobre cada usuari, que equival a una linia
       newUser = [] 
       TableOR = string.split(users, "||") #Dividim el user amb split separant les '||'
       TableAND = string.split(TableOR[2], "&&&") #Fem el mateix amb els '&&&'
       Table100 = string.split(TableOR[3], "&&&")
       nTable100 = [] #Aquesta es una tabla temporal on guardem la llista de artistes escoltats
       
       for elem in Table100: #Amb aquesta iteracio dividim els '%%' i els incloim a la llista de artistes
           nElem = elem.split("%%") 
           nTable100.append(nElem)
       for j in range(2): #Guardem a la nostra taula de usuaris les dades aprofitables dels primers camps (ID i Pais)
           newUser.append(TableOR[j])
       #I en aquest guardem tota la informacio del seu artista preferit (Nom, Plays i mitja)
       newUser.append(TableAND)
       newUser.append(nTable100)
       newTable[i] = newUser#Finalment incloiem la llista de artistes escoltats al final de la taula final
       i += 1
   #Repetim per a cada usuari fins a acabar

   usrList = []
   usrList = sorted(newTable, key = lambda newTable: newTable[0])
   usrList = [User(camp[0], camp[1], camp[2], camp[3]) for camp in newTable]
   return usrList

############################## 
# MAIN
##############################
def main():
   
   # Load data
   userList=loadUserList("dadesED2014-100.txt")
   
   # Show data loaded 
   print "First Usr:\n", userList[0].allData()		
   print "Segond Usr:\n", userList[1].allData()		
  
   # Code to test the STACK class
   print '\n' + "*"*10 + "Going to check STACK:" + '\n'
   newStack = Stack()				                 # new stack creation
   newStack.printStack()		                 # show stack content
   newNode = Node(userList[0])	      # load 1st item in a new node
   newStack.push(newNode)					# add node to the stack
   newStack.printStack()							# show stack content
   
   newStack.push(Node(userList[1]))	# load 2nd item in a new node
   newStack.printStack()

   newStack.push(Node(userList[2]))	# load 3rd item in a new node
   newStack.printStack()

   m1 = newStack.pop()			# remove an element from stack
   newStack.printStack()

   m2 = newStack.pop()			# remove an element from stack
   newStack.printStack()

   m3 = newStack.pop()			# remove an element from stack
   newStack.printStack()

   m4 = newStack.pop()		   # remove an element from stack
   newStack.printStack()	

   print "Deleted elements from the stack:"
   print m1.getUsrID() 
   print m2.getUsrID()
   print m3.getUsrID()
   print "and now GUESS WHAT HAPPENS...:"
   print m4.getUsrID()  

   # Code to test the QUEUE class
   print '\n' + "*"*10 + "Going to check QUEUE:" + '\n'
   newQ = Queue()
   newQ.printQ()

   newNode = Node(userList[0])
   newQ.enqueue(newNode)
   newQ.printQ()

   newQ.enqueue(Node(userList[1]))
   newQ.printQ()

   newQ.enqueue(Node(userList[2]))
   newQ.printQ()

   n1 = newQ.dequeue()
   newQ.printQ()

   n2 = newQ.dequeue()
   newQ.printQ()

   n3 = newQ.dequeue()
   newQ.printQ()

   n4 = newQ.dequeue()
   newQ.printQ()

   print "Deleted elements from the stack:"
   print n1.getUsrID()
   print n2.getUsrID()
   print n3.getUsrID()
   print "and now GUESS WHAT HAPPENS...:"
   print n4.getUsrID()

if __name__ == "__main__":
   main()


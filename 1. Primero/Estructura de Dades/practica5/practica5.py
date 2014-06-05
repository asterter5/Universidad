# practica5.py
#
# Autor: Astor Prieto DehghanPour (aprietde10)

from Tkinter import *
import string

# CLASS NODE AND QUEUE #

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

# CLASS PARSER AND USER #

def parser():
    text = open("dadesED2014-100.txt", "r") #Obrim el document
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
              
    return newTable
  
class User:
  
    def __init__(self, uid = "", pais = "", bestartist = [], allartists = []):
        self.__uID = uid
        self.__country = pais
        self.__bestArtist = bestartist
        self.__allArtists = allartists
       
    def __str__(self):
        # Here write the overload of the string output that returns a concatenated string containing
        # user ID | country | artist most listened | number of artists listened
        return self.__uID," | ", self.__country," | ", self.__bestArtist[0]," | ", str(len(self.__allArtists))
  
    def getUser(self):
        return (self.__uID, self.__country, self.__bestArtist, self.__allArtists)

class TkInterApp:

    def __init__(self, userList):
        self.__users = userList
        self.__count = 0
        root = Tk()
        root.title("Users")
        root.geometry("500x300")
        usrButt = Frame(root)
        usrTxt = Frame(root)
        usrDisplay = Frame(root)
        srchFrom1 = Frame(root)
        srchTo1 = Frame(root)
        srchFrom2 = Frame(root)
        srchTo2 = Frame(root)
        srchButt = Frame(root)
        costs = Frame(root)
        
        usrButt.pack()
        usrButt.place(x=40, y=70)
        usrTxt.pack()
        usrTxt.place(x=30, y=130)
        usrDisplay.pack()
        usrDisplay.place(x=190, y=130)
        costs.pack()
        costs.place(x=400, y=110)
        srchFrom1.pack()
        srchFrom1.place(x=130, y=227)
        srchFrom2.pack()
        srchFrom2.place(x=220, y=230)
        srchTo1.pack()
        srchTo1.place(x=130, y=247)
        srchTo2.pack()
        srchTo2.place(x=220, y=250)
        srchButt.pack()
        srchButt.place(x=220, y=272)

        
        addButt = Button(usrButt, text = "ADD", command = self.__addUser())
        nextButt = Button(usrButt, text = "NEXT", command = self.__nextUser())
        srchButt = Button(srchButt, text = "SEARCH", command = self.__searchAverage())
        viewInf = Label(usrTxt, text = "UserID: \nCountry: \nArtist: \nRelevance: ")
        viewCost1 = Label(costs, text = "ADDING cost: \nXXX")
        viewCost2 = Label(costs, text = "SEARCHING cost: \nXXX")
        addButt.pack()
        nextButt.pack()
        viewInf.pack()
        viewCost1.pack()
        viewCost2.pack()

        fromAverage = Label(srchFrom1, text = "From Average: ")
        fromAverage.pack()
        toAverage = Label(srchTo1, text = "To Average: ")
        toAverage.pack()
        
        e1 = Entry(srchFrom2, textvar = fromAverage)
        e2 = Entry(srchTo2, textvar = toAverage)
        e1.pack()
        e2.pack()
        srchButt.pack()
        
        self.__view = Label(usrDisplay, text = "Start picking an Option.")
        self.__view.pack()
        root.mainloop()

    def __addUser(self):
        pass

    def __nextUser(self):
        user = self.__users[self.__count].getUser()
        self.__view["text"] = user[0]+ "\n"+ user[1]+ "\n"+ user[2][0]+ "\n"+ user[2][2]
        self.__count += 1

    def __searchAverage(self):
        pass
    
    
# SCRIPT #
lista = []
lista = parser()
listaLast = sorted(lista, key = lambda lista: lista[0])
listaLast = [User(camp[0], camp[1], camp[2], camp[3]) for camp in listaLast]
LastFM = TkInterApp(listaLast) 

# practica5.py
#
# Autor: Astor Prieto DehghanPour (aprietde10)

from Tkinter import *
from ABB_AstorPrieto import Node
from ABB_AstorPrieto import ArbolBB
import string
import time

# CLASS PARSER AND USER #


def parser(txt):
    text = open(txt, "r") #Obrim el document
    lines = text.readlines() #I guardem les linies a la variable 'lines'
    text.close()
    newTable = [0 for x in range(100000)] #Creem la taula on guardarem la informacio dels usuaris
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
        newTable[i] = newUser #Finalment incloiem la llista de artistes escoltats al final de la taula final
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

    def getAverage(self):
        return self.__bestArtist[2]

    def getUID(self):
        return self.__uID

    def getUser(self):
        return [self.__uID, self.__country, self.__bestArtist[0], self.__allArtists[2]]

class AppFunc:

    def __init__(self):
        self.__usrL = parser("dadesED2014-100000.txt")
        self.__displayAll = False
        self.__dspU = None
        self.__abb = ArbolBB()
        self.__actual = 0
        self.__addT = None
        self.__searchT = None

    def add(self):
        t0 = time.time();
        crtL = self.__usrL[0:1999]
        for x in crtL:
            self.__abb.add(x)
        self.__usrL = self.__usrL[2000:]
        self.__addT = time.time() - t0
        self.__displayAll = True
        self.__abb.setRange()
        self.__all = iter(self.__abb)
        self.__dspU = self.__all.next() 

    def getAddT(self):
        return self.__addT

    def getSearchT(self):
        return self.__searchT

    def search(self,bg,nd):
        bg = float(bg)
        nd = float(nd)
        t0 = time.time()
        tmp = self.__abb
        tmp.setRange(bg, nd)
        self.__itrCerca = iter(tmp)
        self.__searchT = time.time() - t0
        self.__displayAll = False
        self.__dspU = self.__itrCerca.next()

    def getRemoveT(self):
        return self.__removeT

    def remove(self, bg, nd):
        t0 = time.time()
        self.search(bg, nd)
        for x in self.__itrCerca:
            self.__abb.remove(x)
        self.__abb.setRange()   
        self.__all = iter(self.__abb)
        self.__dspU = self.__all.next()
        self.__abb.remove(self.__dspU)
        self.__removeT = time.time() - t0
        self.__dspU = self.__all.next()
        self.__displayAll = True

    def getDspU(self):
        if (self.__dspU != None):
            return self.__dspU.getAll()
        else:
            return ["","","",""]

    def displayNext(self):
        if self.__displayAll:
            self.__dspU = self.__all.next()
        else:
            try:
                self.__dspU = self.__itrCerca.next()
            except:
                self.__displayAll = True


class TkInterApp:

    def __init__(self):

        self.__lfa = AppFunc()

        root = Tk()
        root.title("Users")
        root.geometry("550x350")
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
        usrButt.place(x=30, y=50)
        usrTxt.pack()
        usrTxt.place(x=30, y=140)
        usrDisplay.pack()
        usrDisplay.place(x=190, y=140)
        costs.pack()
        costs.place(x=430, y=110)
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
        remButt = Button(usrButt, text = "REMOVE", command = self.__removeUser())
        srchButt = Button(srchButt, text = "SEARCH", command = self.__searchAverage())
        viewInf = Label(usrTxt, text = "UserID: \nCountry: \nArtist: \nRelevance: ")
        viewCost1 = Label(costs, text = "ADDING cost: \nXXX")
        viewCost2 = Label(costs, text = "SEARCHING cost: \nXXX")
        viewCost3 = Label(costs, text = "REMOVING cost: \nXXX")
        addButt.pack()
        nextButt.pack()
        remButt.pack()
        viewInf.pack()
        viewCost1.pack()
        viewCost2.pack()
        viewCost3.pack()

        fromAverage = Label(srchFrom1, text = "From Average: ")
        fromAverage.pack()
        toAverage = Label(srchTo1, text = "To Average: ")
        toAverage.pack()
        
        e1 = Entry(srchFrom2, textvar = fromAverage)
        e2 = Entry(srchTo2, textvar = toAverage)
        e1.pack()
        e2.pack()
        srchButt.pack()
        
        userDisplay = Label(usrDisplay, text = "Start picking an Option.")
        userDisplay.pack()
        root.mainloop()

    def __addUser(self):
        self.__lfa.add()
        tmp = "ADDING COST: \n"+str(self.__lfa.getAddT())
        viewCost1.set(tmp)
        self.setPublicU()

    def __searchAverage(self):
        t1 = e1.get()
        t2 = e2.get()
        if (t1 == ""):t1 = 0
        if (t2 == ""):t2 = 1
        self.__lfa.search(t1,t2)
        tmp = "SEARCHING COST: \n"+ str(self.__lfa.getSearchT())
        viewCost2.set(tmp)
        self.setPublicU()

    def __nextUser(self):
        self.__lfa.displayNext()
        self.setPublicU()

    def setPublicU(self):
        userDisplay.set(self.__lfa.getDspU()[0] + "\n" + self.__lfa.getDspU()[1] + "\n" + self.__lfa.getDspU()[2] + "\n" + str(self.__lfa.getDspU()[3]))

    def __removeUser(self):
        t1 = e1.get()
        t2 = e2.get()
        if (t1 == ""):t1 = 0
        if (t2 == ""):t2 = 1
        self.__lfa.remove(t1,t2)
        tmp = "REMOVING COST: \n"+ str(self.__lfa.getRemoveT())
        viewCost3.set(tmp)
        self.setPublicU()
    
lf = TkInterApp()
# SCRIPT #
# lista = []
# lista = parser("dadesED2014-100.txt")
# listaLast = sorted(lista, key = lambda lista: lista[0])
# listaLast = [User(camp[0], camp[1], camp[2], camp[3]) for camp in listaLast]
# LastFM = TkInterApp(listaLast) 

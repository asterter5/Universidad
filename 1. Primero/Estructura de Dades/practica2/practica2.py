# practica2.py
#
# autors: Astor Prieto DehghanPour, Laura Ripoll

from Tkinter import *
import string
import random

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


# BUILDING GUI    
class tkInterTest:
    
    def __init__(self):

        root = Tk()
        logoUB = PhotoImage(file="./logoub.gif")
        w = logoUB.width()
        h = logoUB.height()
        newCanvas=Canvas(root, width=w,height=h, background='white')
        newCanvas.create_image(w/2 + 1,h/2 + 0.5,image=logoUB)
        newCanvas.pack()
        IMG = Label(root, text = "The image is\n " + str(w) + " x "+ str(h))
        IMG.pack()
        root.minsize(w,h)
        root.mainloop()

class LastFM:
    
    def __init__(self, userList):

        ## GENERATE 1) Tk init object 2) Frame 2) Buttons 2) Labels as in Figure 1. Please use Grid 
        self.__nowUser = userList
        self.__count = 0
        root = Tk()
        butt = Frame(root)
        usr = Frame(root)
        butt.pack(side = LEFT)
        usr.pack(side = RIGHT)
        #Se crean dos botones, uno para la lista ordenada y otro para el boton de user aleatorio
        nextButt = Button(butt, text = "ORDERED", command = self.__nextUser)
        randButt = Button(butt, text = "RANDOM", command = self.__randUser)
        self.__view = Label(usr, text = "Start Picking an Option")

        #Todo Pack y se inicia el loop
        nextButt.pack()
        randButt.pack()
        self.__view.pack()
        root.mainloop()

    #Funcion para el siguiente user ordenado, simplemente sumando 1 al contador
    def __nextUser(self):
        user = self.__nowUser[self.__count].getUser()
        self.__view["text"] = "uID: "+ user[0]+ "\nCountry: "+ user[1]+ "\nMost Played Artist: "+ user[2][0]+ "\nMPA Relevance: "+ user[2][2]+ "\nNumber of Artists Played: "+ str(len(user[3]))
        self.__count += 1

    #Funcion para el siguiente user random, se genera un int aleatorio dentro de la lista
    def __randUser(self):
        self.__count = int(random.random() * len(self.__nowUser))
        user = self.__nowUser[self.__count].getUser()
        self.__view["text"] = "uID: "+ user[0]+ "\nCountry: "+ user[1]+ "\nMost Played Artist: "+ user[2][0]+ "\nMPA Relevance: "+ user[2][2]+ "\nNumber of Artists Played: "+ str(len(user[3]))

# Script starts HERE
lista = []
lista = parser()
listaLast = sorted(lista, key = lambda lista: lista[0])
listaLast = [User(camp[0], camp[1], camp[2], camp[3]) for camp in listaLast]
LastFM = LastFM(listaLast)
# Create a user list as a list of objects of type "User"
# using dadesED2014-100.txt
# run the interface

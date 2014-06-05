# practica7.py (S7_Astor_Prieto)
#
# Autor: Astor Prieto (niUB16445586)

from ABB_Astor_Prieto import Node
from ABB_Astor_Prieto import ABB
import string

def parser(txt): # Funcion que parsea el archivo 'dadesED2014-100.txt'

    lines = open(txt, "r")
    text = lines.readlines()
    lines.close()
    tablaOR = []
    tablaAND = []
    tabla100 = []
    newTable = []
    for user in text:
        tablaOR = string.split(user, "||")
        tablaAND = string.split(tablaOR[2], "&&&")
        tabla100 = string.split(tablaOR[3], "&&&")
        
        tabla = []
        tabla.append(tablaOR[0])
        tabla.append(tablaOR[1])
        tabla.append(tablaAND[0])
        tabla.append(tablaAND[2])
        newTable.append(tabla)
        
    return newTable


### CLASS USER ###
class User:

    def __init__(self, uID = None, country = None, bestArtist = None, favAverage = None):
        self.__uID = uID
        self.__country = country
        self.__bestArtist = bestArtist
        self.__favAverage = favAverage

    def getKey(self): # Funcion que toma la clave del average del user
        return self.__favAverage * 100

    def getUser(self):
        return self.__uID + self.__country + self.__bestArtist + str(self.__favAverage)

    def __str__(self):
        return "User: " + self.__uID +", "+ self.__country +", "+ self.__bestArtist +": "+ str(self.__favAverage)

### SCRIPT MAIN ###    
def main():

    arbolBB = ABB()
    userList = []
    listaUsers = parser("dadesED2014-100.txt")
    for user in listaUsers:
        userList.append(User(user[0], user[1], user[2], user[3]))

    for user in userList:
        arbolBB.add(Node(user.getKey(), user))

    arbolBB.postorder()
    arbolBB.showLeafs()
    
print main()

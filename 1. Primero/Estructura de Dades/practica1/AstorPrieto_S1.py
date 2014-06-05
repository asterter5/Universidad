# practica1.py
#
# autor: Astor Prieto (aprietde10)

import string

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

def main():
    estructuraDatos = []
    estructuraDatos = parser()
    for campo in estructuraDatos:
        print campo, "\n"
main()

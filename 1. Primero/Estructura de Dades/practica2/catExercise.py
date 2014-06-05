# coding: utf-8

class Pussa:
        ''' Class Pussa '''
        # (a) Define a private attribute idPussa
        def __init__(self, idx):
                self.__idPussa = idx
        
        # (b) Define a __str__ method that 
        def __str__(self):
                return str(self.__idPussa)
        
        # (c) Define setIdPussa
        def setIdPussa(self, idx):
                self.__idPussa = idx
        
        # (c) Define getIdPussa
        def getIdPussa(self):
                return self.__idPussa
                
class Cat:
        ''' Class cat '''
        # (a) Define the init method with a private attribute called catNum and a list of pusses
        def __init__(self, nombre):
                self.__catNum = nombre
                self.__listPussa = []
                
        # (b) Define the mixeta method
        def mixeta(self):
                print "Miau!", self.__catNum
                print "Pusses:", len(self.__listPussa)
                for i in self.__listPussa:
                        puss = i.getIdPussa()
                        print "idP:",puss
                print
        
        # (c) Define the setter function for catNum
        def setCatNum(self, idx):
                self.__catNum = idx
                
        # (c) Define the getter function for catNum             
        def getCatNum(self):
                return self.__catNum
        
        # (d) Define a setter for adding a Pussa in the list of pusses
        def addPussa(self, pussa):
                self.__listPussa.append(pussa)
        
        # (e) Define the cleanCat method which removes all pusses from the cat, empty the list
        def cleanCat(self):
                self.__listPussa = []
        
        # (f) Define the contageousCat method
        def contageousCat(self):
                newPusses = []
                for i in self.__listPussa:
                        puss1 = Pussa(i.getIdPussa() * 10 + 1)
                        puss2 = Pussa(i.getIdPussa() * 10 + 2)
                        newPusses.append(puss1)
                        newPusses.append(puss2)
                return newPusses
        
def main():

        # (a) Define a new list of 10 cats
        cats = []
        for i in range(10):
                cats.append(Cat(i + 1))
        
        # (b) Salute all cats by calling mixeta method
        print
        print "Start first salutation"
        for cat in cats:
                cat.mixeta()
                
        # (c) Copy the first 5 cats to another list (secondCatList)
        secondCatList = []
        for i in range(5):
                secondCatList.append(cats[i])
        
        # (d) Add 10 to the cat number on each Cat object on secondCatList
        for cat in secondCatList:
                cat.setCatNum(cat.getCatNum() + 10)

        # (e) Salute all cats on cats list with mixeta method
        print
        print "Start second salutation"
        for cat in cats:
                cat.mixeta()

        # EXPLAIN THE OUTPUT:
        # Se ha copiado la referencia de la lista, por lo que al cambiar
        # El CatNum, se ha cambiado tambien en la lista original

        
        # (f)  Now, our cats get a "Pussa" infection. Put 4 Pussa objects on all even-index cats on the list cats. 
        # First generate the 20 needed Pussa objects with consecutive numbers. 
        # Then copy the references of the Pussa objects to the corresponding cats.
        pusses = []
        pussaNum = 0
        for i in range(20):
                pusses.append(Pussa(i + 1))
        for i in [0, 2, 4, 6, 8]:
                cats[i].addPussa(pusses[pussaNum])
                pussaNum += 1
                cats[i].addPussa(pusses[pussaNum])
                pussaNum += 1
                cats[i].addPussa(pusses[pussaNum])
                pussaNum += 1
                cats[i].addPussa(pusses[pussaNum])
                pussaNum += 1
        
        # (g) Salute the cats on the first list (cats) and see that the changes done in secondCatList affected also the cats list.
        print
        print "Salute with infection"
        for cat in cats:
                cat.mixeta()
                
        # EXPLAIN THE OUTPUT:
        # Se han infectado todos los gatos impares
        # Por cada gato impar tenemos 4 pussas ahora

        
        # (h) The infected cats infect all the other cats!! 
        for i in [0, 2, 4, 6, 8]:
                nP = cats[i].contageousCat()
                for pussa in nP:
                        cats[i+1].addPussa(pussa)
        
        # (i) Show the disaster
        print
        print "Salute with spreaded infection"
        for cat in cats:
                cat.mixeta()

        # EXPLAIN THE OUTPUT:
        # El metodo contageousCat ha creado 2 pussas por cada pussa existente
        # Los gatos pares se han contagiado con las nuevas pussas (8 por cada uno)

        
        # (j) Clean all cats with cleanCat method
        for cat in cats:
                cat.cleanCat()
                
        # (k) Salute all cats. Note that all Pussa objects are still alive on the pusses list, but are not referenced inside Cat objects anymore.
        print "Salute after cleaning"
        for cat in cats:
                cat.mixeta()

        # EXPLAIN THE OUTPUT:
        # Gracias al metodo cleanCat, ahora las listas de pussas de cada
        # gato estan vacias, es decir, los gatos estan limpios.
        
        # (l)Print the Pussa objects
        print "Printing the Pussa objects on the pusses List"
        for puss in pusses:
                print "Puss num: ", puss

        # EXPLAIN THE OUTPUT:
        # La lista sigue llena de pusses, pero ya no estan relacionadas
        # con ningun gato

        
        print "END of Exercise 1"
                 
main()
        
        
        

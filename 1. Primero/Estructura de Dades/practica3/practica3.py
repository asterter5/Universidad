# -*- coding: cp1252 -*-
# practica3.py
#
# @author: Astor Prieto DehghanPour (aprietde10)


#Definimos la clase Momento, con todos sus atributos
class Momento:

    #Creamos el constructor de la clase, dando por defecto el momento 000 00 AM
    def __init__(self, dia = 0, mes = 0, anyo = 0, hora = 0, minuto = "00"):
        self.__dia = dia
        self.__mes = mes
        self.__anyo = anyo
        self.__hora = hora
        self.__minuto = minuto
        self.__zona_horaria = "AM"

    #Sobrecargamos el metodo__str__ para imprimir en el formato adecuado
    def __str__(self):
        return "["+ str(self.__dia) +"-"+ str(self.__mes) +"-"+ str(self.__anyo) +" "+ str(self.__hora) +":"+ str(self.__minuto) +" "+ self.__zona_horaria +"]"

    #Definimos getter para el atributo minuto
    def getMinuto(self):
        return self.__minuto
    #Definimos setter para el atributo minuto
    def setMinuto(self, n):
        self.__minuto = n

#Definimos la clase Evento, que contiene un Nombre, un Momento de inicio, y una duracion
class Evento:

    #El constructor de la clase, que toma por defecto el Evento ("", 000 00 AM, 0)
    def __init__(self, nombre = "", inicio = Momento(), duracion = 0):
        self.__nombre = nombre
        self.__inicio = inicio
        self.__duracion = duracion

    #Getter para el parametro Nombre
    def getNombre(self):
        return self.__nombre

    #Metodo para posponer n minutos la hora del inicio del evento
    def posponer(self, n):
        (self.__inicio).setMinuto((self.__inicio).getMinuto() + n)

    #Sobrecargamos el metodo __str__ para obtener el Evento en el formato deseado
    def __str__(self):
        return "Nombre: "+ self.__nombre +", Inicio: "+ str(self.__inicio) +", Duracion: "+ str(self.__duracion)

    #Sobrecargamos el metodo __cmp__ para que compare el atributo Duracion de cada evento
    def __cmp__(self, other):
        if (self.__duracion < other.__duracion):
            return -1
        elif(self.__duracion == other.__duracion):
            return 0
        else:
            return 1

    #Getter para el atributo Duracion
    def getDuracion(self):
        return self.__duracion

    #Setter para el atributo Duracion
    def setDuracion(self, newDur):
        self.__duracion = newDur

    #Metodo para comprobar si la duracion de un evento dura mas que minutos tiene un dia (1440 min)
    def terminaMismoDia(self):
        if (self.__duracion >= 1440):
            return True
        else:
            return False

#Funcion que suma 60 minutos a la duracion de un evento si esta pasa de 120
def posponeEventosExtensos(agenda):
    for camp in agenda:
        if (camp.getDuracion() > 120):
            camp.setDuracion((camp.getDuracion()) + 60)
    return agenda

#Evento que comprueba y imprime si un evento va a durar mas que un dia entero
def terminaMismoDia(agenda):
    for camp in agenda:
        if camp.terminaMismoDia():
            print camp.getNombre() +", SI."
        else:
            print camp.getNombre() +", NO."

#MAIN
def main():

    #Creamos agenda1 y los cuatro eventos iniciales, luego añadimos a agenda1
    agenda1 = []
    ev1 = Evento("ClaseA", Momento(25, 03, 2014, 12), 100)
    ev2 = Evento("Practicas", Momento(24, 03, 2014, 11), 100)
    ev3 = Evento("Cena", Momento(24, 03, 2014, 22), 150)
    ev4 = Evento("Conferencia", Momento(25, 03, 2014, 16), 120)
    agenda1.append(ev1)
    agenda1.append(ev2)
    agenda1.append(ev3)
    agenda1.append(ev4)

    #Primera llamada a Agenda1
    print "******** 2. Contenido de la Agenda ********\n"
    for camp in agenda1:
        print camp
    print "\n"

    #Modificamos la duracion del segundo evento
    ev2.setDuracion(180)

    #Segunda llamada a Agenda1
    print "******** 3. Contenido de la Agenda ********\n"
    for camp in agenda1:
        print camp
    print "\n"

    #Llamamos al metodo posponeEventosExtensos sobre Agenda1
    posponeEventosExtensos(agenda1)

    #Tercera llamada a Agenda1
    print "******** 4. Contenido de la Agenda ********\n"
    for camp in agenda1:
        print camp
    print "\n"

    #Creamos una agenda2 y volcamos el contenido de la primera, para despues ordenarla
    agenda2 = []
    for camp in agenda1:
        agenda2.append(camp)
    agenda2.sort()

    #Primera llamada a Agenda2 (Agenda1 ordenada segun Duracion)
    print "******** 5. Contenido de la Agenda ********\n"
    for camp in agenda2:
        print camp
    print "\n"

    #Llamada al metodo terminaMismoDia para comprobar los eventos de Agenda1
    print "******** 6. Evento - Termina el mismo Dia (SI/NO) ********\n"
    terminaMismoDia(agenda1)
    
#end
main()
    

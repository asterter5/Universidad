#prova.py
#
#autor: Astor Prieto (aprietde10)

import string

def separa_frase(frase):
    lista_nums = [] #Creamos dos listas vacias donde guardaremos los numeros por 
    lista_words = [] #un lado y las letras por otro lado
    suma = 100 #Inicializamos donde se guardara nuestra suma
    frase = string.split(frase, chr(95)) #Separamos la frase en una lista
    for word in frase:
        if (word >= chr(48) and word <= chr(57)): #por cada elemento de la frase discernimos si es un numero 
            lista_nums.append(word)
        else: #o si es una palabra a contar
            lista_words.append(word)
    for num in lista_nums: #Una vez separados, hacemos la suma de los elementos de lista_nums
        suma += eval(num) 
    print lista_words
    print lista_nums
    print string.join(frase, chr(95)), (suma - 100)

def ascii_hex(char):
    conv = ord(char[0]) #tomamos un caracter como parametro y lo convertimos a su valor ordinal
    hexa = hex(conv) #con su valor ordinal de ascii, lo pasamos a su numero hexadecimal
    return string.upper(hexa[2]+hexa[3]) #devolvemos solo los caracteres significativos del numero hexadecimal

def write_ascii_hex(frase):
    nueva = "" #Creamos una string donde se guardara nuestra frase en hexadecimal
    for lletra in frase: #por cada caracter de la frase pasada como parametro
        hexa = ascii_hex(lletra) #ejecutamos la funcion anterior para convertirlo
        nueva = nueva + hexa + " " #y anadimos los caracteres convertidos al nuevo string
    file = open("output.txt", "w")
    file.write(nueva)
    print "Consulta el fitxer output.txt"
    file.close()

phase = "45_mas_21_es_igual_a"
separa_frase(phase)
print
ejemplo = ascii_hex('n')
print ejemplo
print
write_ascii_hex("Hola")

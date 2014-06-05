from practica6 import User
from practica6 import Parser
from ABB_AstorPrieto import ArbolBB
from ABB_AstorPrieto import Node


#Test
llistaUsuaris = parser("dadesED2014-100.txt")
ABB = ArbolBB()
for x in llistaUsuaris:
    ABB.add(x)
tmp = iter(ABB)
print tmp.next().getKey()
print tmp.next().getKey()
print tmp.next().getKey()
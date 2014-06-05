.data 30

pila:

.org 500H
	LXI H, pila
	SPHL
	call puertos
NOP
HLT

puertos:
	PUSH PSW
	in 00h
	ANI 00000001
	out 05h
	POP PSW
Ret
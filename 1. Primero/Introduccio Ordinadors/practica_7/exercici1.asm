.data 40h
	buffer: db 00h, E0h

.org 100h
inici:
	JMP inici
HLT

.org 24h
	LHLD buffer
	IN 00h
	MOV M, A
	INX H
	SHLD buffer
ret
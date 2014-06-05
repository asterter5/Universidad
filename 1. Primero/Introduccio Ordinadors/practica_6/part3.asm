.define
	cero 77h
	uno 44h
	dos 3Eh
	tres 6Eh
	cuatro 4Dh
	cinco 6Bh

.data 40h
	buffer: db 00h, 07h

.org 100h
inici:
	JMP inici

borrado:
	MVI A, 00h
	OUT 00h
	SHLD buffer
	JMP inici

ncero:
	MVI A, cero
	OUT 00h
	SHLD buffer
	JMP inici
nuno:
	MVI A, uno
	OUT 00h
	SHLD buffer
	JMP inici
ndos:
	MVI A, dos
	OUT 00h
	SHLD buffer
	JMP inici
ntres:
	MVI A, tres
	OUT 00h
	SHLD buffer
	JMP inici
ncuatro:
	MVI A, cuatro
	OUT 00h
	SHLD buffer
	JMP inici
ncinco:
	MVI A, cinco
	OUT 00h
	SHLD buffer
	JMP inici

interrupcio:
	LHLD buffer
	IN 00h
	MOV M, A
	SUI 30h
	JZ ncero
	ADI 30h
	SUI 31h
	JZ nuno
	ADI 31h
	SUI 32h
	JZ ndos
	ADI 32h
	SUI 33h
	JZ ntres
	ADI 33h
	SUI 34h
	JZ ncuatro
	ADI 34h
	SUI 35h
	JZ ncinco
	ADI 35h
	SUI 63h
	JZ borrado
ret

HLT

.org 24h
	JMP interrupcio
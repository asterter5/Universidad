
Contador: .dW 5
Valor1: .dW 6
Resultat: .rW 1
.begin Inici
Inici:
	ADD R0,R0,R1
	SUB R0,R0,R2
	LOAD Contador(R0), R3
	LOAD Valor1(R1), R2
Loop:
	ADD R1, R2,R1
	SUBI R3, #1,R3
	BG Loop
	STORE R1, Resultat(R0)
.end
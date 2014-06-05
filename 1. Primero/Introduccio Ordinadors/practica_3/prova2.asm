Contador: .dW 19
Valor1: .dW 32760
Resultat: .rW 1
Mascara: .dw 32767
.begin Inici
Inici:
	ADD R0,R0,R1
	SUB R0,R0,R2
	LOAD Contador(R0),R3
	LOAD Valor1(R1),R2
	LOAD Mascara(R0),R7
Loop:
	ADD R1,R2,R1
	BL Overflow
Ret:
	SUBI R3,#1,R3
	BG Loop
	BR End
Overflow:
	AND R1,R7,R1
	ADDI R5,#1,R5
	BR Ret
End:
	STORE R1, Resultat(R0)
.end
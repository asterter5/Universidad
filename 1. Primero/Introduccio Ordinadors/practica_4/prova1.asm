guardaResultat: .rw 1
.begin start
start:
	ADD R0,R0,R3
	ADD R0,R0,R7
	ADDI R0, #4, R2
	ADD R2, R3, R3
	SUBI R7, #1,R7
	BG salto
salto: 	
	STORE R3, guardaResultat(R0)
.end
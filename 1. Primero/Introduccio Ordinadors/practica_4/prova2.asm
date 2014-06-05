valorDada: .dw 7
guardaResultat: .rw 1
.begin start
start: 
	LOAD valorDada(R0), R1
	ADDI R0, #9, R2
	ADD R0, R0, R3
loop: 
	ADD R2, R3, R3
	SUBI R7, #1,R7
	BG loop
	STORE R3, guardaResultat(R0)
.end
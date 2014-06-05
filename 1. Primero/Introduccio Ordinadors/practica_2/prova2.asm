Dades: .dw 4, 5, 6, 7  
.begin inici		;directiva de inici de programa
inici:			;inici de programa
	SUB R7, R7, R7
	LOAD Dades(R0), R1
	ADDI R7, #1, R7
	LOAD 0(R7), R2
	ADDI R7, #1, R7
	LOAD 0(R7), R3
	ADDI R7, #1, R7
	LOAD 0(R7), R4
loop:
	ADD R1, R2, R5
	ADD R3, R4, R6
	SUBI R3,#1, R3
	BG loop
.end 			;directiva final de programa
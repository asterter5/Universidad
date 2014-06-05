A: .dw 50
B: .dw 50
.begin inici		;directiva de inici de programa
inici:			;inici de programa
	LOAD A(R0), R1
	LOAD B(R0), R2
loop:
	SUB R2, R1, R0 
	BG 9
	BEQ 10
	ADD R1, R2, R3
	BR 10
	SUB R2, R1, R3
.end 			;directiva final de programa
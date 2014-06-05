dada1: .dw 3083
dada2: .dw 17
.begin inici		;directiva de inici de programa
inici:			;inici de programa
	LOAD dada1(R0), R1
	LOAD dada2(R0), R2
loop:
	ADD R7, R1, R7
	SUBI R2,#1, R2
	BG loop
.end 			;directiva final de programa
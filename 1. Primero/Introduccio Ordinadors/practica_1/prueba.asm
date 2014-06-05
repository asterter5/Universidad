dades: .dw 3, 5, 2, 8
reserva: .rw 1

.begin iniciPrograma

iniciPrograma:

	SUB r1, r1, r1
	ADD r0, r0, r2
	SUBI r1, #4, r0
	BEQ 13
	LOAD 0(r1), r3
	ADD r3, r2, r2
	ADDI r1, #1, r1
	BR 07
	STORE r2, 4(r0)

.end
.define
	num 4
.data 00h
	mat1: db 1, 2, 3, 4, 5
	mat2: db 6, 7, 8, 9, 0
	mat3: db 0, 0, 0, 0, 0	
.org 100h
	LXI H, mat1 
	LXI B, mat3 
	MVI D, num

bucle1: ;BUCLE PER A GUARDAR MAT1 A MAT3
	MOV A, M
	STAX B ;Guardem al valor 1 de mat3 el Acc
	INX H
	INX B
	DCR D
	JP bucle1
	
	LXI B, mat3 ;Recarreguem els valors de mat3
	MVI D, num ;Reset del iterador

bucle2: ;BUCLE PER A SUMAR MAT2 A MAT3
	MOV E, M
	LDAX B
	ADD E
	STAX B ;Guardem al valor 1 de mat3 el Acc
	INX H
	INX B
	DCR D
	JP bucle2
	
;	CALL subrutina
;
;subrutina:
;	POP B
;	POP D
;	POP H
;	RET
HLT
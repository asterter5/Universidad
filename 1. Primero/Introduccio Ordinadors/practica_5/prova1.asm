.define
	num 4
.data 00h
	mat1: db 1, 2, 3, 4, 5
	mat2: db 6, 7, 8, 9, 0
	mat3: db 0, 0, 0, 0, 0	
.org 100h
	LXI H, mat1 ;HL <= 00
	LXI B, mat2 ;BC <= 05
	MVI D, num
bucle:
	MOV E, M
	LDAX B ;Carreguem a Acc el valor 1 de mat2
	ADD E
	STAX B ;Guardem al valor 1 de mat2 el Acc
	INX H
	INX B
	DCR D
	JP bucle
HLT
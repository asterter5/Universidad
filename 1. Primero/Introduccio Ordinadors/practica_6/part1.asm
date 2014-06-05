.define
	num 02h

.data 0b
	mat1: db 1,2
	mat2: db 3,4
	mat3: db 0,0

.data 40
	pila: db 9,8

.org 600H
	LXI H, pila
	SPHL
	MVI A,23
	SUI 42
	MVI B, num
	LXI D, mat1
	LXI H, mat2
suma:
	call sumar
	DCR B
	jnz suma
NOP
HLT

sumar:
	PUSH PSW
	LDAX D
	ADD M
	STAX D
	INX H
	INX D
	POP PSW
ret

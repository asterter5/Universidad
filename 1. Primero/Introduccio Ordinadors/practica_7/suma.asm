
.define
	txt E000h
	tamtxt 25*40

.org 1000h
	mvi B, E0h
	mvi C, 00h
	call BORRAR
	mvi D, 05

loop:
	jmp loop

; Interrupcio TRAP asociada a la pulsacio de una tecla
.org 0024h
	in 00h 			;Llegir input del teclat
	mov e,a
	cpi 3Dh
	jz IGUAL
	ani F0h
	cpi 30h 		;Comprova que shagi introduit un numero
	jnz IGUAL 
	mov a,d
	cpi 3 			
	rz
	cpi 0 			
	rz
	mov a,e 
	stax b 			
	inx b
	dcr d
	ret

IGUAL:
	mov a,d
	cpi 0 			;Comprova si san introduit els dos numeros
	jz CALCULA 
	cpi 03h
	rnz 
	mov a,e
	cpi 2Bh 		;Comprova si sa introduit el signe "+"
	rnz 
	stax b 			
	inx b
	dcr d
	ret

CALCULA:
	mov a,e
	cpi 3Dh 		;Comprova el signe "="
	rnz
	stax b
	lxi h, txt 	
	mov a,m 		;Llegeix el digit mes significatiu
	ral 			;Desplasem el acumulador cap a la esquerra
	ral 
	ral 
	ral 
	ani F0h 		
	mov d,a 		;Llegeix el segon digit del primer numero
	inx h
	mov a,m 		
	ani 0Fh
	ora d
	mov d,a
	inx h
	inx h
	mov a,m 		;Llegeix el digit mes significatiu del segon numero
	ral 			
	ral 
	ral 
	ral 
	ani F0h 		
	mov e,a
	inx h 			
	mov a,m 		;Llegeix el digit menys significatiu del segon numero
	inx h
	ani 0Fh
	ora e 			
	add d 			
	jnc DEC
	inx h
	mvi m,31h

DEC: 
	daa 
	jnc RESULTAT
	inx h
	mvi m,31h

RESULTAT:
	inx h
	mov b,a 		
	ani F0h 		
	rar 			
	rar 
	rar 
	rar 
	ani 0Fh 		
	ori 30h 		
	mov m,a 		
	inx h 
	mov a,b
	ani 0Fh 		
	ori 30h 		
	mov m,a 

	hlt

BORRAR:
	lxi H, txt
	lxi D, txt+tamtxt

REP:
	mvi A,32
	mov M,A 		
	inx H 			
	call COMP
	cpi 1
	jz RETORNA
	jmp REP

RETORNA:
	ret

COMP:
	mov A,E
	cmp L
	jnz NO_I
	mov A,D
	cmp H
	jnz NO_I
	mvi A, 1
	ret

NO_I:
	mvi A,0
	ret

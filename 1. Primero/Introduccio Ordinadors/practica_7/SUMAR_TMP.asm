; Ejemplo de programa
; de suma
; Asociado a interrupcion TRAP

.define
	texto E000h
	tamtexto 25*40

; -------------------------------
; PROGRAMA PRINCIPAL
; -------------------------------

.org 1000h
	mvi B, E0h
	mvi C, 00h
	call borrar_p
	mvi D, 05

bucle:
	jmp bucle


; -------------------------------
; RUTINA QUE LEE DEL TECLADO Y ESCRIBE EN MEMORIA
; -------------------------------

.org 0024h 			;Interrupcion TRAP
	in 00h 		;Leer dato del teclado
	mov e,a
	cpi 3dh
	jz SIGUE
	ani f0h
	cpi 30h 		;Verifica si es caracter numerico
	jnz SIGUE 
	mov a,d
	cpi 3 		;Verifica si se completo el primer operando
	rz
	cpi 0 		;verifica si ya estan completos los dos operandos
	rz
	mov a,e 
	stax b 		;Pone el caracter en pantalla
	inx b
	dcr d
	ret

SIGUE:
	mov a,d
	cpi 0 		;Verifica si ya estan completos los dos operandos
	jz ADELANTE 
	cpi 03h
	rnz 
	mov a,e
	cpi 2bh 		;Despues del primer operando verifica si se introdujo "+"
	rnz 
	stax b 		;Se pone el signo "+" en pantalla
	inx b
	dcr d
	ret

ADELANTE:
	mov a,e
	cpi 3dh 		;Verifica si es el caracter de "="
	rnz
	stax b
	lxi h, texto 	;apunta al area de memoria de datos
	mov a,m 		;Lee el digito mas significativo del primer operando
				;Incrementa el puntero de memoria de datos
	ral 			;Desplazamiento del dato en el acumulador un lugar a la izquierda
	ral 
	ral 
	ral 
	ani f0h 		;AND con f0
	mov d,a 		;Lee el dígito menos significativo del primer operando
	inx h
	mov a,m 		;Lee el digito mas significativo de la memoria de datos
	ani 0fh
	ora d
	mov d,a
	inx h
	inx h
	mov a,m
	ral 			;Desplazamiento del dato en el acumulador un lugar a la izquierda
	ral 
	ral 
	ral 
	ani f0h 		;AND con f0
	mov e,a
	inx h 		;Incrementa el puntero de la memoria de datos
	mov a,m 		;Lee el digito menos significativo del segundo operando
	inx h
	ani 0fh
	ora e 		;Operacion OR con el digito mas significativo
	add d 		;Suma del primer operando en el regictro D con el segundo en el A
	jnc AJUSTE
	inx h
	mvi m,31h

AJUSTE: 
	daa 			;Realiza el ajuste decimal de los digitos en BCD
	jnc RESULT
	inx h
	mvi m,31h

RESULT:
	inx h
	mov b,a 		;Copia el resultado en el registro B
	ani f0h 		;Deja en A el digito mas significativo
	rar 			;Desplazamiento del dato en el acumulador un lugar a la derecha
	rar 
	rar 
	rar 
	ani 0fh 		;AND con 0f
	ori 30h 		;Operacion OR con 30H para convertir a caracter ASCII 
	mov m,a 		;Poner el msd del resultado en pantalla
	inx h 
	mov a,b
	ani 0fh 		;Seleccionar el digito menos significativo
	ori 30h 		;Convertirlo a caracter ASCII
	mov m,a 		;Poner resultado en pantalla
	hlt

borrar_p:
	lxi H, texto 	;cargamos origen
	lxi D, texto+tamtexto ;cargamos fin

repite_c:
	mvi A,32
	mov M,A 		;borrar punto de memoria
	inx H 		;incrementar direccion
	call comparador
	cpi 1
	jz fin_clear
	jmp repite_c

fin_clear:
	ret

comparador: 		;compara DE con HL (en 16 bits). Devuelve A=1 si igual
	mov A,E
	cmp L
	jnz no_igual
	mov A,D
	cmp H
	jnz no_igual
	mvi A, 1
	ret

no_igual:
	mvi A,0
	ret


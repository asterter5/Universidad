// Ivan Torres i Astor Prieto
//
// Practica_03PAE.c


/******************************
 * 
 * PRÁCTICA 3_PIH Interrupcions i Timers
 * 
 *****************************/

#include <msp430x54xA.h>
#include <stdio.h>
#include "hal_lcd.h"
		
char saludo[17]= "PRACT 3";						//Inicialitzacio de totes les variables a usar.
char cadena[17];
char borrado[] = "                 ";  
unsigned char contraste   = 0x64;
unsigned char iluminacion  = 30;
unsigned char linea=1;
char clkf=0;					//En aquesta variable, guardem el estat anterior dels botons,
						//per a despres modificar els parametres del rellotge o alarma en funcio
char estado=0;
char estado_anterior=8;
long int i;
long int tbcount = 0;				//Counter del timer B, per saber cuan passa 1 segon
long int tacount = 0;				//Counter del timer A, per saber cuan passa 1 segon
long int milis = 1000;				//Variable en la que guardem el temps a aplicar a la funcio delay();
long int hora = 0;				//Variable on guardem la hora del rellotge
long int min = 0;				//Variable on guardem els minuts del rellotge
long int sec = 0;				//Variable on guardem els segons del rellotge
long int aHora = 0;				//Variable que guarda la hora de la alarma
long int aMin = 1;				//Variable que guarda els minuts de la alarma
char valores[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};	//cadena de valors on guardem el nombres en Hex dels LEDS del Port4.


/**************************************************************************
 * BORRAR LINEA
 * 
 * Datos de entrada: Linea, indica la linea a borrar
 * 
 * Sin datos de salida
 * 
 **************************************************************************/

void borrar(unsigned char Linea)
{
	halLcdPrintLine(borrado, Linea, OVERWRITE_TEXT); //incluimos una linea en blanco
}


/**************************************************************************
 * ESCRIBIR LINEA
 * 
 * Datos de entrada: Linea, indica la linea a escribir
 * 					 String, cadena de caracteres que vamos a introducir
 * 
 * Sin datos de salida
 * 
 **************************************************************************/
  
void escribir(char String[], unsigned char Linea)  

{
	halLcdPrintLine(String, Linea, OVERWRITE_TEXT); //superponemos la nueva palabra introducida, haya o no algo.
}

/**************************************************************************
 * DELAY
 * 
 * Datos de entrada: Tiempo de retraso. 1 segundo equivale a variable retraso 25000 (aprox)
 * 
 * Sin datos de salida
 * 
 **************************************************************************/


void delay (long int temps)
{
   
		if (tbcount != 0) {			//Reiniciem la variable tcount (ms)
			tbcount = 0;
		}
		while (tbcount <= temps) {	//Delay usant els milis del Timer B
		}
	
}


/**************************************************************************
 * INICIALIZACIÓN DE LOS BOTONES.
 * Configuramos botones y leds: 
 * 
 * Sin datos de entrada
 * 
 * Sin datos de salida
 * 
 **************************************************************************/

void init_botons(void)
{
  //Configuramos botones y leds:
  P1DIR |= 0x03;	//Puertos P1.0 y P1.1 como salidas (Leds)
  P1OUT |= 0x01;	//Inicializamos puerto P1.0 a 1, 
  P1OUT &= 0xFD;	// y P1.1 a 0, para leds en alternancia


  P2DIR &= ~0xC0;	//Puertos P2.6 y P2.7 como entradas (botones S1 y S2)
  P2SEL &= ~0xC0;	//Puertos P2.6 y P2.7 como I/O digitales,
  P2REN |= 0xC0;	//con resistencia activada
  P2OUT |= 0xC0;	// de pull-up
  P2IE |= 0xC0; 	//Interrupciones activadas en P2.6 y P2.7,
  P2IES &= ~0xC0;	// con transicion L->H
  
  
  //Configuramos el joystick:
  P2DIR &= ~0x3E;	//Puertos P2.1 a P2.5 como entradas (joystick)
  P2SEL &= ~0x3E;	//Puertos P2.1 y P2.5 como I/O digitales,
  P2REN |= 0x3E;	//con resistencia activada
  P2OUT |= 0x3E;	// de pull-up
  P2IE |= 0x3E; 	//Interrupciones activadas en P2.1 a P2.5,
  P2IES &= ~0x3E;	// con transicion L->H
  
}

/*****************************************************************************
 * CONFIGURACIÓN DEL PUERTO 4, PARA ILUMINAR LOS LEDS
 * 
 * Sin datos de entrada
 * 
 * Sin datos de salida
 *  
 ****************************************************************************/
 
void config_P4_LEDS (void)
{
	P4DIR |= 0xFF;			//Inicialitzem tots els LEDS de P4 com a Sortides digitals.
	P4SEL |= 0x00;			//Marquem tots els LEDS de P4 com a la seva funcio primaria (sortida digital).
	P4OUT = 0x00;			//Donem el primer valor de sortida del P4, deixant tots els LEDS apagats inicialment.
}


/**************************************************************************
 * INICIALIZACIÓN DE PANTALLA. 
 * Inicializamos la pantallita LCD:
 * 
 * Sin datos de entrada
 * 
 * Sin datos de salida
 * 
 **************************************************************************/

void init_LCD(void)
{
      
  halLcdInit();  			//Programa interno para iniciar la pantalla     
  halLcdBackLightInit(); 		//Inicio de Iluminación posterior de la pantalla 
  halLcdSetBackLight(iluminacion); 	//Determinación de la Iluminación posterior de la pantalla
  halLcdSetContrast(contraste);		//Establecimiento del contraste
  halLcdClearScreen(); 			//Limpiar (borrar) la pantalla
}


/**************************************************************************
 * INICIALIZACIÓN DE LOS TIMERS. 
 * Inicializamos el Timer A1 i el Timer B:
 * El primero se usa para el reloj de la pantalla LCD
 * El segundo lo usamos para la funcion delay();
 * 
 * Sin datos de entrada
 * 
 * Sin datos de salida
 * 
 **************************************************************************/

void init_timers(void)
{
	/* Usamos el TimerB */
	TBCTL |= 0x0210;
	TBCCR0 = 0x03E8;		//Marca como maximo de la cuenta 1 ms.
	TBCCTL0 |= 0x0010;		//Activem les interrupcions per a CCR0.

	/* Usamos el TimerA1 */
	TA1CTL|= 0x0210;		//Preparamos el TimerA1.
	TA1CCR0 = 0x03E8;		//Maximo de la cuenta para 1 ms.
	TA1CCTL0 |= 0x0010;		//Activamos las interrupciones en CCR0.

}

void main(void)
 {

  	WDTCTL = WDTPW+WDTHOLD;       	// Paramos el watchdog timer

  	init_botons();					// Iniciamos los botones y Leds.
  	init_timers();					// Iniciamos el Timer B.
  	config_P4_LEDS();				// Iniciamos los Leds.
  	_enable_interrupt(); 				// Activamos las interrupciones a nivel global del chip
    init_LCD();						// Inicializamos la pantalla
  
  	escribir(saludo,linea); 			//escribimos saludo en la primera linea
  	linea++; 							//Aumentamos el valor de linea y con ello pasamos a la linea siguiente

  	do
   	{
   		
   		
   	if (estado_anterior != estado)			// Dependiendo el valor del estado se encenderá un LED externo u otro.
	{				
   	   sprintf(cadena," estado %d", estado); 	// Guardamos en cadena lo siguiente frase: estado "valor del estado" 
   	   escribir(cadena, linea); 			// Escribimos cadena
   	   sprintf(cadena," tiempo %d ms", milis);
   	   escribir(cadena, 3);
   	   estado_anterior=estado; 			// Actualizamos el valor de estado_anterior, para que no esté siempre escribiendo.
   	 }

   	/*
   	 * Implementada la hora i la alarma:
   	 *  Amb els botons del joystick 3, 4 i 5 seleccionem canviar les hores, els segons i els minuts de la hora, respectivament.
   	 *  Amb el boto S1, seleccionem canviar la hora de la alarma.
   	 *  Amb el boto S2, seleccionem canviar el minut de la alarma.
   	 *  Quan arriba la hora de la alarma, es mostra un missatge per pantalla.
   	 */

   	if (hora == aHora && min == aMin) {		//Si la hora guardada per la alarma es igual a la hora del rellotge
   		sprintf(cadena, "- YA ES LA HORA -", sec);
   		escribir(cadena, 5);			//Se imprime un mensaje en la pantalla de alarma
   	}

   	borrar(5);					//Cuando pasa la hora de la alarma, se deja de mostrar el mensaje

   	//MOSTRAMOS LA HORA
	//Con esta serie de sprintf se muestra la hora del reloj
	//Este bloque es equivalente a [sprintf(cadena, "Hora: %02d:%02d:%02d", hora, min, sec)]
	//Por alguna razon, esta sentencia no funciona en nuestro robot, pero de esta otra forma si

   	sprintf(cadena, "            %02d", sec);
   	escribir(cadena, 7);
   	sprintf(cadena, "         %02d:", min);
   	escribir(cadena, 7);
   	sprintf(cadena, "Hora: %02d:", hora);
   	escribir(cadena, 7);

   	//MOSTRAMOS LA ALARMA
	//Pasa lo mismo con la alarma, este bloque es equivalente a [sprintf(cadena, "Alarma: %02d:%02d", aHora, aMin)]

   	sprintf(cadena, "           %02d", aMin);
   	escribir(cadena, 8);
   	sprintf(cadena,"Alarma: %02d:", aHora);
   	escribir(cadena, 8);

	/***********************************************************************************************************************************
	*
	* 	Iniciem una subrutina que comprovara, cada cop que torni a comensar la funcio main() (despres de executar la IHR),
	* 	el estat en el que es troba i canviara el registre P4OUT per a encendre o apagar els LEDS de P4
	*	o be sumara o restara temps a la variable delayTime, per a fer que sencenguin o apaguin els LEDS
	*	de P4 amb mes o menys velocitat.
	*
	*	Aquesta subrutina tambe serveix per a cambiar la hora del rellotge i la alarma,
	*	En els estats 6 i 7, se puede aumentar o reducir la hora, min y sec del reloj o de la alarma,
	*	dependiendo de cual haya sido el estado anterior.
	*
	***********************************************************************************************************************************/


   	if (estado == 6) { 				//Si ens trobem al estat 6, sumarem un valor fixe a delayTime,
   		if (milis >= 2500) {			//fent que en els estats "3" o "4" els LEDS sencenguin i apaguin mes lentament.
   			milis = 2500;
   		}
   		else {
   			milis = milis + 500;
   		} switch(clkf) {			//Aquest switch comprova el estat en el que ens trobabem anteriorment
   			case 1:
   				aHora++;		//Si el estat anterior era 1, augmentem la hora de la alarma
   				if (aHora >= 24) {
   					aHora = 0;
   				}
   				break;
   			case 2:				//Si el estat anterior era 2, augmentem els minuts de la alarma
   				aMin++;
   				if (aMin >= 60) {
   					aMin = 0;
   				}
   				break;
   			case 3:				//Si el estat anterior era 3, augmentem la hora del rellotge
   				hora++;
   				break;
   			case 4:				//Si el estat anterior era 4, augmentem els segons del rellotge
   				sec++;
   				break;
   			case 5:				//Si el estat anterior era 5, augmentem els minuts del rellotge
   				min++;
   				break;
   		}
   		estado = 0;
   		estado_anterior = 8;
    }
   	if (estado == 7 ) {				//Si ens trobem al estat 7, restarem un valor fixe a delayTime,
   		if (milis <= 500) {			//fent que en els estats "3" o "4" els LEDS sencenguin i apaguin mes rapidament.
   		   	milis = 500;
   		}
   		else {
   			milis = milis - 500;
   		} switch(clkf) {			//Aquest switch comprova el estat que ens trobavem anteriorment
   			case 1:
   				aHora--;		//Si el estat anterior era 1, reduim la hora de la alarma
   				if (aHora < 0) {
   					aHora = 23;
   				}
   				break;
   			case 2:				//Si el estat anterior era 2, reduim els minuts de la alarma
   				aMin--;
   				if (aMin < 0) {
   					aMin = 59;
   				}
   				break;
   			case 3:				//Si el estat anterior era 3, reduim la hora del rellotge
				hora--;
				if (hora < 0) {
					hora = 23;
				} break;
			case 4:				//Si el estat anterior era 4, reduim els segons del rellotge
				sec--;
				if (sec < 0) {
					sec = 59;
				} break;
			case 5:				//Si el estat anterior era 5, reduim els minuts del rellotge
				min--;
				if (min < 0) {
					min = 59;
				} break;
		}
   		estado = 0;
   		estado_anterior = 8;
    }
   	if (estado == 3) {				//Si ens trobem al estat 3, iniciem un bucle for que comensara a encendre els LEDS
      for (i=7;i>=0;i--){				//un per un de dreta a esquerra, agafant com a delay entre ells la variable delayTime.
      	P4OUT = valores[i];				//Per a accedir iterativament als leds, un per un, usem la cadena de valors de la variable "valors".
      	delay(milis);
      }
    }
    if (estado == 4) {					//Si ens trobem al estat 4, iniciem un bucle for que comensara a encendre els LEDS
      for (i=0;i<8;i++){				//un per un de esquerra a dreta, agafant com a delay entre ells la variable delayTime.
      	P4OUT = valores[i];				//Per a accedir iterativament als leds, un per un, usem la cadena de valors de la variable "valors".
      	delay(milis);
      }
    }


    P1OUT^= 0x03;					// Encender los LEDS con intermitencia
    delay(1000);					// retraso de aprox 1 segundo
   	}

  	while(1);					//Bucle infinito que deja al robot en espera hasta la ocurrencia de alguna interrupcion.
}


/**************************************************************************
 * MINIPROGRAMA DE LOS BOTONES:
 * Mediante este programa, se detectará que botón se ha pulsado
 * 		 
 * Sin Datos de entrada
 * 
 * Sin datos de salida
 * 
 * Actualiza el valor estado
 * 
 **************************************************************************/
 
#pragma vector=TIMERB0_VECTOR		//INTERRUPCION ASOCIADA AL TIMERB
__interrupt void TimerB_ISR(void)
{
	TBCCTL0 &= 0xFFEF; 		//Desactivamos la interrupciones de CCR0

	tbcount++;

	TBCCTL0 |= 0x0010;		//Reactivamos las interrupciones de CCR0
	TBCCTL0 &= 0xFFFE;		//Limpiamos el flag CCIFG
}

#pragma vector=TIMER1_A0_VECTOR		//INTERRUPCION ASOCIADA AL TIMERA1
__interrupt void TimerA1_ISR(void)
{
	TA1CCTL0 &= 0xFFEF;		//Desactivamos las interrupciones de CCR0

	tacount++;

	if(tacount == 1000) {		//A cada segon que passa (comptat per la variable tacount), sumem un segon al rellotge
		sec = sec + 1;
		if(sec >= 60) {		//Si els segons son 60, tornem a posarlos a 0 i sumem 1 minut
			sec = 00;
			min = min + 1;
		} if(min >= 60) {	//Si els mintus son 60, tornem a posarlos a 0 i sumem 1 hora
			min = 00;
			hora = hora + 1;
		} if(hora >= 24) {	//Si arriba a 24 hores, tornem a marcar 0 hores
			hora = 00;
		} tacount = 0;		//reiniciem el comptador del TimerA1
	}


	TA1CCTL0 |= 0x0010;		//Reactivamos las interrupciones de CCR0
	TA1CCTL0 &= 0xFFFE;		//Limpiamos el flag de CCIFG
}

#pragma vector=PORT2_VECTOR  //interrupción de los botones. Actualiza el valor de la variable global estado.
__interrupt void Port2_ISR(void)
{
	P2IE &= 0xC0; 	//interrupciones botones S1 y S2 (P2.6 y P2.7) desactivadas
	P2IE &= 0x3E;   //interrupciones joystick (2.1-2.5) desactivadas

	
	/**********************************************************+
		A RELLENAR POR EL ALUMNO BLOQUE CASE 
	 
	Boton S1, estado =1 y leds ON
	Boton S2, estado =2 y leds uno ON y otro OFF 
	Joystick left, estado =3 y leds off
	Joystick right, estado =4 y leds off
	Joystick center, estado = 5 y leds uno OFF y otro ON
	Joystick up, estado =6 y leds off
	Joystick down, estado =7 y leds off
	 * *********************************************************/


	 switch (P2IFG) {			//Switch que buscara, segun el valor del registro P2IFG, quien ha llamado la interrupcion.
	 case 0x40: /* Estado 1, BOTON S1 */
		 	 P1OUT |= 0x03;		//Amb aquesta modificacio de P1OUT, encenem el LED P1.0 i P1.1.
		 	 estado = 1;		//Marquem, a la variable "estado", que ens trobem al estat 1.
		 	 clkf = estado;
		 	 break;
	 case 0x80: /* Estado 2, BOTON S2 */
		 	 P1OUT = 0x01;		//Amb aquesta modificacio de P1OUT, encenem el LED P1.0 i apaguem el LED P1.1.
		 	 estado = 2;		//Marquem, a la variable "estado", que ens trobem al estat 2.
		 	 clkf = estado;
		 	 break;
	 case 0x02: /* Estado 3, Joystick Izquierda */
		 	 P1OUT &= 0x00;		//Amb aquesta modificacio de P1OUT, apaguem tot dos leds (P1.0 i P1.1).
		 	 estado = 3;		//Marquem, a la variable "estado", que ens trobem al estat 3.
		 	 clkf = estado;
		 	 break;
	 case 0x04: /* Estado 4, Joystick Derecha */
	 		 P1OUT &= 0x00;		//Amb aquesta modificacio de P1OUT, apaguem tot dos leds (P1.0 i P1.1).
	 		 estado = 4;		//Marquem, a la variable "estado", que ens trobem al estat 4.
	 		 clkf = estado;
	 		 break;
	 case 0x08: /* Estado 5, Joystick Centro */
	 		 P1OUT = 0x02;		//Amb aquesta modificacio de P1OUT, apaguem el LED P1.0 i encenem el LED P1.1.
	 		 estado = 5;		//Marquem, a la variable "estado", que ens trobem al estat 5.
	 		 clkf = estado;
	 		 break;
	 case 0x10: /* Estado 6, Joystick Arriba */
	 		 P1OUT &= 0x00;		//Amb aquesta modificacio de P1OUT, apaguem tot dos leds (P1.0 i P1.1).
	 		 estado = 6;		//Marquem, a la variable "estado", que ens trobem al estat 6.
	 		 break;
	 case 0x20: /* Estado 7, Joystick Abajo */
	 		 P1OUT &= 0x00;		//Amb aquesta modificacio de P1OUT, apaguem tot dos leds (P1.0 i P1.1).
	 		 estado = 7;		//Marquem, a la variable "estado", que ens trobem al estat 7.
	 		 break;
	 }


	/***********************************************
   	 * HASTA AQUI BLOQUE CASE
   	 ***********************************************/	
	
	P2IFG = 0;		//limpiamos todas las interrupciones
	P2IE |= 0xC0; 	//interrupciones botones S1 y S2 (P2.6 y P2.7) reactivadas
	P2IE |= 0x3E;  //interrupciones joystick (2.1-2.5) reactivadas
 return;
}

// Ivan Torres i Astor Prieto
//
// Practica_02PAE.c


/******************************
 * 
 * PRÁCTICA 2_PIH Programació de Ports i pràctica de: "do-while" "case" "if" i "for"
 * 
 *****************************/

#include <msp430x54xA.h>
#include <stdio.h>
#include "hal_lcd.h"
		
char saludo[17]= "PRACT 2";						//Inicialitzacio de totes les variables a usar.
char cadena[17];
char borrado[] = "                 ";  
unsigned char contraste   = 0x64;
unsigned char iluminacion  = 30;
unsigned char linea=1;
char estado=0;
char estado_anterior=8;
long int i;
long int delayTime;							//Variable en la que guardem el temps a aplicar a la funcio delay();
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
 * DELAY - A CONFIGURAR POR EL ALUMNO_ con bucle while
 * 
 * Datos de entrada: Tiempo de retraso. 1 segundo equivale a variable retraso 25000 (aprox)
 * 
 * Sin datos de salida
 * 
 **************************************************************************/


void delay (long int temps)
{
   volatile long int i=0;

	 /***********************************************
   	 * A RELLENAR POR EL ALUMNO BLOQUE WHILE
   	 ***********************************************/	
   
   	 while (i < temps) {		//Bucle while, on simplement anem sumant un a la variable i cada pas.
   		 i++;
   	 }

   
   	 /***********************************************
   	 * HASTA AQUI BLOQUE WHILE
   	 ***********************************************/	
	
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
 * CONFIGURACIÓN DEL PUERTO 4, PARA ILUMINAR LOS LEDS. A REALIZAR POR EL ALUMNO
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



void main(void)
{	

  	WDTCTL = WDTPW+WDTHOLD;       	// Paramos el watchdog timer
  	delayTime = 25000; 		//Delay de 1 segundo.
  
  	init_botons();					// Iniciamos los botones y Leds.
  	config_P4_LEDS();				// Iniciamos los Leds.
    _enable_interrupt(); 				// Activamos las interrupciones a nivel global del chip
    init_LCD();						// Inicializamos la pantalla
  
  	escribir(saludo,linea); 			//escribimos saludo en la primera linea
  	linea++; 					//Aumentamos el valor de linea y con ello pasamos a la linea siguiente

  	do
   	{
   		
   		
   	if (estado_anterior != estado)			// Dependiendo el valor del estado se encenderá un LED externo u otro.
	{				
   	   sprintf(cadena," estado %d", estado); 	// Guardamos en cadena lo siguiente frase: estado "valor del estado" 
   	   escribir(cadena,linea); 			// Escribimos cadena
   	   estado_anterior=estado; 			// Actualizamos el valor de estado_anterior, para que no esté siempre escribiendo.
   	 }



	/***********************************************************************************************************************************
	*
	* 	Iniciem una subrutina que comprovara, cada cop que torni a comensar la funcio main() (despres de executar la IHR),
	* 	el estat en el que es troba i canviara el registre P4OUT per a encendre o apagar els LEDS de P4
	*	o be sumara o restara temps a la variable delayTime, per a fer que sencenguin o apaguin els LEDS
	*	de P4 amb mes o menys velocitat.
	*
	***********************************************************************************************************************************/


   	if (estado == 6) { 				//Si ens trobem al estat 6, sumarem un valor fixe a delayTime,
      delayTime = delayTime + 5000;			//fent que en els estats "3" o "4" els LEDS sencenguin i apaguin mes lentament.
    }
   	if (estado == 7 ) {				//Si ens trobem al estat 7, restarem un valor fixe a delayTime,
      delayTime = delayTime - 5000;			//fent que en els estats "3" o "4" els LEDS sencenguin i apaguin mes rapidament.
    }
   	if (estado == 3) {				//Si ens trobem al estat 3, iniciem un bucle for que comensara a encendre els LEDS
      for (i=7;i>=0;i--){				//un per un de dreta a esquerra, agafant com a delay entre ells la variable delayTime.
      	P4OUT = valores[i];				//Per a accedir iterativament als leds, un per un, usem la cadena de valors de la variable "valors".
      	delay(delayTime);
      }
    }
    if (estado == 4) {					//Si ens trobem al estat 4, iniciem un bucle for que comensara a encendre els LEDS
      for (i=0;i<8;i++){				//un per un de esquerra a dreta, agafant com a delay entre ells la variable delayTime.
      	P4OUT = valores[i];				//Per a accedir iterativament als leds, un per un, usem la cadena de valors de la variable "valors".
      	delay(delayTime);
      }
    }


    P1OUT^= 0x03;					// Encender los LEDS con intermitencia
    delay(25000);					// retraso de aprox 1 segundo
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
		 	 break;
	 case 0x80: /* Estado 2, BOTON S2 */
		 	 P1OUT = 0x01;		//Amb aquesta modificacio de P1OUT, encenem el LED P1.0 i apaguem el LED P1.1.
		 	 estado = 2;		//Marquem, a la variable "estado", que ens trobem al estat 2.
		 	 break;
	 case 0x02: /* Estado 3, Joystick Izquierda */
		 	 P1OUT &= 0x00;		//Amb aquesta modificacio de P1OUT, apaguem tot dos leds (P1.0 i P1.1).
		 	 estado = 3;		//Marquem, a la variable "estado", que ens trobem al estat 3.
		 	 break;
	 case 0x04: /* Estado 4, Joystick Derecha */
	 		 P1OUT &= 0x00;		//Amb aquesta modificacio de P1OUT, apaguem tot dos leds (P1.0 i P1.1).
	 		 estado = 4;		//Marquem, a la variable "estado", que ens trobem al estat 4.
	 		 break;
	 case 0x08: /* Estado 5, Joystick Centro */
	 		 P1OUT = 0x02;		//Amb aquesta modificacio de P1OUT, apaguem el LED P1.0 i encenem el LED P1.1.
	 		 estado = 5;		//Marquem, a la variable "estado", que ens trobem al estat 5.
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

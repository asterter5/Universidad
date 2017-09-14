/*
 * libreria_config.c
 *
 *  Created on: 13/05/2015
 *      Author: mat.aules
 */

#include <msp430x54xA.h>
#include <stdio.h>
#include "hal_lcd.h"
#include "libreria_robot.h"
#include "libreria_config.h"

extern byte gbpParameter[32];

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
  halLcdSetBackLight(30); 	//Determinación de la Iluminación posterior de la pantalla
  halLcdSetContrast(0x64);		//Establecimiento del contraste
  halLcdClearScreen(); 			//Limpiar (borrar) la pantalla
}

/**************************************************************************
 * INICIALIZACIÓN DE LOS TIMERS.
 * Inicializamos los timers A1 y B:
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
	TBCCR0 = 0x3E80;		//Marca como maximo de la cuenta 1 ms.
	TBCCTL0 |= 0x0010;		//Activem les interrupcions per a CCR0.

	/* Usamos el TimerA1 */
	TA1CTL|= 0x0210;		//Preparamos el TimerA1.
	TA1CCR0 = 0x3E80;		//Maximo de la cuenta para 1 ms.
	TA1CCTL0 |= 0x0010;		//Activamos las interrupciones en CCR0.

}

/**************************************************************************
 * INICIALIZACIÓN DE LA USCI.
 * Inicializamos la USCI para modificar la frecuència del micro:
 *
 * Sin datos de entrada
 *
 * Sin datos de salida
 *
 **************************************************************************/

void init_UCS(void)
{
	/* inicialització de les freqüències de rellotge del microcontrolador */
	unsigned long DCORSEL = DCORSEL_6; 	//DCORSEL_6 selecciona rango de DCO de 7 a 60 MHz
	unsigned short FLLN = 487;			//Parametro N
	__bis_SR_register(SCG0); 			// Desactiva el FLL control loop
	UCSCTL0 = 0x00; 					// Posa DCOx, MODx al mínim possible
	UCSCTL1 = DCORSEL; 					// Seleccionem el rang de DCO 16 MHz
	UCSCTL2 = FLLN + FLLD_1; 			//Selecciona el factor multiplicador del DCO
	UCSCTL3 = 0; 						//Referència FLL SELREF = XT1, divisor =1;
	/* Selecció de la font de rellotge: ACLK el Clock extern de 2^15 (32kHz), SMCLK i MCLK el DCO intern de 16MHz */
	UCSCTL4 = SELA__XT1CLK | SELS__DCOCLKDIV | SELM__DCOCLKDIV ;
	UCSCTL5 = DIVA__1 | DIVS__1; 		//Divisor per SMCLK: f(SMCLK)/1 i ACLK: f(ACLK)/1
	__bic_SR_register(SCG0); 			// Enable the FLL control loop
	P11DIR = 0x07; 						//Configurem els pins 11.0, 11.1 y 11.2 com sortida
	P11SEL = 0x07; 						//ACLK, MCLK y SMCLK; activem els pins de test (FUNC. ALTERNATIVA)
}

/**************************************************************************
 * INICIALIZACIÓN DE LA UART.
 * Inicializamos la UART para enviar y recibir datos del robot:
 *
 * Sin datos de entrada
 *
 * Sin datos de salida
 *
 **************************************************************************/

void init_UART(void)
{
	/* Inicialitzem la UART per a comunicarse amb el robot */
	UCA0CTL1 |= UCSWRST; //Fem un reset de la USCI i es desactiva
	UCA0CTL0 = 0x00; 	//UCSYNC=0 mode asíncron
						//UCMODEx=0 seleccionem mode UART
						//UCSPB=0 nomes 1 stop bit
						//UC7BIT=0 8 bits de dades
						//UCMSB=0 bit de menys pes primer
						//UCPAR=x no es fa servir bit de paritat
						//UCPEN=0 sense bit de paritat
	UCA0CTL1 |= UCSSEL__SMCLK; //Triem SMCLK (16MHz) com a font del clock BRCLK
	UCA0BR0 = 1; //Prescaler de BRCLK fixat a 1 (LO byte = 1, ...
	UCA0BR1 = 0; //... HI byte = 0).
	UCA0MCTL = UCOS16; // No necessitem modulació (divisió entera), però
						// si oversampling => bit 0 = UCOS16 = 1.
						// El Baud rate és BRCLK/16=1MBps
	P3SEL |= 0x30; //I/O funcion: P3.4 = UART0TX, P3.5 = UART0RX
	P3REN |= 0x20; //amb resistència activada de pull-up l’entrada P3.5
	P3OUT |= 0x20; //
	P3DIR |= 0x80; //Port P3.7 com sortida (Data Direction: selector Tx/Rx)
	P3SEL &= ~0x80; //Port 3.7 com I/O digital
	P3OUT &= ~0x80; //Inicialitzem el port P3.7 a 0 (Rx)
	UCA0CTL1 &= ~UCSWRST; //Reactivem la línia de comunicacions sèrie
	UCA0IE |= UCRXIE; //Això s’ha d’activà només quan fem la recepció
 }

/**************************************************************************
 * CONFIGURACION DE LOS MOTORES.
 * Configuramos los motores modificando los registros de los modulos,
 * para que giren en modo continuo:
 *
 * Sin datos de entrada
 *
 * Sin datos de salida
 *
 **************************************************************************/
void config_motores(void)
{
	volatile int i;

	gbpParameter[0] = 0x06;			//Escribimos en las posiciones de memoria 6, 7, 8 y 9
	gbpParameter[1] = 0;
	for (i=0; i<4; i++){
		TxPacket(0x01, 2, 0x03);	// Modo Continuo para motor1 (Atras derecha)
		RxPacket();
		TxPacket(0x02, 2, 0x03);	// Modo Continuo para motor2 (Delante derecha)
		RxPacket();
		TxPacket(0x03, 2, 0x03);	// Modo Continuo para motor3 (Delante izquierda)
		RxPacket();
		TxPacket(0x04, 2, 0x03);	// Modo Continuo para motor4 (Atras izquierda)
		RxPacket();

		gbpParameter[0]++;
	}
}

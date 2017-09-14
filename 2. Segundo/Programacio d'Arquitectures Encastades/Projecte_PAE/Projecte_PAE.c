// Ivan Torres i Astor Prieto
//
// Projecte_PAE.c


/******************************
 * 
 * PROJECTE_PIH - ROBOT PAE.
 * 
 *****************************/

#include <msp430x54xA.h>
#include <stdio.h>
#include "hal_lcd.h"
#include "libreria_robot.h"
#include "libreria_config.h"

extern byte gbpParameter[32];				// Array para los parametros de Tx.
extern int byte_UART;
extern int byte_recibido;
extern int timeOut;
extern int cont;
extern int cMicro;
extern char micro;
extern RxRes paquete;

char saludo[17]= "PORJECTE PAE";						//Inicialitzacio de totes les variables a usar.
char cadena[17];
char borrado[] = "                 ";  
unsigned char linea=1;
char estado=0;
char estado_anterior=8;
long int i;
long int tbcount = 0;
long int tacount = 0;
long int milis = 1000;				//Variable en la que guardem el temps a aplicar a la funcio delay();
char direccion_pred;
char front;
char der;
char izq;
int flag_func;

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
 * ESCRIBIR_SENSORES
 *
 * Sin datos de entrada
 *
 * Sin datos de salida
 *
 **************************************************************************/
void escribir_sensores(void)
{
	front = leer_sensor_frontal().Packet[5];			//Leemos el sensor IR frontal
	sprintf(cadena,"Frontal: %02X", front);
	escribir(cadena, 5);
	der = leer_sensor_derecho().Packet[5];			//Leemos el sensor IR derecho
	sprintf(cadena,"Derecho: %02X", der);
	escribir(cadena, 6);
	izq = leer_sensor_izquierdo().Packet[5];			//Leemos el sensor IR izquierdo
	sprintf(cadena,"Izquierdo: %02X", izq);
	escribir(cadena, 7);
}

/**************************************************************************
 * CANCION VICTORIA
 * 
 * Sin datos de entrada
 * 
 * Sin datos de salida
 * 
 **************************************************************************/
void cancion_victoria()
{
	halt_motores();
	delay(1000);
	reproducir_nota(22, 8); // SOL
	delay(1100);
	reproducir_nota(22, 8); // SOL
	delay(1100);
	reproducir_nota(22, 8); // SOL
	delay(1100);
	reproducir_nota(18, 5); // MIb
	delay(800);
	reproducir_nota(25, 2); // SIb
	delay(420);
	reproducir_nota(22, 8); // SOL
	delay(1100);
	reproducir_nota(18, 5); // MIb
	delay(800);
	reproducir_nota(25, 2); // SIb
	delay(420);
	reproducir_nota(22, 16); // SOL
	delay(2050);

	reproducir_nota(29, 8); // RE^
	delay(1100);
	reproducir_nota(29, 8); // RE^
	delay(1100);
	reproducir_nota(29, 8); // RE^
	delay(1100);
	reproducir_nota(30, 5); // MIb^
	delay(800);
	reproducir_nota(25, 2); // SIb
	delay(420);
	reproducir_nota(21, 8); // SOLb
	delay(1100);
	reproducir_nota(18, 5); // MIb
	delay(800);
	reproducir_nota(25, 2); // SIb
	delay(420);
	reproducir_nota(22, 16); // SOL
	delay(2050);

	/*
	reproducir_nota(34, 8); // SOL^
	delay(1100);
	reproducir_nota(22, 5); // SOL
	delay(800);
	reproducir_nota(22, 2); // SOL
	delay(420);
	reproducir_nota(34, 8); // SOL^
	delay(1100);
	reproducir_nota(33, 5); // FAs^
	delay(800);
	reproducir_nota(32, 2); // FA^
	delay(420);
	reproducir_nota(31, 2); // MI^
	delay(420);
	reproducir_nota(30, 2); // REs^
	delay(420);
	reproducir_nota(31, 5); // MI^
	delay(800);
	reproducir_nota(23, 5); // SOLs
	delay(800);
	reproducir_nota(28, 8); // DOs^
	delay(1100);
	reproducir_nota(27, 5); // DO^
	delay(800);
	reproducir_nota(26, 2); // SI
	delay(420);
	reproducir_nota(25, 2); // SIb
	delay(420);
	reproducir_nota(24, 2); // LA
	delay(420);
	reproducir_nota(26, 5); // SI
	delay(800);
	reproducir_nota(18, 5); // MIb
	delay(800);
	reproducir_nota(21, 8); // SOLb
	delay(1100);
	reproducir_nota(19, 5); // MI
	delay(800);
	reproducir_nota(22, 2); // SOL
	delay(420);
	reproducir_nota(25, 8); // SIb
	delay(1100);
	reproducir_nota(22, 5); // SOL
	delay(800);
	reproducir_nota(26, 2); // SI
	delay(420);
	reproducir_nota(29, 16); // RE^
	delay(2050);

	reproducir_nota(34, 8); //
	delay(1100);
	reproducir_nota(22, 5); //
	delay(800);
	reproducir_nota(22, 2); //
	delay(420);
	reproducir_nota(34, 8); //
	delay(1100);
	reproducir_nota(33, 5); //
	delay(800);
	reproducir_nota(32, 2); //
	delay(420);
	reproducir_nota(31, 2); //
	delay(420);
	reproducir_nota(30, 2); //
	delay(420);
	reproducir_nota(31, 5); //
	delay(800);
	reproducir_nota(23, 5); //
	delay(800);
	reproducir_nota(28, 8); //
	delay(1100);
	reproducir_nota(27, 5); //
	delay(800);
	reproducir_nota(26, 2); //
	delay(420);
	reproducir_nota(25, 2); //
	delay(420);
	reproducir_nota(24, 2); //
	delay(420);
	reproducir_nota(26, 5); //
	delay(800);
	reproducir_nota(18, 5); //
	delay(800);
	reproducir_nota(21, 8); //
	delay(1100);
	reproducir_nota(19, 5); //
	delay(800);
	reproducir_nota(26, 2); //
	delay(420);
	reproducir_nota(22, 8); //
	delay(1100);
	reproducir_nota(18, 5); //
	delay(800);
	reproducir_nota(25, 2); //
	delay(420);
	reproducir_nota(22, 16); //
	delay(2050); */

}

/**************************************************************************
 *
 * FUNCION MAIN.
 *
 **************************************************************************/

void main(void)
 {

  	WDTCTL = WDTPW+WDTHOLD;       	// Paramos el watchdog timer

  	init_botons();					// Iniciamos los botones y Leds.
  	init_timers();					// Iniciamos el Timer B.
  	init_UCS();						// Iniciamos la UCS y ponemos SMCLK a 16MHz.
  	init_UART();					// Iniciamos la UART para comunicarnos con el robot.
  	config_P4_LEDS();				// Iniciamos los Leds.
  	_enable_interrupt(); 			// Activamos las interrupciones a nivel global del chip
    init_LCD();						// Inicializamos la pantalla
    config_motores();				// Ponemos los motores en modo continuo
  
  	escribir(saludo,linea); 		//escribimos saludo en la primera linea
  	linea++; 						//Aumentamos el valor de linea y con ello pasamos a la linea siguiente

  	delay(3000);

  	do
   	{

  		while (cMicro < 2) {
  			halLcdPrintLine("   Escuchando", 4, OVERWRITE_TEXT);
  			cMicro = leer_microfono().Packet[5];
  		}

  		/* HEURISTICA DEL ROBOT: */
  		escribir_sensores();

  		/*
  		Siempre intentaremos actualizar los sensores lo antes posible, tmb no interesaria para las pruebas el k salga la distancia de cada uno por pantalla...
  		Para lo que viene a continuacion necesitariamos inicializar un contador absoluto arriba del todo a 1, cn el objetivo de k una vez se encuente un objeto a nivel frontal haga una comparacion hacia los lados para saber
         que pared esta mas cerca, si la izquierda esta mas cerca implica k los el primero sera a la derecha(eso lo marcara otra funcion), pero los siguientes hasta encontrarse cn otra pared frontal seran hacia la izquierda(y el ultimo otra vez a la derecha)
  		*/
  		if(izq > 0xB0 || der > 0xB0){
  			while (izq > 0x90 && front < 0x20) {
  				giro_derecha();
  				escribir_sensores();
  			}
  			while (der > 0x80 && front < 0x20) {
  				giro_izquierda();
  				escribir_sensores();
  			}

  		}
  		if (front > 0x70 && cont > 0) {
  			if(der < izq) {
  			 	direccion_pred = 0;  //IZQesta la usaremos para k cuando los 3 sensores vuelvan a 00 sepamos hacia donde tiene k volver el robot
  			} else {
  			  	direccion_pred = 2;	//DER
  			} cont--;
  		}

  		if (cont == 0 && front > 0x80) {
  			while (der < izq && front != 0x00 ){
  			  	giro_derecha();				//HACEMOS GIRAR A LA DERECHA AL ROBOT
  			  	escribir_sensores();
  				flag_func = 2;
  			}
  			while (izq < der && front != 0x00 ){
  			  	giro_izquierda();				//HACEMOS GIRAR A LA IZQUIERDA AL ROBOT
  			    escribir_sensores();
  			    flag_func = 0;
  			}
  		}

  		if (cont == 0 && izq < 0X10  && der < 0X10 && front < 0x90) {
  			int cont2 = 10;
  			while (izq < 0X40  && der < 0X40 && front < 0x30 && cont2 > 0) {
  				mov_adelante(0xFF);
  	  			delay(50);
  	  			escribir_sensores();
  	  			--cont2;
  			}

  			while (direccion_pred == 0 && front == 0x00 && izq < 0x70) {
  			  	giro_izquierda_mod();
  			  	escribir_sensores();
  			}while (direccion_pred == 2 && front == 0x00 && der < 0x70) {	// NOk salte antes pork parece k no es tan sensible
  			  	giro_derecha_mod();											// como el otro
  			  	escribir_sensores();
  			}
  		}

  		if (cont == 0 && izq > 0X50  && der > 0X50 && front > 0xC0) {
  			while (izq > 0x00 || der > 0x00){
  				mov_atras(0xFF);
  			  	escribir_sensores();
  			}
  			delay(900);
  			giro_izquierda_mod();
  			delay(600);
  			escribir_sensores();
  		}
  		mov_adelante(0xFF);			//HACEMOS AVANZAR AL ROBOT                  exactamente no se cuanto deberiamos dejarle, lo descubriremos en las pruebas

  		/*/HEURISTICA DEL ROBOT. */


   	if (estado_anterior != estado)			// Dependiendo el valor del estado se encenderá un LED externo u otro.
	{				
   	   sprintf(cadena," estado %d", estado); 	// Guardamos en cadena lo siguiente frase: estado "valor del estado" 
   	   escribir(cadena, linea); 			// Escribimos cadena
   	   sprintf(cadena," tiempo %d ms", milis);
   	   escribir(cadena, 3);
   	   estado_anterior=estado; 			// Actualizamos el valor de estado_anterior, para que no esté siempre escribiendo.
   	 }

	/***********************************************************************************************************************************
	*
	* 	Iniciem una subrutina que comprovara, cada cop que torni a comensar la funcio main() (despres de executar la IHR),
	* 	el estat en el que es troba i enviara uns paquets o uns altres als motors del robot per a encendre els LED's de cada
	*	motor i per a comensar el moviment dels motors.
	*
	*	Els botons del joystick criden a les funcions respectives per a moure el robot endevant (Joystick adalt), endarrera 
	*	(Joystick abaix), a la esquerra (Joystick esquerra) i a la dreta (Joystick dreta). A mes, el boto S2 para en complet el 
	*	moviment dels motors i el boto S1 ens llegira i imprimira per pantalla LCD les lectures dels tres sensors IR del robot.
	*
	***********************************************************************************************************************************/

   	if (estado == 6) {
   		//mov_adelante(0xFF);				//HACEMOS AVANZAR AL ROBOT

   		estado = 0;
   		estado_anterior = 8;
    }

   	if (estado == 7 ) {
   		//mov_atras(0xFF);				//HACEMOS RETROCEDER AL ROBOT

   		estado = 0;
   		estado_anterior = 8;
    }

   	if (estado == 3) {
   	  //giro_izquierda();				//HACEMOS GIRAR A LA DERECHA AL ROBOT
   	  //delay(2430);
   	  //halt_motores();				//TRAS 2'5 SEGUNDOS, PARAMOS EL GIRO

   	  estado = 0;
   	  estado_anterior = 8;
    }

    if (estado == 4) {
      //giro_derecha();				//HACEMOS GIRAR A LA IZQUIERDA AL ROBOT
      //delay(2430);
      //halt_motores();				//TRAS 2'5 SEGUNDOS, PARAMOS EL GIRO

      estado = 0;
      estado_anterior = 8;
    }

    if (estado == 2) {
    	//halt_motores();				//PAREM AMB EL BOTO S2 TOT EL MOVIMENT DEL ROBOT
    	cont = 1;
    	cancion_victoria();

    	estado = 0;
    	estado_anterior = 8;
    }

    if (estado == 1) {						//CON EL BOTON S1:
    	paquete = leer_sensor_frontal();			//Leemos el sensor IR frontal
    	sprintf(cadena,"Frontal: %02X", paquete.Packet[5]);	//Imprimimos su lectura por pantalla
    	escribir(cadena, 5);

    	paquete = leer_sensor_derecho();			//Leemos el sensor IR derecho
    	sprintf(cadena,"Derecho: %02X", paquete.Packet[5]);	//Imprimimos su lectura por pantalla
    	escribir(cadena, 6);

    	paquete = leer_sensor_izquierdo();			//Leemos el sensor IR izquierdo
    	sprintf(cadena,"Izquierdo: %02X", paquete.Packet[5]);	//Imprimimos su lectura por pantalla
    	escribir(cadena, 7);

    	estado = 0;
    	estado_anterior = 8;
    }

    P1OUT^= 0x03;					// Encender los LEDS con intermitencia
    //delay(1000);					// retraso de aprox 1 segundo
   	}

  	while(1);					//Bucle infinito que deja al robot en espera hasta la ocurrencia de alguna interrupcion.
}

/**************************************************************************
 * RUTINAS DE SERVICIO DE INTERRUPCIONES:
 * 
 * Tres rutinas que gestionan las interrupciones que generaremos;
 * USCI_A0_ISR() gestiona las interrupciones de la UART.
 * TimerB_ISR() y TimerA1_ISR() gestionan los timers del micro.
 * Port2_ISR() gestiona las interrupciones provocadas por los botones.
 * 
 **************************************************************************/
 
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
	UCA0IE &= ~UCRXIE;		//Desactivamos interrupciones de la UART
	byte_UART = UCA0RXBUF;	//Recibimos el byte del buffer de la UART
	byte_recibido = 1;		//Marcamos como que hemos recibido un byte
	UCA0IE |= UCRXIE;		//Reactivamos las interrupciones
}

#pragma vector=TIMERB0_VECTOR
__interrupt void TimerB_ISR(void)
{
	TBCCTL0 &= 0xFFEF; 		//Desactivamos la interrupciones de CCR0

	tbcount++;

	TBCCTL0 |= 0x0010;		//Reactivamos las interrupciones de CCR0
	TBCCTL0 &= 0xFFFE;		//Limpiamos el flag CCIFG
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TimerA1_ISR(void)
{
	TA1CCTL0 &= 0xFFEF;		//Desactivamos las interrupciones de CCR0

	tacount++;			//Aumentamos el contador tacount
	timeOut--;			//Vamos bajando el contador de TimeOut

	TA1CCTL0 |= 0x0010;		//Reactivamos las interrupciones de CCR0
	TA1CCTL0 &= 0xFFFE;		//Limpiamos el flag de CCIFG
}

#pragma vector=PORT2_VECTOR  //interrupción de los botones. Actualiza el valor de la variable global estado.
__interrupt void Port2_ISR(void)
{
	P2IE &= 0xC0; 	//interrupciones botones S1 y S2 (P2.6 y P2.7) desactivadas
	P2IE &= 0x3E;   //interrupciones joystick (2.1-2.5) desactivadas

	 switch (P2IFG) {			//Switch que buscara, segun el valor del registro P2IFG, quien ha llamado la interrupcion.
	 case 0x40: /* Estado 1, BOTON S1 */
		 	 P1OUT |= 0x03;		//Amb aquesta modificacio de P1OUT,
		 	 estado = 1;		//Marquem, a la variable "estado", que ens trobem al estat 1.
		 	 break;
	 case 0x80: /* Estado 2, BOTON S2 */
		 	 P1OUT = 0x01;		//Amb aquesta modificacio de P1OUT, 
		 	 estado = 2;		//Marquem, a la variable "estado", que ens trobem al estat 2.
		 	 break;
	 case 0x02: /* Estado 3, Joystick Izquierda */
		 	 P1OUT &= 0x00;		//Amb aquesta modificacio de P1OUT, 
		 	 estado = 3;		//Marquem, a la variable "estado", que ens trobem al estat 3.
		 	 break;
	 case 0x04: /* Estado 4, Joystick Derecha */
	 		 P1OUT &= 0x00;		//Amb aquesta modificacio de P1OUT, 
	 		 estado = 4;		//Marquem, a la variable "estado", que ens trobem al estat 4.
	 		 break;
	 case 0x08: /* Estado 5, Joystick Centro */
	 		 P1OUT = 0x02;		//Amb aquesta modificacio de P1OUT, 
	 		 estado = 5;		//Marquem, a la variable "estado", que ens trobem al estat 5.
	 		 break;
	 case 0x10: /* Estado 6, Joystick Arriba */
	 		 P1OUT &= 0x00;		//Amb aquesta modificacio de P1OUT, 
	 		 estado = 6;		//Marquem, a la variable "estado", que ens trobem al estat 6.
	 		 break;
	 case 0x20: /* Estado 7, Joystick Abajo */
	 		 P1OUT &= 0x00;		//Amb aquesta modificacio de P1OUT,
	 		 estado = 7;		//Marquem, a la variable "estado", que ens trobem al estat 7.
	 		 break;
	 }
	
	P2IFG = 0;		//limpiamos todas las interrupciones
	P2IE |= 0xC0; 	//interrupciones botones S1 y S2 (P2.6 y P2.7) reactivadas
	P2IE |= 0x3E;  //interrupciones joystick (2.1-2.5) reactivadas
 return;
}

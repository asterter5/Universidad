// Ivan Torres i Astor Prieto
//
// Practica_04PAE.c


/******************************
 * 
 * PRÁCTICA 4_PIH Connexió al Robot.
 * 
 *****************************/

#include <msp430x54xA.h>
#include <stdio.h>
#include "hal_lcd.h"
		
typedef unsigned char byte; 			//DEFINIM EL TIPUS BYTE
#define TXD0_READY (UCA0IFG & UCTXIFG)
#define RXD0_READY (UCA0IFG & UCRXIFG)

typedef struct {
	byte Packet[32];			//DEFINIM EL PAQUET QUE RETORNARA RxPacket()
} RxRes;

char saludo[17]= "PRACT 4";						//Inicialitzacio de totes les variables a usar.
char cadena[17];
char borrado[] = "                 ";  
unsigned char contraste   = 0x64;
unsigned char iluminacion  = 30;
unsigned char linea=1;
char clkf=0;
char estado=0;
char estado_anterior=8;
long int i;
long int tbcount = 0;
long int tacount = 0;
long int milis = 1000;				//Variable en la que guardem el temps a aplicar a la funcio delay();
char valores[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};	//cadena de valors on guardem el nombres en Hex dels LEDS del Port4.
byte gbpParameter[32];		// Array para los parametros de Tx.
int LED_flag1 = 0;
int LED_flag2 = 0;
int LED_flag3 = 0;
int LED_flag4 = 0;
int byte_UART = 0;
int byte_recibido = 0;
int timeOut = 1000;
RxRes paquete;


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

/* FUNCIONS PER A CANVIAR EL SENTIT DE RECEPCIO */

void Sentit_Dades_Rx(void)
{
	//Configuració del Half Duplex dels motors: Recepció
	P3OUT &= ~0x80; //El pin P3.7 (DIRECTION_PORT) el posem a 0 (Rx)
}

void Sentit_Dades_Tx(void)
{
	//Configuració del Half Duplex dels motors: Transmissió
	P3OUT |= 0x80; //El pin P3.7 (DIRECTION_PORT) el posem a 1 (Tx)
}

/* funció TxUAC0(byte): envia un byte de dades per la UART 0 */
void TxUAC0(byte bTxdData)
{
	while(!TXD0_READY); // Espera a que estigui preparat el buffer de transmissió
	UCA0TXBUF = bTxdData;
}

/*
TxPacket() necessita 3 paràmetres; ID del Dynamixel, Instruction byte, Mida dels paràmetres.
TxPacket() torna la mida del "Return packet" des del Dynamixel.
*/
byte TxPacket(byte bID, byte bParameterLength, byte bInstruction)
{
	byte bCount,bCheckSum,bPacketLength;
	byte gbpTxBuffer[32];
	volatile int i = 50;
	char error[] = "adr. no permitida";
	if ((gbpParameter[0]<5)&&(bInstruction==3)){		//Si intentem escriure en posicions conflictives del robot
		//si se intenta escribir en una direccion <= 0x05,
	    //emitir mensaje de error de direccion prohibida:
	    halLcdPrintLine( error, 5, OVERWRITE_TEXT);
	    //y salir de la funcion sin mas:
	    return 0;
	}
	Sentit_Dades_Tx(); //El pin P3.7 (DIRECTION_PORT) el posem a 1 (Tx)
	gbpTxBuffer[0] = 0xFF; //Primers 2 bytes que indiquen inici de trama FF, FF.
	gbpTxBuffer[1] = 0xFF;
	gbpTxBuffer[2] = bID; //ID del mòdul al que volem enviar el missatge
	gbpTxBuffer[3] = bParameterLength+2; //Length(Parameter,Instruction,Checksum)
	gbpTxBuffer[4] = bInstruction; //Instrucció que enviem al mòdul

	for(bCount = 0; bCount < bParameterLength; bCount++)//Comencem a generar la trama
	{
		gbpTxBuffer[bCount+5] = gbpParameter[bCount];
	}
	bCheckSum = 0;
	bPacketLength = bParameterLength+4+2;

	for(bCount = 2; bCount < bPacketLength-1; bCount++) //Càlcul del Checksum
	{
		bCheckSum += gbpTxBuffer[bCount];
	}
	gbpTxBuffer[bCount] = ~bCheckSum; //Escriu el Checksum (complement a 1)

	for(bCount = 0; bCount < bPacketLength; bCount++) //Aquest bucle és el que envia la trama
	{
		TxUAC0(gbpTxBuffer[bCount]);
	}
	while((UCA0STAT&UCBUSY)); //Espera fins s’ha transmès el últim byte
	Sentit_Dades_Rx(); //Posem la línia de dades en Rx perquè el mòdul Dynamixel envia resposta
	return(bPacketLength);
}

/*
RxPacket() necessita 0 paràmetres.
RxPacket() retorna el "Status packet" demanat des del Dynamixel.
*/
RxRes RxPacket(void)
{
	RxRes respuesta;		// Variable on guardem el packet de resposta del robot
	byte bCount, bLength, bCheckSum;
	bCheckSum = 0;			// Inicialitzacio del CheckSum
	timeOut = 1000;
	byte_recibido = 0;		// Netejem el flag de byte_recibido de la UART
	Sentit_Dades_Rx();

	for (bCount = 0; bCount < 4; bCount++) {	//Rebem els primers 4 bytes de la trama
		timeOut = 1000;
		while (!byte_recibido) {		//Esperem a la interrupcio de la UART
			if (timeOut <= 0)break;		//Si es passa el temps del TimeOut, acabem la funció
		}
		if (timeOut <= 0) {
			halLcdPrintLine("Error TimeOut", 5, OVERWRITE_TEXT);	//Amb un missatge de error de TimeOut
			return respuesta;
		}
		byte_recibido = 0;
		respuesta.Packet[bCount] = byte_UART;	//En cas de "no TimeOut", rebem el byte de la UART
	}
	bLength = respuesta.Packet[3] + 4;		//Trobem el tamany total de la trama amb el bLength
	for (bCount = 4; bCount < bLength; bCount++) {	//Rebem la resta de bytes de la trama
		timeOut = 1000;
		while (!byte_recibido) {		//Esperem a la interrupcio de la UART
			if (timeOut <= 0)break;		//Si es passa el temps del TimeOut, acabem la funció
		}
		if (timeOut <= 0) {
			halLcdPrintLine("Error TimeOut", 5, OVERWRITE_TEXT);	//Amb un missatge de error de TimeOut
			return respuesta;
		}
		byte_recibido = 0;
		respuesta.Packet[bCount] = byte_UART;	//En cas de "no TimeOut", rebem el byte de la UART
	}
	for(bCount = 2; bCount < bLength - 1; bCount++) { //Càlcul del Checksum
		bCheckSum += respuesta.Packet[bCount];
	}
	bCheckSum = bCheckSum + respuesta.Packet[bLength - 1]; //Si el CheckSum es correcto, esto dara 0xFF
	if (bCheckSum != 0xFF) {
		halLcdPrintLine("Error CheckSum", 5, OVERWRITE_TEXT); 		//Si hi ha error de CheckSum, es mostra un missatge
		return respuesta;
	}
	return respuesta;
}

/*
 * Funciones para mover el robot;
 * Las basicas van a ser mover adelante, atras, y los dos sentidos de giro.
 * Tambien una funcion auxiliar para configurar el motor en giro continuo,
 * y una funcion para parar el movimiento.
 *
 */

/* Configuracion de los registros del 6 al 9 para poner los motores en Modo Continuo */
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

/* Mover para adelante */
void mov_adelante(byte velocidad)
{
	gbpParameter[0] = 0x20;			// Escribimos en las posiciones de memoria 20 y 21 (Velocidad del motor)
	gbpParameter[1] = velocidad;	// Pasamos por parametro la velocidad a poner en el motor
	gbpParameter[2] = 0x04;
	TxPacket(0x01, 3, 0x04);		// Enviamos REG_WRITE al motor 1
	paquete = RxPacket();
	TxPacket(0x02, 3, 0x04);		// Enviamos REG_WRITE al motor 2
	paquete = RxPacket();

	gbpParameter[0] = 0x20;			// Hacemos lo mismo con los otros dos motores, pero en sentido contrario
	gbpParameter[1] = velocidad;	// ya que estan girados fisicamente
	gbpParameter[2] = 0x00;
	TxPacket(0x03, 3, 0x04);		// Enviamos REG_WRITE al motor 3
	paquete = RxPacket();
	TxPacket(0x04, 3, 0x04);		// Enviamos REG_WRITE al motor 4
	paquete = RxPacket();

	TxPacket(0xFE, 0, 0x05);		// Instruccion ACTION con el ID de Broadcast para iniciar el movimiento hacia adelante
}

/* Mover para atras */
void mov_atras(byte velocidad)
{
	gbpParameter[0] = 0x20;			// Escribimos en las posiciones de memoria 20 y 21 (Velocidad del motor)
	gbpParameter[1] = velocidad;	// Pasamos por parametro la velocidad a poner en el motor
	gbpParameter[2] = 0x00;
	TxPacket(0x01, 3, 0x04);		// Enviamos REG_WRITE al motor 1
	paquete = RxPacket();
	TxPacket(0x02, 3, 0x04);		// Enviamos REG_WRITE al motor 2
	paquete = RxPacket();

	gbpParameter[0] = 0x20;			// Hacemos lo mismo con los otros dos motores, pero en sentido contrario
	gbpParameter[1] = velocidad;	// ya que estan girados fisicamente
	gbpParameter[2] = 0x04;
	TxPacket(0x03, 3, 0x04);		// Enviamos REG_WRITE al motor 3
	paquete = RxPacket();
	TxPacket(0x04, 3, 0x04);		// Enviamos REG_WRITE al motor 4
	paquete = RxPacket();

	TxPacket(0xFE, 0, 0x05);		// Instruccion ACTION con el ID de Broadcast para iniciar el movimiento hacia atras
}

/* Giro hacia la derecha */
void giro_derecha(void)
{
	gbpParameter[0] = 0x20;			// Escribimos en las posiciones de memoria 20 y 21 (Velocidad del motor)
	gbpParameter[1] = 0xFF;			// Pasamos por parametro la velocidad a poner en el motor
	gbpParameter[2] = 0x04;
	TxPacket(0x01, 3, 0x04);		// Enviamos REG_WRITE al motor 1
	paquete = RxPacket();
	TxPacket(0x02, 3, 0x04);		// Enviamos REG_WRITE al motor 2
	paquete = RxPacket();

	gbpParameter[0] = 0x20;			// Hacemos lo mismo con los otros dos motores, pero en sentido contrario
	gbpParameter[1] = 0xFF;			// ya que estan girados fisicamente
	gbpParameter[2] = 0x04;
	TxPacket(0x03, 3, 0x04);		// Enviamos REG_WRITE al motor 3
	paquete = RxPacket();
	TxPacket(0x04, 3, 0x04);		// Enviamos REG_WRITE al motor 4
	paquete = RxPacket();

	TxPacket(0xFE, 0, 0x05); 		// Instruccion ACTION con el ID de Broadcast para iniciar el giro a la derecha
}

/* Giro hacia la izquierda */
void giro_izquierda(void)
{
	gbpParameter[0] = 0x20;			// Escribimos en las posiciones de memoria 20 y 21 (Velocidad del motor)
	gbpParameter[1] = 0xFF;			// Pasamos por parametro la velocidad a poner en el motor
	gbpParameter[2] = 0x00;
	TxPacket(0x01, 3, 0x04);		// Enviamos REG_WRITE al motor 1
	paquete = RxPacket();
	TxPacket(0x02, 3, 0x04);		// Enviamos REG_WRITE al motor 2
	paquete = RxPacket();

	gbpParameter[0] = 0x20;			// Hacemos lo mismo con los otros dos motores, pero en sentido contrario
	gbpParameter[1] = 0xFF;			// ya que estan girados fisicamente
	gbpParameter[2] = 0x00;
	TxPacket(0x03, 3, 0x04);		// Enviamos REG_WRITE al motor 3
	paquete = RxPacket();
	TxPacket(0x04, 3, 0x04);		// Enviamos REG_WRITE al motor 4
	paquete = RxPacket();

	TxPacket(0xFE, 0, 0x05);		// Instruccion ACTION con el ID de Broadcast para iniciar el giro a la izquierda
}

/* PARAR LOS MOTORES */
void halt_motores(void)
{
	gbpParameter[0] = 0x20;			// Escribimos en las posiciones de memoria 20 y 21 (Velocidad del motor)
	gbpParameter[1] = 0x00;			// Pasamos por parametro la velocidad a poner en el motor
	gbpParameter[2] = 0x00;
	TxPacket(0x01, 3, 0x04);		// Enviamos REG_WRITE al motor 1
	paquete = RxPacket();
	TxPacket(0x02, 3, 0x04);		// Enviamos REG_WRITE al motor 2
	paquete = RxPacket();

	gbpParameter[0] = 0x20;			// Hacemos lo mismo con los otros dos motores, pero en sentido contrario
	gbpParameter[1] = 0x00;			// ya que estan girados fisicamente
	gbpParameter[2] = 0x00;
	TxPacket(0x03, 3, 0x04);		// Enviamos REG_WRITE al motor 3
	paquete = RxPacket();
	TxPacket(0x04, 3, 0x04);		// Enviamos REG_WRITE al motor 4
	paquete = RxPacket();

	TxPacket(0xFE, 0, 0x05);		// Instruccion ACTION con el ID de Broadcast que para todo el movimiento
}

/*
 * Funciones para leer los sensores;
 * Tres funciones para leer los sensores frontal, derecho e izquierdo.
 */

/* Leer sensor frontal */
RxRes leer_sensor_frontal(void)
{
	gbpParameter[0] = 0x1B;			// Leemos la direccion 1B
	gbpParameter[1] = 0x01;			// De los sensores, cuyo ID es 100 (0x64)
	TxPacket(0x64, 2, 0x02);
	paquete = RxPacket();

	return paquete;
}

/* Leer sensor derecho */
RxRes leer_sensor_derecho(void)
{
	gbpParameter[0] = 0x1C;			// Leemos la direccion 1C
	gbpParameter[1] = 0x01;			// De los sensores, cuyo ID es 100 (0x64)
	TxPacket(0x64, 2, 0x02);
	paquete = RxPacket();

	return paquete;
}

/* Leer sensor izquierdo */
RxRes leer_sensor_izquierdo(void)
{
	gbpParameter[0] = 0x1A; 		// Leemos la direccion 1A
	gbpParameter[1] = 0x01;			// De los sensores, cuyo ID es 100 (0x64)
	TxPacket(0x64, 2, 0x02);
	paquete = RxPacket();

	return paquete;
}

void main(void)
 {

  	WDTCTL = WDTPW+WDTHOLD;       	// Paramos el watchdog timer

  	init_botons();					// Iniciamos los botones y Leds.
  	init_timers();					// Iniciamos el Timer B.
  	init_UCS();						// Iniciamos la UCS y ponemos SMCLK a 16MHz.
  	init_UART();						// Iniciamos la UART para comunicarnos con el robot.
  	config_P4_LEDS();				// Iniciamos los Leds.
  	_enable_interrupt(); 			// Activamos las interrupciones a nivel global del chip
    init_LCD();						// Inicializamos la pantalla
    config_motores();				// Ponemos los motores en modo continuo
  
  	escribir(saludo,linea); 		//escribimos saludo en la primera linea
  	linea++; 						//Aumentamos el valor de linea y con ello pasamos a la linea siguiente

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

	gbpParameter[0] = 0x19;		//Posicion de memoria a leer
	gbpParameter[1] = 1;		//Cantidad de posiciones a leer
	TxPacket(0x02, 2, 0x02);	//Enviamos la peticion para leer
	paquete = RxPacket();		//Recibimos el paquete de respuesta
	sprintf(cadena, "ID: %d STAT: %d", paquete.Packet[2], paquete.Packet[5]);	//Imprimimos el status del LED del ID 0x02
	escribir(cadena, 4);

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
   		gbpParameter[0] = 0x19;		//PARAMETRES PER A ENCENDRE UN LED DEL MOTOR.
   		if (LED_flag3 == 1) {
   			gbpParameter[1] &= 0x00;
   			LED_flag3 = 0;
   		} else {
   			gbpParameter[1] |= 0x01;
   			LED_flag3 = 1;
   		}
   		TxPacket(0x03, 2, 0x03);			//ENCENDEMOS EL LED DEL MOTOR3.
   		RxPacket();
   		mov_adelante(0xFF);				//HACEMOS AVANZAR AL ROBOT

   		estado = 0;
   		estado_anterior = 8;
    }

   	if (estado == 7 ) {
   		gbpParameter[0] = 0x19;		//PARAMETRES PER A ENCENDRE UN LED DEL MOTOR.
   		if (LED_flag4 == 1) {
   			gbpParameter[1] &= 0x00;
   			LED_flag4 = 0;
   		} else {
   			gbpParameter[1] |= 0x01;
   			LED_flag4 = 1;
   		}
   		TxPacket(0x04, 2, 0x03);			//ENCENDEMOS EL LED DEL MOTOR4.
   		RxPacket();
   		mov_atras(0xFF);				//HACEMOS RETROCEDER AL ROBOT

   		estado = 0;
   		estado_anterior = 8;
    }

   	if (estado == 3) {
   	  gbpParameter[0] = 0x19;		//PARAMETRES PER A ENCENDRE UN LED DEL MOTOR.
   	  if (LED_flag1 == 1) {
   		  gbpParameter[1] &= 0x00;
   		  LED_flag1 = 0;
   	  } else {
   		  gbpParameter[1] |= 0x01;
   		  LED_flag1 = 1;
   	  }
   	  TxPacket(0x01, 2, 0x03);			//ENCENDEMOS EL LED DEL MOTOR1.
   	  RxPacket();
   	  giro_derecha();				//HACEMOS GIRAR A LA DERECHA AL ROBOT
   	  delay(2430);
   	  halt_motores();				//TRAS 2'5 SEGUNDOS, PARAMOS EL GIRO

   	  estado = 0;
   	  estado_anterior = 8;
    }

    if (estado == 4) {
      gbpParameter[0] = 0x19;		//PARAMETRES PER A ENCENDRE UN LED DEL MOTOR.
      if (LED_flag2 == 1) {
          gbpParameter[1] &= 0x00;
          LED_flag2 = 0;
      } else {
    	  gbpParameter[1] |= 0x01;
    	  LED_flag2 = 1;
      }
      TxPacket(0x02, 2, 0x03);			//ENCENDEMOS EL LED DEL MOTOR2.
      RxPacket();
      giro_izquierda();				//HACEMOS GIRAR A LA IZQUIERDA AL ROBOT
      delay(2430);
      halt_motores();				//TRAS 2'5 SEGUNDOS, PARAMOS EL GIRO


      estado = 0;
      estado_anterior = 8;
    }

    if (estado == 2) {
    	halt_motores();				//PAREM AMB EL BOTO S2 TOT EL MOVIMENT DEL ROBOT

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
		 	 clkf = estado;
		 	 break;
	 case 0x80: /* Estado 2, BOTON S2 */
		 	 P1OUT = 0x01;		//Amb aquesta modificacio de P1OUT, 
		 	 estado = 2;		//Marquem, a la variable "estado", que ens trobem al estat 2.
		 	 clkf = estado;
		 	 break;
	 case 0x02: /* Estado 3, Joystick Izquierda */
		 	 P1OUT &= 0x00;		//Amb aquesta modificacio de P1OUT, 
		 	 estado = 3;		//Marquem, a la variable "estado", que ens trobem al estat 3.
		 	 clkf = estado;
		 	 break;
	 case 0x04: /* Estado 4, Joystick Derecha */
	 		 P1OUT &= 0x00;		//Amb aquesta modificacio de P1OUT, 
	 		 estado = 4;		//Marquem, a la variable "estado", que ens trobem al estat 4.
	 		 clkf = estado;
	 		 break;
	 case 0x08: /* Estado 5, Joystick Centro */
	 		 P1OUT = 0x02;		//Amb aquesta modificacio de P1OUT, 
	 		 estado = 5;		//Marquem, a la variable "estado", que ens trobem al estat 5.
	 		 clkf = estado;
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


	/***********************************************
   	 * HASTA AQUI BLOQUE CASE
   	 ***********************************************/	
	
	P2IFG = 0;		//limpiamos todas las interrupciones
	P2IE |= 0xC0; 	//interrupciones botones S1 y S2 (P2.6 y P2.7) reactivadas
	P2IE |= 0x3E;  //interrupciones joystick (2.1-2.5) reactivadas
 return;
}

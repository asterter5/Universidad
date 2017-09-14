/*
 * libreria_robot.c
 *
 *  Created on: 06/05/2015
 *      Author: mat.aules
 */

#include <msp430x54xA.h>
#include <stdio.h>
#include "hal_lcd.h"
#include "libreria_robot.h"

byte gbpParameter[32];				// Array para los parametros de Tx.
int byte_UART = 0;
int byte_recibido = 0;
int timeOut = 1000;
int cont = 1;
int cMicro = 0;
RxRes paquete;

/**************************************************************************
 *
 * FUNCIONES PARA COMUNICARSE CON EL ROBOT.
 *
 **************************************************************************/

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
	UCA0TXBUF = bTxdData; // Pone el byte del buffer de la UART del micro en el bus de transmision
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
			halLcdPrintLine("Error TimeOut", 4, OVERWRITE_TEXT);	//Amb un missatge de error de TimeOut
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
			halLcdPrintLine("Error TimeOut", 4, OVERWRITE_TEXT);	//Amb un missatge de error de TimeOut
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
		halLcdPrintLine("Error CheckSum", 4, OVERWRITE_TEXT); 		//Si hi ha error de CheckSum, es mostra un missatge
		return respuesta;
	}
	return respuesta;
}

/**************************************************************************
 *
 * FUNCIONES PARA MOVER LOS MOTORES DEL ROBOT.
 *
 * Funciones para mover el robot;
 * Las basicas van a ser mover adelante, atras, y los dos sentidos de giro.
 * Tambien una funcion auxiliar para configurar el motor en giro continuo,
 * y una funcion para parar el movimiento.
 *
 **************************************************************************/

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

	TxPacket(0xFE, 0, 0x05); 		// Instruccion ACTION con el ID de Broadcast para iniciar el giro a la derecha
}

/* Giro para la derecha mientras avanza */
void giro_derecha_mod(void)
{
	gbpParameter[0] = 0x20;			// Escribimos en las posiciones de memoria 20 y 21 (Velocidad del motor)
	gbpParameter[1] = 0x70;			// Pasamos por parametro la velocidad a poner en el motor
	gbpParameter[2] = 0x04;
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

	TxPacket(0xFE, 0, 0x05);
}

/* Giro hacia la izquierda */
void giro_izquierda(void)
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

	TxPacket(0xFE, 0, 0x05);		// Instruccion ACTION con el ID de Broadcast para iniciar el giro a la izquierda
}

/* Giro para la izquierda mientras avanza */
void giro_izquierda_mod(void)
{
	gbpParameter[0] = 0x20;			// Escribimos en las posiciones de memoria 20 y 21 (Velocidad del motor)
	gbpParameter[1] = 0xFF;			// Pasamos por parametro la velocidad a poner en el motor
	gbpParameter[2] = 0x04;
	TxPacket(0x01, 3, 0x04);		// Enviamos REG_WRITE al motor 1
	paquete = RxPacket();
	TxPacket(0x02, 3, 0x04);		// Enviamos REG_WRITE al motor 2
	paquete = RxPacket();

	gbpParameter[0] = 0x20;			// Hacemos lo mismo con los otros dos motores, pero en sentido contrario
	gbpParameter[1] = 0x70;			// ya que estan girados fisicamente
	gbpParameter[2] = 0x00;
	TxPacket(0x03, 3, 0x04);		// Enviamos REG_WRITE al motor 3
	paquete = RxPacket();
	TxPacket(0x04, 3, 0x04);		// Enviamos REG_WRITE al motor 4
	paquete = RxPacket();

	TxPacket(0xFE, 0, 0x05);
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

/**************************************************************************
 *
 * FUNCIONES PARA LEER LOS SENSORES IR DEL MODULO AX-S1.
 *
 * Funciones para leer los sensores;
 * Tres funciones para leer los sensores frontal, derecho e izquierdo.
 *
 **************************************************************************/

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

/* Leer el microfono del AX-S1 */
RxRes leer_microfono(void)
{
	gbpParameter[0] = 0x25; 		// Leemos la direccion 23 (micro)
	gbpParameter[1] = 0x01;			// De los sensores, cuyo ID es 100 (0x64)
	TxPacket(0x64, 2, 0x02);
	paquete = RxPacket();

	return paquete;
}

/**************************************************************************
 *
 * FUNCIONES PARA USAR EL BUZZER DEL MODULO AX-S1.
 *
 * Funciones para reproducir notas;
 * Funcion para reproducir una serie de notas concatenadas.
 *
 **************************************************************************/

/* Reproducir una nota en el AX-S1 */
void reproducir_nota(byte nota, byte duracion)
{
	gbpParameter[0] = 0x28;
	gbpParameter[1] = nota;
	gbpParameter[2] = duracion;
	TxPacket(0x64, 3, 0x03);
	paquete = RxPacket();
}

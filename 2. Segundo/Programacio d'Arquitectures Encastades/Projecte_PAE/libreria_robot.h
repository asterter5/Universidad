/*
 * libreria_robot.h
 *
 *  Created on: 06/05/2015
 *      Author: mat.aules
 */

#include <msp430x54xA.h>
#include <stdio.h>
#include "hal_lcd.h"

#ifndef LIBRERIA_ROBOT_H_
#define LIBRERIA_ROBOT_H_

typedef unsigned char byte; 			//DEFINIM EL TIPUS BYTE
#define TXD0_READY (UCA0IFG & UCTXIFG)
#define RXD0_READY (UCA0IFG & UCRXIFG)

typedef struct {
	byte Packet[32];			//DEFINIM EL PAQUET QUE RETORNARA RxPacket()
} RxRes;

/* FUNCIONES DE COMUNICACION CON EL ROBOT */

void Sentit_Dades_Rx(void);

void Sentit_Dades_Tx(void);

void TxUAC0(byte bTxdData);

byte TxPacket(byte bID, byte bParameterLength, byte bInstruction);

RxRes RxPacket(void);

/* FUNCIONES PARA MOVER LOS MOTORES */

void mov_adelante(byte velocidad);

void mov_atras(byte velocidad);

void giro_derecha(void);

void giro_derecha_mod(void);

void giro_izquierda(void);

void giro_izquierda_mod(void);

void halt_motores(void);

/* FUNCIONES PARA LEER LOS SENSORES */

RxRes leer_sensor_frontal(void);

RxRes leer_sensor_derecho(void);

RxRes leer_sensor_izquierdo(void);

RxRes leer_microfono(void);

/* FUNCIONES PARA REPRODUCIR SONIDOS */

void reproducir_nota(byte nota, byte duracion);

#endif /* LIBRERIA_ROBOT_H_ */

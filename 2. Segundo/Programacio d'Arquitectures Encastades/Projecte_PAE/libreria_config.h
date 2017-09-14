/*
 * libreria_config.h
 *
 *  Created on: 06/05/2015
 *      Author: mat.aules
 */

#include <msp430x54xA.h>
#include <stdio.h>
#include "hal_lcd.h"
#include "libreria_robot.h"

#ifndef LIBRERIA_CONFIG_H_
#define LIBRERIA_CONFIG_H_

/*
 * Funcions per a configurar totes les parts del microcontrolador.
 */

void init_botons(void);

void config_P4_LEDS(void);

void init_LCD(void);

void init_timers(void);

void init_UCS(void);

void init_UART(void);

void config_motores(void);


#endif /* LIBRERIA_CONFIG_H_ */

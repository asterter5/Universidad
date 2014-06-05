/**
programa per realitzat per estudiar les interrupcions
treballa a nivell de registres.
Registres implicats:

T1CON 	Registre de control del timer
TMR1	Registre incrementador
IE 		Registre d'habilitació d'interrupcions
IF		Registre de flags associat a les interrupcions
PR1		valor al qual volem arribar amb el timer...

Programa realitzat per 
		Manel López
		Data:	1/1/2011
		revisió	2/5/2011
*/

#include <p24fj128ga010.h>
#include "spieeprom.h"
#include "spi2.h"
#include <timer.h>

#define DEFAULT_VALUE	0x0000
#define PRESCALER_1_256 0x0030
#define PRESCALER_1_64	0x0020
#define PRESCALER_1_8	0x0010
#define PRESCALER_1_1	0x0000
#define VALOR_FINAL 	0xFFFF
//PER DESCONFIGURAR EL JTAG I PODER ATACAR A TOTS ELS LEDS CLIQUEU A CONFIGURE. SELECCIONEU
//CONFIGURATION BITS. A LA OPCIO JTAGEN CLIQUEU I POSEU DISABLE

//LES OPCIONS DE CLOCK DEL SISTEMA...
//POSMOD HS
//FNOSC PRIMARY OSCILLATOR (xt, HS, EC)

//JUGEU AMB EL PRESCALER DINS LA FUNCIO initialaizeTimer1()

void initialize(void){
	TRISA = 0x0000;//configura el port A (on està connectada la bateria de LEDS com a sortida

	PORTA = 0x0003;//encen tots els leds 
	TRISD |=0x00C0;//configurem RD6 com entrada sw3 

}
void initializeTimer1(void){
	//configurem registre de control del timer 
	T1CON = DEFAULT_VALUE;
	//INTRODUIM UN PRESCALER VOL DIR QUE CADA COP QUE DECREMENTEM 1 CONTEM FINS A 256...
	T1CON |= PRESCALER_1_64;
	//POSEM EL CONTINGUT DEL CONTADOR A 0 INICIALMENT...
	TMR1 = 0;
	//VALOR AL QUAL HA D'ARRIBAR EL CONTADOR
	PR1 = VALOR_FINAL;
	//PRIORITAT DE LA INTERRUPCIO ASSOCIADA AL TIMER = 1
	IPC0bits.T1IP =0x01;
	//ESBORREM EL FLAG DE LA INTERRUPCIO PER PERMETRE EL SALT DE NOU
	IFS0bits.T1IF = 0;
	// HABILITEM LA INTERRUPCIO Interrupt Enable IE del timer1
	IEC0bits.T1IE = 1;
}

int main(void){

	unsigned char input[8] = "hola mon";
	unsigned char output[8] = "";
	int i=0;//definim una variable
	int addr;//variable per a les adreces

	initialize();
	SPI2INTInit();
	EEPROMInit();
	initializeTimer1();
	
	//llencem el timer 1!!!
	T1CONbits.TON = 1;
		
	while(1){
		if(!(PORTD & 0x0040)){ //mira si el switch S3 esta apretat. si es correcte entra en el bucle
			for (i=0;i<8;i++)
				EEPROMWriteByte(input[i], 0x10+i);
		}
		if(!(PORTD & 0x0050)){
			for (i=0;i<8;i++)
				output[i] = EEPROMReadByte(0x10+i);
		}
	}
	return 0;
}


void __attribute__((__interrupt__, __shadow__)) _T1Interrupt(void)
{

/* Interrupt Service Routine code goes here         */
	int i;
	PORTA ^=0x80;
	IFS0bits.T1IF  = 0;
	for (i=0;i<0xFFFF;i++);
	PORTA ^=0x80;
}

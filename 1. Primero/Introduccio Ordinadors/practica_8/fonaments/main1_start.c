#include <p24fj128ga010.h>


void initialize(void){
	TRISA = 0x0000;//configura el port A (on està connectada la bateria de LEDS com a sortida

	PORTA = 0xffff;//encen tots els leds 
	TRISD |=0x0040;//configurem RD6 com entrada sw3 

}
int main(void){
	int i;//definim una variable
	initialize();
	for (i=0;i<0xffff;i++);//un contador per retardar l'entrada del while, no fa res
	while(1){
		if(!(PORTD & 0x0040))//mira si el switch S3 esta apretat. si es correcte entra en el bucle
			PORTA ^=0xff;
		}
	return 0;
}

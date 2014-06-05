#include <p24fj128ga010.h>


void initialize(void){
	TRISA = 0x0000;//configura el port A (on està connectada la bateria de LEDS com a sortida

	PORTA = 0xffff;//encen tots els leds 
	TRISD |=0x20c0;//configurem RD6, RD7 i RD13 com entrada sw3 
	

}
int main(void){
	int i;//definim una variable
	initialize();
	for (i=0;i<0x0003;i++);//un contador per retardar l'entrada del while, no fa res
	while(1){
		if(!(PORTD & 0x0040))//mira si el switch S3 esta apretat. si es correcte entra en el bucle
			PORTA = 0xff;//ENCEN TOT
		else if(!(PORTD & 0x0080))//mira si el switch S6 esta apretat. si es correcte entra en el bucle
			PORTA = 0x00;//APAGA TOT
		else if(!(PORTD & 0x2000))//mira si el switch S4 esta apretat. si es correcte entra en el bucle
			PORTA ^=0x55;//ENCEN o APAGA ELS 0101|0101
	}		
	return 0;
}

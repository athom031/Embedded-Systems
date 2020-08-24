/*	Author: Alex Thomas
 *  Assignment: Lab #8  Exercise #3
 *	Exercise Description: 
 *
 *	Analog Digital Conversion with photoresistor 
 *
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}


unsigned short MAX = 0x0FF;
unsigned short tmp = 0x00;


//unsigned short AD_convert = 0x00;


int main(void) {

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	ADC_init();

    while (1) {
		tmp = ADC;
		if(tmp >= MAX / 2) {
			PORTB = 0xFF;
			PORTD = 0x03;
		}
		else {
			PORTB = 0x00;
			PORTD = 0x00;
		}
	}
    return 1;
}

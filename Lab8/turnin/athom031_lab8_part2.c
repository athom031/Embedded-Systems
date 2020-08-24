/*	Author: Alex Thomas
 *  Partner(s) Name: 
 *	Lab Section: 021
 *	Assignment: Lab #8  Exercise #2
 *	Exercise Description: 
 *
 *	Analog Digital Conversion -> photoresistor
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


unsigned short AD_convert = 0x00;


int main(void) {

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	ADC_init();

    while (1) {

	AD_convert = ADC;
	PORTB = (char)AD_convert;
	PORTD = (char)(AD_convert >> 8);

    }
    return 1;
}

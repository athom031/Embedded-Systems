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
unsigned short MAX_8th = 0x00;

unsigned short tmp = 0x00;


//unsigned short AD_convert = 0x00;


int main(void) {

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
//	DDRD = 0xFF; PORTD = 0x00;

	ADC_init();

    while (1) {
		tmp = ADC;
		MAX_8th = MAX / 8;		
		if(tmp >= MAX_8th * 8) {
			PORTB = 0x80;
		}
		else if(tmp >= MAX_8th * 7) {
			PORTB = 0x40;
		}
		else if(tmp >= MAX_8th * 6) {
			PORTB = 0x20;
		}
		else if(tmp >= MAX_8th * 5) {
			PORTB = 0x10;
                }
                else if(tmp >= MAX_8th * 4.5) {
			PORTB = 0x08;
                }
		else if(tmp >= MAX_8th * 4) {
			PORTB = 0x04;
                }
                else if(tmp >= MAX_8th * 3.5) {
			PORTB = 0x02;
                }	
		else {
			PORTB = 0x01;
		}

	}
    return 1;
}

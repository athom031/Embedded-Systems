/*	Author: alex
 *  Partner(s) Name: 
 *	Lab Section: 021
 *	Assignment: Lab #3  Exercise #4
 *	Exercise Description: 
 *      	CHALLENGE: Bit Shifting
 * 		upper and lower Nibble
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;
	
	while(1) {
		tmpA = PINA;
		tmpB = tmpA;
		tmpC = tmpA;
		
		// upper nibble of PINA mapped to lower nibble of PORTB
		tmpB = tmpB >> 4;
		
		// lower nibble of PINA mapped to upper nibble of PORTC
		tmpC = tmpC << 4;

		
		PORTB = tmpB;
		PORTC = tmpC;
	}
	return 0;
}

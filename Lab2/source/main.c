/*	Author: alex
 *  Partner(s) Name: 
 *	Lab Section: 021
 *	Assignment: Lab #2  Exercise #4 (Challenge)
 *      Description:
 *      amusement park ride seat weight restrictions
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
  	/* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; // config port A's 8 pins as first seat input
	DDRB = 0x00; PORTB = 0xFF; // config port B's 8 pins as second seat input
	DDRC = 0x00; PORTC = 0xFF; // config port C's 8 pins as third seat input
	DDRD = 0xFF; PORTD = 0x00; // config port D's 8 pins as our output


	unsigned char totWeight = 0x00; // calculate how whats the total weight of A + B + C
	unsigned char difWeight = 0x00; // calculate the difference in weight between A and C for balance
	unsigned char tmpA = 0x00; // temp variable to hold values of A
	unsigned char tmpB = 0x00; // temp variable to hold values of B
	unsigned char tmpC = 0x00; // temp variable to hold values of C
	unsigned char tmpD = 0x00; // temp variable to hold output value of D
	
	while (1) {
		//1) read input no need for mask -> need whole thing
		tmpA = PINA;
		tmpB = PINB;
		tmpC = PINC;

		totWeight = tmpA + tmpB + tmpC;
		if(totWeight > 0x8C) {
			tmpD = 0x01 | tmpD;
				//this means our weight is over 140
		}
		else {	
			tmpD = 0xFE & tmpD;
		}
		
		//we have unsigned so just don't get into negative values 
		if(tmpA > tmpC) {
			difWeight = tmpA - tmpC;
			
		}	
		else {
			difWeight = tmpC - tmpA;
		}
		
		if(difWeight > 0x50) {
			tmpD = 0x02 | tmpD;
		}
		else {
			tmpD = 0xFD & tmpD;
		}

		//shift two bits left

		tmpD = tmpD & 0x03;
		totWeight = totWeight & 0xFC;		
		tmpD = totWeight | tmpD;

		PORTD = tmpD;
	}
	return 0;
}

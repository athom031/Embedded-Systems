/*	Author: alex
 *  Partner(s) Name: 
 *	Lab Section: 021
 *	Assignment: Lab #3  Exercise #1
 *	Exercise Description: 
 *      	count the number of 1's in port A and port B
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
  	/* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; // config port A's 8 pins as input
	DDRB = 0x00; PORTB = 0xFF; // config port B's 8 pins as input

	DDRC = 0xFF; PORTC = 0x00; // config port C's 8 pins as outputs
	
	/* tmp variables */
	unsigned char cntOnes = 0x00; // temp variable that num of 1
	unsigned char tmpA = 0x00; // temp variable to hold values of A
	unsigned char tmpB = 0x00; // temp variable to hold values of B
	
	while (1) {
		tmpA = PINA;
		tmpB = PINB;
		
		cntOnes = 0x00;
				
		while(tmpA) {
			if(tmpA & 0x01) {
				cntOnes = cntOnes + 1;
			}
			tmpA = tmpA >> 1;
		}

		while(tmpB) {
			if(tmpB & 0x01) {
				cntOnes = cntOnes + 1;
			}
			tmpB = tmpB >> 1;
		}

		PORTC = cntOnes;
	}
	return 0;
}

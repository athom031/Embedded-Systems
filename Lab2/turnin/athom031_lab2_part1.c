/*	Author: alex
 *  Partner(s) Name: 
 *	Lab Section: 021
 *	Assignment: Lab #2  Exercise #1
 *      Description:
 *      turn on LED if garage door is left open at night
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
	DDRB = 0xFF; PORTB = 0x00; // config port B's 8 pins as outputs
	unsigned char tmpB = 0x00; // temp variable to hold values of B
	unsigned char tmpA = 0x00; // temp variable to hold values of A
	
	/* Insert your solution below */
	while (1) {
		//1) read input
		tmpA = PINA & 0x03;
		//2) perform computation
		// if PA0 is 1, set PB1PB0 = 01, else 10
		if(tmpA == 0x02) {
			tmpB = (tmpB & 0xFC) | 0x01; 
			//set tmpB to bbbbbb01
			//clear rightmost 2 bits -> set to 01
		}
		else { 
			tmpB = (tmpB & 0xFC);
		}		
		PORTB = tmpB;
	}
	return 0;
}

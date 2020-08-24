/*	Author: Alex Thomas
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: 
 *		increment/decrement output with button input
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

/*WORDING OF DEPRESS VERY CONFUSING
 -> THOUGHT IT MEANT WHEN BOTH BUTTONS ARE NOT BEING PRESSED COMPLETELY CHANGES PROBLEM
*/

/*
 Buttons are connected to PA0 and PA1. Output for PORTC is initially 7. 
 Pressing PA0 increments PORTC once (stopping at 9). 
 Pressing PA1 decrements PORTC once (stopping at 0). 
 If both buttons are depressed (even if not initially simultaneously), 
 PORTC resets to 0.
*/
  
enum States {Start, INIT, INC, DEC, WAIT_I, WAIT_D, RESET} state;

unsigned char tmpC = 0x00; // tmp variable to hold output
unsigned char tmpA = 0x00; // tmp variable to hold input
void Tick() {
	tmpA = PINA;

	switch(state) {
		case Start:
			tmpC = 0x07;
			PORTC = tmpC;
			state = INIT;
			break;
		case INIT:
			if((tmpA & 0x03) == 0x00) {
				state = INIT;
			}
			else if ((tmpA & 0x03) == 0x01) {
				state = INC;
			}
			else if ((tmpA & 0x03) == 0x02) {
				state = DEC;
			}
			else { //input is 0x03
				state = RESET;
			}
			break;
		case INC:
		case WAIT_I:
			if((tmpA & 0x03) == 0x00) {
				state = INIT;
			}
			else if ((tmpA & 0x03) == 0x01) {
				state = WAIT_I;
			}
			else if ((tmpA & 0x03) == 0x02) {
				state = DEC;
			}
			else { //input is 0x03
				state = RESET;
			}
			break;
		case DEC:
		case WAIT_D:
			if((tmpA & 0x03) == 0x00) {
				state = INIT;
			}
			else if ((tmpA & 0x03) == 0x01) {
				state = INC;
			}
			else if ((tmpA & 0x03) == 0x02) {
				state = WAIT_D;
			}
			else { //input is 0x03
				state = RESET;
			}
			break;
		case RESET:
			if((tmpA & 0x03) == 0x00) {
				state = INIT;
			}
			else if ((tmpA & 0x03) == 0x01) {
				state = INC;
			}
			else if ((tmpA & 0x03) == 0x02) {
				state = RESET;
			}
			else { //input is 0x03
				state = RESET;
			}
			break;
		default:
			break;
	} // state transitions go here
	
	switch(state) {
		case Start:
			break;
		case INIT:
			break;
		case INC:
			if(tmpC < 9) {
				tmpC += 1;
			}
			else {
				tmpC = 0x09;
			}
			PORTC = tmpC;
			break;
		case DEC:
			if(tmpC > 0) {
				tmpC -= 1;
			}
			else {
				tmpC = 0x00;
			}
			PORTC = tmpC;
			break;
		case WAIT_I:
			break;
		case WAIT_D:
			break;
		case RESET:
			tmpC = 0x00;
			PORTC = tmpC;
			break;
		default: 
			break;
	} // state actions go here
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;     
	DDRC = 0xFF; PORTC = 0x00;
	
	state = Start;
	while(1) {
		Tick();
	
	}	
	return 0;
}

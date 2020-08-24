/*	Author: alex
 *  Partner(s) Name: 
 *	Lab Section: 021
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: 
 *		Door Opener KeyPad
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

/*
 A household has a digital combination deadbolt lock system on the doorway. 
 The system has buttons on a keypad. 
 Button 'X' connects to PA0, 'Y' to PA1, and '#' to PA2. 
 Pressing and releasing '#', then pressing 'Y', should unlock the door 
 	by setting PB0 to 1. Any other sequence fails to unlock. 
 Pressing a button from inside the house (PA7) locks the door (PB0=0). For debugging 
 purposes, give each state a number, and always write the current state to PORTC 
 (consider using the enum state variable). 
 Also, be sure to check that only one button is pressed at a time. 
*/

/* 
 PA0 - 'X'
 PA1 - 'Y'
 PA2 - '#'
 
 i dont think we need a state to lock the door
 if ever PA7 is asserted we just set PB to 0 in any state

 we also dont need to save state number on port c because we can 
 find it in the test vector

 if ever multiple buttons being pressed at one time -> go to SeqStrt
*/

  
enum States {Start, SeqStrt, PRS_HASH, REL_HASH, PRS_Y, UNLCK_DR} state;

unsigned char tmpB = 0x00; // tmp variable to hold output
unsigned char tmpA = 0x00; // tmp variable to hold input
void Tick() {
	tmpA = PINA;
	switch(state) {
		case Start:
			tmpB = 0x00;
			PORTB = tmpB;
			state = SeqStrt;
			break;
		case SeqStrt:
			if((tmpA & 0x07) == 0x04) {
				state = PRS_HASH;
			}
			else {
				state = SeqStrt;
			}
			break;
		case PRS_HASH:
			if((tmpA & 0x07) == 0x04) {
				state = PRS_HASH;
			}
			else if((tmpA & 0x07) == 0x00) {
				//released the buttons 
				state = REL_HASH;
			}
			else {
				state = SeqStrt;
			}
			break;
		case REL_HASH:
			if((tmpA & 0x07) == 0x00) {
				state = REL_HASH;
			}
			else if((tmpA & 0x07) == 0x02) {
				state = PRS_Y;
			}
			else {
				state = SeqStrt;
			}
			break;
		case PRS_Y:
			state = UNLCK_DR;
			break;
		case UNLCK_DR:
			if((tmpA & 0x07) == 0x04) {
				state = PRS_HASH;
			}
			else {
				state = SeqStrt;
			}
			break;
	} //state transitions
	
	switch(state) {
		case Start:
			break;
		case SeqStrt:
		case PRS_HASH:
		case REL_HASH:
		case PRS_Y:
			if((tmpA & 0x80) == 0x80) {
				tmpB = 0x00;
				PORTB = tmpB;
			}
			break;
		case UNLCK_DR:
			tmpB = 0x01;
			PORTB = tmpB;
			break;
		default:
			break;
	} // state transitions go here
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;     
	DDRB = 0xFF; PORTB = 0x00;
	
	state = Start;
	while(1) {
		Tick();
	
	}	
	return 0;
}

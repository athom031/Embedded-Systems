/*	Author: Alex Thomas
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #2
 *	Exercise Description: Redo of Lab 4 Exercise 2
 *		more so the implementation onto our circuit boards
 *		update starting val to be 0 and not 7
 * 	
 * 	LAB DEMO: https://drive.google.com/open?id=1shazp8iuyXNJDLmK_94vHozME60KBNL2
 *
 * 	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

/*
 * Buttons are connected to PA0 and PA1
 * Output for PORTC is initially 0x00
 * Pressing A0 increments PORTC once (stopping at 9)
 * if both buttons are pressed PORTC reset to 0
 */

enum States {Start, INIT, INC, DEC, WAIT_I, WAIT_D, RESET} state;

unsigned char tmpC = 0x00; //tmp variable to hold output
unsigned char tmpA = 0x00; //tmp variable to hold input

void Tick() {
	tmpA = (~PINA & 0x03); //buttons are in pinout mode 

	switch(state) {
		case Start:
			tmpC = 0x00;
			PORTC = tmpC;
			state = INIT;
			break;
		case INIT:
			if(tmpA == 0x00) {
				state = INIT;
			}
			else if(tmpA == 0x01) {
				state = INC;
			}
			else if(tmpA == 0x02) {
				state = DEC;
			}
			else { //input is 0x03
				state = RESET;
			}
			break;
		case INC:
		case WAIT_I:
			if(tmpA == 0x00) {
				state = INIT;
			}
			else if(tmpA == 0x01) {
				state = WAIT_I; 
			}
			else if(tmpA == 0x02) {
				state = DEC;
			}
			else { //input is 0x03
				state = RESET;
			}
			break;
		case DEC:
		case WAIT_D:
			if(tmpA == 0x00) {
				state = INIT;
			}
			else if(tmpA == 0x01) {
				state = INC;
			}
			else if(tmpA == 0x02) {
				state = WAIT_D;
			}
			else { //input is 0x03
				state = RESET;
			}
			break;
		case RESET:
			if(tmpA == 0x00) {
				state = INIT;
			}
			else if(tmpA == 0x01) {
				state = INC;
			}
			else if(tmpA == 0x02) {
				state = RESET; //no point trying to decrement 0
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
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	state = Start;

	while(1) {
		Tick();
	}
	
	return 0;
}

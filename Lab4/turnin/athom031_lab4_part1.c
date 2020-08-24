/*	Author: alex
 *  Partner(s) Name: 
 *	Lab Section: 021
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: 
 *      	alternate LED light bulb with switch
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


/*
 PB0 and PB1 each connect to an LED
 ON STATE -> when PB0 is on and PB1 is off => 0x01
 OFF STATE -> when PB1 is on and PB0 is off => 0x02
 
 INIT state -> PBO is on
 
 press button => 0x01 input
 
 turns off current LED and turns on other LED
 state keeps state when button is released
*/

  
enum States {Start, INIT, BUTTN_REL1, OFF, BUTTN_REL2, ON} state;

/*
Start => goes to the state machine is initialized at
INIT => basically a copy of BUTTN_REL1 
BUTTN_REL1 => the button has been pressed to keep machine at ON state do nothing while button is not being pressed
OFF => button is being pressed (LED PB0 OFF, LED PB1 ON)
BUTTN_REL2 => the button has been pressed to keep machine at OFF state do nothing while button is not being pressed
ON => button is being pressed (LED PB0 ON, LED PB1 OFF) OFF
*/


void Tick() {
	switch(state) {
		case Start:
			PORTB = 0x01;
			state = INIT;
			break;
		case INIT:
			if(PINA && 0x01) {
				state = OFF; // switches to OFF state from INIT state -> means button has been pressed
			}
			else {
				state = BUTTN_REL1; // button is released can go to button release state
			}
			break;
		case BUTTN_REL1:
			if(PINA && 0x01) {
				state = OFF;
			}
			else {
				state = BUTTN_REL1;
			}
			break;
		case OFF:
			if(PINA && 0x01) {
				state = OFF;
			} //OFF => button is being pressed (LED PB0 OFF, LED PB1 ON)
			else {
				state = BUTTN_REL2;
			}
			break;
		case BUTTN_REL2:
			if(PINA && 0x01) {
				state = ON;
			} 
			else {
				state = BUTTN_REL2;
			}
			break;
		case ON:
			if(PINA && 0x01) {
				state = ON;
			}
			else {
				state = BUTTN_REL1;
			}
			break;
		default:
			break;
	} // transitions go here	

	switch(state) {
		case Start:
			break;
		case INIT:
			PORTB = 0x01;
			break;
		case BUTTN_REL1:
			break;
		case OFF:
			PORTB  = 0x02;
			break;
		case BUTTN_REL2:
			break;
		case ON:
			PORTB = 0x01;
			break;
		default:
			break;
	} // state actions go here
}
 
int main(void) {
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;     
	
	state = Start;
	while(1) {
		Tick();
	
	}	
	return 0;
}

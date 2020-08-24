/*	Author: Alex Thomas
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #3
 *	Exercise Description: CHALLENGE
 *		Festive Holiday Light Design (10 year old sister helped)
 *
 *	LAB DEMO: https://drive.google.com/open?id=1nuDbGQikX3Ge7uGKZNAMuTGtfHtcfycR
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

/*
 * On input (A0 button press) change light output
 * outputted light design is on PORTB
 */

unsigned char lightState[0x07] = {0x00, 0x15, 0x2A, 0x03, 0x30, 0x0C, 0x3F};

enum States {Start, Buttn_Rel, Buttn_Prs} state;

unsigned char tmpB = 0x00; //tmp variable to hold output
unsigned char tmpA = 0x00; //tmp variable to hold input

unsigned char iterator = 0x00;
void Tick() {
	tmpA = (~PINA & 0x01); //buttons are in pinout mode 

	switch(state) {
		case Start:
			iterator = 0x00;

			tmpB = lightState[iterator];
			PORTB = tmpB;
			state = Buttn_Rel;
			break;
		case Buttn_Rel:
			if(tmpA) {
				state = Buttn_Prs;
			}
			else {
				state = Buttn_Rel;
			}
			break;
		case Buttn_Prs:
			if(tmpA) {
				state = Buttn_Prs;
			}
			else {
				if(iterator < 0x06) {
					iterator += 0x01;
				}
				else {
					iterator = 0x00;
				}
				state = Buttn_Rel;
			}
			break;
		default:
		       	break;
	} //state transitions

	switch(state) {
		case Start:
			break;
		case Buttn_Rel:
		case Buttn_Prs:
			tmpB = lightState[iterator];
                        PORTB = tmpB;
			break;
		default:
			break;
	} // state actions go here 

}
			

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	state = Start;

	while(1) {
		Tick();
	}
	
	return 0;
}

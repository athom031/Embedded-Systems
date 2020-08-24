/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #9  Exercise #2
 *
 *	SPEAKER INTRO -> MUSIC PLAYER
 *	Exercise Description: play the c scale
 *
 *  DEMO LINK: https://drive.google.com/drive/folders/110l7cgeTNagTqprzTv6vbPrcgaiaut5v?usp=sharing
 * 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


/*GIVEN FUNCTIONS IN PRELAB*/
void set_PWM(double frequency) {	
	// Keeps track of the currently set frequency
	// Will only update the registers when the frequency
	// changes, plays music uninterrupted.
	static double current_frequency;
	if (frequency != current_frequency) {

		if (!frequency) TCCR3B &= 0x08; //stops timer/counter
		else TCCR3B |= 0x03; // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) OCR3A = 0xFFFF;
		
		// prevents OCR3A from underflowing, using prescaler 64					
		// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) OCR3A = 0x0000;
		
		// set OCR3A based on desired frequency
		else OCR3A = (short)(8000000 / (128 * frequency)) - 1;

		TCNT3 = 0; // resets counter
		current_frequency = frequency;
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
	// COM3A0: Toggle PB6 on compare match between counter and OCR3A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	// WGM32: When counter (TCNT3) matches OCR3A, reset counter
	// CS31 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

enum States{Start, INIT, ON, OFF} state;

unsigned char tmpA = 0x00;


void Tick() {

	tmpA = (~PINA & 0x07);

	switch(state) { //state transitions
		case Start:
			set_PWM(0);
			state = INIT;
			break;
		case INIT:
			if(tmpA) {
				state = ON;
			}
			else {
				state = INIT;
			}
			break;
		case ON:
			if(tmpA == 0x00) {
				state = OFF;
			}
			else if(tmpA == 0x03 || tmpA == 0x05 || tmpA == 0x06 || tmpA == 0x07) {
				state = OFF;
			} // case where multiple buttons are being pressed
			else {
				state = ON;
			}
			break;
		case OFF:
			state = INIT;
			break;
		default:
			break;
	} //state transitions
	
	switch(state) { //state actions
		case Start:
			break;
		case INIT:
			set_PWM(0);
			break;
		case ON:
			if(tmpA == 0x01) {
				set_PWM(261.33);
			} 
			else if(tmpA == 0x02) {
				set_PWM(293.66);
			}
			else if(tmpA == 0x04) {
				set_PWM(329.64);
			}
			break;
		case OFF:
			set_PWM(0);
			break;
		default:
			break;
	} //state actions
}



int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	state = Start;

	PWM_on();
	
    /* Insert your solution below */
    while (1) {
    	Tick();
    }
    return 1;
}

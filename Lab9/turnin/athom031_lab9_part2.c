/*	Author: Alex Thomas
 *  Partner(s) Name: 
 *	Lab Section: 021
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

//ATTEMPTING CONCURRENT MACHINES


//FIRST ONE TOGGLES WHETHER OR NOT AUDIO SHOULD BE ON
enum Sound_States{Sound_Start, WAIT, PUSH} sound_state;

unsigned char tmpVolButtn = 0x00; //tmp variable to hold input of buttons
unsigned char volToggle = 0x00; // global variable to hold state

void SoundChange() {
	tmpVolButtn = (~PINA & 0x01); // button hardware is in pinout mode 
	
	switch(sound_state) { //state transitions
		case Sound_Start:
			volToggle = 0x00;
			sound_state = WAIT; 
			break;
		case WAIT:
			if(tmpVolButtn) {
				sound_state = PUSH;
				if(volToggle) {
				       volToggle = 0x00;
				}
		 		else {
					volToggle = 0x01;
				}
			}
			else {
				sound_state = WAIT;
			}
			break;
		case PUSH:
			if(tmpVolButtn) {
				sound_state = PUSH;
			}
			else {
				sound_state = WAIT;
			}
			break;
		default:
			break;
	} // state transitions

	switch(sound_state) { //action transitions
		case Sound_Start:
		case WAIT:
		case PUSH:
		default:
			break;
	} //action transitions
}



//THIS STATE MACHINE PLAYS SOUND WHEN DESIRED -> PROVIDES BUTTON INPUT THAT SCALES UP OR DOWN SCALE
unsigned char scale_iter = 0x00;

unsigned char ButtonInc = 0x00;
enum Scale_States{Scale_Start, INIT, INC, DEC} scale_state;

void ScaleChange() {
	ButtonInc = (~PINA & 0x06);

	switch(scale_state) { //state transitions
		case Scale_Start:
			scale_iter = 0x00;
			scale_state = INIT;
			break;
		case INIT:
		       if(ButtonInc == 0x02) {
			       scale_state = INC;
			       if(scale_iter < 0x07) {
				       scale_iter++;
			       }
		       }
		       else if(ButtonInc == 0x04) {
			       scale_state = DEC;
			       if(scale_iter != 0x00) {
				       scale_iter--;
			       }
		       }
		       else {
			       scale_state = INIT;
		       }
		       break;
		case INC:
		       if(ButtonInc == 0x02) {
			       scale_state = INC;
		       }
		       else {
			       scale_state = INIT;
		       }
		       break;
		case DEC:
		       if(ButtonInc == 0x04) {
			       scale_state = DEC;
		       }
		       else  {
			       scale_state = INIT;
		       }
		       break;
		default:
		       break;
	} //state transitions

	switch(scale_state) { //action transitions
		case Scale_Start:
		case INIT:
		case INC:
		case DEC:
		default:
			break;
	}
}

double c_Scale[0x08] = {261.33, 293.66, 329.64, 349.23, 392.00, 440.00, 493.88, 523.25};
enum Play_States{Play_Start, Play} play_state;
void PlayChange() {
	switch(play_state) { //state transitions
		case Play_Start:
			play_state = Play;
		case Play:
			play_state = Play;
		default:
			break;
	} //state transitions

	switch(play_state) { //state actions
		case Play_Start:
			break;
		case Play:
			if(volToggle) {
				set_PWM(c_Scale[scale_iter]);
			}
			else {
				set_PWM(0);
			}
			break;
		default:
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	scale_state = Scale_Start;
	sound_state = Sound_Start;
	play_state  = Play_Start;
	PWM_on();
	
    /* Insert your solution below */
    while (1) {
	SoundChange();
	ScaleChange();
	PlayChange();
    }
    return 1;
}

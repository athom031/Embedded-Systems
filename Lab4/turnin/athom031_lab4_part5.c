/*	Author: alex
 *  Partner(s) Name: 
 *	Lab Section: 021
 *	Assignment: Lab #4  Exercise #5
 *	Exercise Description: 
 *		CHALLENGE: Door Opener KeyPad
 * 		update lock to also happen by entering code again
 * 		update sequence to longer string
 * 			now we can implement an array loop
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

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

 Extend the above door so that it can also be locked by entering the earlier code 
 Extend the above door to require the 4-button sequence #-X-Y-X rather than the 
 earlier 2-button sequence. To avoid excessive states, store the correct button 
 sequence in an array, and use a looping SM.  
*/


/*	Author: alex
 *  Partner(s) Name: 
 *	Lab Section: 021
 *	Assignment: Lab #4  Exercise #5
 *	Exercise Description: 
 *		CHALLENGE: Door Opener KeyPad
 * 		update lock to also happen by entering code again
 * 		update sequence to longer string
 * 			now we can implement an array loop
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
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

 Extend the above door so that it can also be locked by entering the earlier code 
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

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
  
enum States {Start, RESET, SeqStart, SeqInc, SeqLoop, UNLCK_DR} state;

unsigned char tmpA = 0x00; // tmp variable to hold input
unsigned char tmpB = 0x00; // tmp variable to hold output

unsigned char instSeq[0x03] = {0x01, 0x02, 0x01};

unsigned char iterator = 0x00;  

void Tick() {
	tmpA = PINA;

	switch(state) {
		case Start:
			tmpB = 0x00;
			PORTB = tmpB;
			state = RESET;
			break;
		case RESET:
			iterator = 0x00;	
			if((tmpA & 0x07) == 0x04) { //if hash key detected go to start of sequence
				state = SeqStart;
			}
			else {
				state = RESET; //else stay in RESET state
			}
			break;
		case SeqStart:
			iterator = 0x00;
			if((tmpA & 0x07) == 0x04) {
				state = SeqStart;//while still # stay there
			}
			else if((tmpA & 0x07) == 0x00) { //means you have released key, go to array loop
				state = SeqLoop;
			} 
			else { 
				state = RESET; // input is now neither pressing or releasing hash key
			}
			break;
		case SeqInc:
			//  possible error in how we go to unlock door state
			//if (iterator == 0x03) { // iterator has been increased and is done with array 
			//	state = UNLCK_DR; // go change lock status of DR
			//}
			if((tmpA & 0x07) == instSeq[iterator]) {
				if(iterator == 0x02) {
					state = UNLCK_DR; //iterator is at last element of array and matches input
				}
				else {
					state = SeqInc;//if input is still value of array, stay right there
				}
			}
			else if((tmpA & 0x07) == 0x00) {
				iterator += 1; //we have now released array element key
				state = SeqLoop; //increase iterator and stay in SeqLoop till input is no longer 0x00
				//when input is done releasing a key and picks next key come back here
			}
			else if((tmpA & 0x07) == 0x04) {
				state = SeqStart; //input is not desired key but is # start of sequence, go there
			}
			else {
				state = RESET; //input is not desired key or start of sequence RESET
			}
			break;
		case SeqLoop:
			if((tmpA & 0x07) == 0x00) {
				state = SeqLoop; // key has been released waiting for next key
			}
			else {
				state = SeqInc; // new input detected check in SeqInc
 			}
			break;
		case UNLCK_DR:
			if((tmpA & 0x07) == 0x04) {
				state = SeqStart;
			}
			else {
				state = RESET;
			}
			break;
		default:
			break;
	} //state transitions
	
	switch(state) {
	//Start, RESET, SeqStart, SeqInc, SeqLoop, UNLCK_DR
		case Start:
			break;
		case RESET:
		case SeqStart:
		case SeqInc:
		case SeqLoop:
			if((tmpA & 0x80) == 0x80) {
				tmpB = 0x00; //means inside key has been pressed
				PORTB = tmpB;
			}
			PORTC = iterator;
			break;
		case UNLCK_DR:
			tmpB = ~PORTB; //change value of tmpB
			PORTB = (0x01 & tmpB);
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

/*
enum States {Start, SeqStrt, ARR_LP, ARR_INC, CHANGE_LCK} state;

unsigned char tmpA = 0x00; // tmp variable to hold input
unsigned char tmpB = 0x00; // tmp variable to hold output

unsigned char instSeq[0x07] = {0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01};

unsigned char iterator = 0x00;  

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
				iterator += 1;
				state = ARR_LP;
			}
			else {
				iterator = 0x00;
				state = SeqStrt;
			}
			break;
		case ARR_INC:
			if(iterator < 0x07) {
				if(instSeq[iterator] == tmpA) {
					state = ARR_LP;
				}
				else {
					iterator = 0x00;
					state = SeqStrt;
				}
			}
			else { // iterator == 0x07
				iterator = 0x00;
				state = SeqStrt;
			}
			break;
		case ARR_LP:
			if(instSeq[iterator] == tmpA) {
				state = ARR_LP;
			}
			else {
				iterator += 1;
				state = ARR_INC;
			}
			break;
		case CHANGE_LCK: 
			state = SeqStrt;
			break;
	} //state transitions
	
	switch(state) {
		case Start:
			break;
		case SeqStrt:
		case ARR_LP:
		case ARR_INC:
			if((tmpA & 0x80) == 0x80) {
				tmpB = 0x00;
				PORTB = tmpB;
			}
			break;
		case CHANGE_LCK:
			tmpB = ~tmpB;
			tmpB = (0x01 & tmpB);
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

/*
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
  
enum States {Start, RESET, SeqStart, SeqInc, SeqLoop, UNLCK_DR} state;

unsigned char tmpA = 0x00; // tmp variable to hold input
unsigned char tmpB = 0x00; // tmp variable to hold output

unsigned char instSeq[0x03] = {0x01, 0x02, 0x01};

unsigned char iterator = 0x00;  

void Tick() {
	tmpA = PINA;

	switch(state) {
		case Start:
			tmpB = 0x00;
			PORTB = tmpB;
			state = RESET;
			break;
		case RESET:
			if((tmpA & 0x07) == 0x04) { //if hash key detected go to start of sequence
				state = SeqStart;
			}
			else {
				state = RESET; //else stay in RESET state
			}
			break;
		case SeqStart:
			if((tmpA & 0x07) == 0x04) {
				state = SeqStart;//while still # stay there
			}
			else if((tmpA & 0x07) == 0x00) { //means you have released key, go to array loop
				iterator = 0x00;
				state = SeqLoop;
			} 
			else { 
				state = RESET; // input is now neither pressing or releasing hash key
			}
			break;
		case SeqInc:
			
			//  possible error in how we go to unlock door state

			//if (iterator == 0x03) { // iterator has been increased and is done with array 
			//	state = UNLCK_DR; // go change lock status of DR
			//}
			
			if((tmpA & 0x07) == instSeq[iterator]) {
				if(iterator == 0x02) {
					state = UNLCK_DR; //iterator is at last element of array and matches input
				}
				else {
					state = SeqInc;//if input is still value of array, stay right there
				}
			}
			else if((tmpA & 0x07) == 0x00) {
				iterator += 1; //we have now released array element key
				state = SeqLoop; //increase iterator and stay in SeqLoop till input is no longer 0x00
				//when input is done releasing a key and picks next key come back here
			}
			else if((tmpA & 0x07) == 0x04) {
				state = SeqStart; //input is not desired key but is # start of sequence, go there
			}
			else {
				state = RESET; //input is not desired key or start of sequence RESET
			}
			break;
		case SeqLoop:
			if((tmpA & 0x07) == 0x00) {
				state = SeqLoop; // key has been released waiting for next key
			}
			else {
				state = SeqInc; // new input detected check in SeqInc
 			}
			break;
		case UNLCK_DR:
			if((tmpA & 0x07) == 0x04) {
				state = SeqStart;
			}
			else {
				state = RESET;
			}
			break;
		default:
			break;
	} //state transitions
	
	switch(state) {
	//Start, RESET, SeqStart, SeqInc, SeqLoop, UNLCK_DR
		case Start:
			break;
		case RESET:
		case SeqStart:
		case SeqInc:
		case SeqLoop:
			if((tmpA & 0x80) == 0x80) {
				tmpB = 0x00; //means inside key has been pressed
				PORTB = tmpB;
			}
			break;
		case UNLCK_DR:
			tmpB = ~tmpB; //change value of tmpB
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
*/

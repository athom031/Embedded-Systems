/*	Author: Alex Thomas
 *  Partner(s) Name: 
 *	Lab Section: 021
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: tweak introduction to synchronization and make game
 *			toggle on and off sequence of LED bulbs one every 300s try and catch light in the middle
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0; //TimerISR() will set this to 1 but we want it cleared to 0

//internal variables to mapp AVR's ISR to a cleaner TimeriSR model
unsigned long _avr_timer_M = 1; // We start the count here, down to 0, default as 1 ms
unsigned long _avr_timer_cntcurr = 0; // currrent internal count of 1ms ticks

void TimerOn() {
	// AVR timer/counter controller register TCCR 1
	TCCR1B = 0x0B; 
			//CONFUSED
			//bit3 = 0 -> CTC mode (clear the timer on compare
			//bit2 bit1 bit0 => 0 1 1: prescaler / 64
			//00001011 => 0x0B
				//8 MHz clock -> 8,000,000  / 64 = 125,000 ticks
				//TNCT1 register willl count as 125,000 ticks
	
	// AVR output compare register OCR1A
	OCR1A = 125; // timer interrupt will be generated when TNCT1 == OCR1A
       		     // desired 1 ms tick => .001 s * 125,000 tick = 125
		     // so when you desire a ___ ms tick multiply in SECONDS by 125,000
		     // when TNCT1 register = 125 -> 1 ms has passed and we compare to 125
 	
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit 1: OCIE1A -> enables compare match intterupt -> HUH

	// Initialize avr counter
	TCNT1 = 0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR is called every _avr_timer_cntCurr milliseconds
	
	//Enable global interrrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
	TCCR1B = 0x00; // bit3 bit1 bit0 = 000 : timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// C programmer does not touch ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	//CPU automatically calls TNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { //results in a more efficient compare
		TimerISR(); // call the ISR which user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}



/* ABOVE IS THE TIMING FOR THE SYNCHRONIZATION NOW WE CAN IMPLEMENT OUR STATE DESIGN */

enum States {Start, lightB0, lightB1, lightB2, lightB1_two, PRS_BUTTN, WAIT_RESET} state;

unsigned char tmpB = 0x00; //tmp variable to hold output
unsigned char tmpA = 0x00; //tmp variable to hold input
void Tick() {

	tmpA = (~PINA & 0x01); //remember buttons are pin out 
	if(tmpA != 0x01) {
		tmpA = 0x00;
	}
	switch(state) {
		case Start:
			state = lightB0;
			break;
		case lightB0:
			if(tmpA) {
				state = PRS_BUTTN;
			} else {
				state = lightB1;
			}
			break;
		case lightB1:
			if(tmpA) {
				state = PRS_BUTTN;
			} else {
				state = lightB2;
			}
			break;
		case lightB2:
			if(tmpA) {
				state = PRS_BUTTN;
			} else {
				state = lightB1_two;
			}
			break;
		case lightB1_two:
			if(tmpA) {
				state = PRS_BUTTN;
			} else {
				state = lightB0;
			}
			break;
		case PRS_BUTTN:
			if(tmpA){
				state = PRS_BUTTN;
			} else {
				state = WAIT_RESET;
				tmpA = 0x00;
			}
			break;
		case WAIT_RESET:
			if(tmpA) {
				state = lightB0;
				tmpA = 0x00;
			} else {
				state = WAIT_RESET;
			}
			break;
		default: 
			break;
	} // state transitions go here just once at state go to next state after 1 second

	switch(state) {
		case Start:
			break;
		case lightB0:
			tmpB = 0x01;
			PORTB = tmpB;
			break;
		case lightB1:
			tmpB = 0x02;
			PORTB = tmpB;
			break;
		case lightB2:
			tmpB = 0x04;
			PORTB = tmpB;
			break;
		case lightB1_two:
			tmpB = 0x02;
			PORTB = tmpB;
		case PRS_BUTTN:
			break;
		case WAIT_RESET:
			break;
		default:
			break;
	} // state actions

}


int main() {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;// set port B to output
	DDRA = 0x00; PORTA = 0xFF;// set port A to input
	state = Start;
	
	TimerSet(300); // UPDATED FOR THE GAME
	TimerOn();
	
	while(1) {
		//USER CODE
		Tick();
		while(!TimerFlag); // wait timer amount
		TimerFlag = 0;
	}
	return 1;
}

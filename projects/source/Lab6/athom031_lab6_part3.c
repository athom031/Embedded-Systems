/*	Author: Alex Thomas
 *  Assignment: Lab #6  Exercise #3
 *	Exercise Description: CHALLENGE
 *			Synchronized implementation of increment decrement button lab
 *
 *			Pressing A0 increments, Pressing A1 decrements, pressing both resets to 0
 *
 *			We now check to see if button has been pressed every 100 ms
 *
 *			so don't need to wait for button to be released
 *
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

enum States {Start, Buttn_Rel, INC, DEC, RSET} state;

unsigned char cnt = 0x00;
unsigned char tmpB = 0x00; //tmp variable to hold output
unsigned char tmpA = 0x00; //tmp variable to hold input
void Tick() {

	tmpA = (~PINA & 0x03); //remember buttons are pin out 
	
	switch(state) {
		case Start:
			tmpB = 0x07;
			PORTB = tmpB;
            cnt = 0x00;
			state = Buttn_Rel;
			break;
		case Buttn_Rel:
            if(tmpA == 0x01) {
                state = INC;
            } else if (tmpA == 0x02) {
                state = DEC;
            } else if (tmpA == 0x03) {
                state = RSET;
            } else { //input is 0x00
                state = Buttn_Rel;
            }
            cnt = 0x00;
            break;
		case INC:
            if(tmpA == 0x01) {
                cnt += 1;
                state = INC;
            } else if (tmpA == 0x02) {
                cnt = 0x00;
                state = DEC;
            } else if (tmpA == 0x03) {
                cnt = 0x00;
                state = RSET;
            } else { //input is 0x00
                cnt = 0x00;
                state = Buttn_Rel;
            }
            break;
		case DEC:
            if(tmpA == 0x01) {
                cnt = 0x00;
                state = INC;
            } else if (tmpA == 0x02) {
                cnt += 1;
                state = DEC;
            } else if (tmpA == 0x03) {
                cnt = 0x00;
                state = RSET;
            } else { //input is 0x00
                cnt = 0x00;
                state = Buttn_Rel;
            }
            break;
		case RSET:
			if(tmpA == 0x01) {
				state = INC;
			} else if (tmpA == 0x02) {
				state = DEC;
			} else if (tmpA == 0x03) {
				state = RSET;
			} else { //input is 0x00
				state = Buttn_Rel;
			}
            cnt = 0x00;
			break;
		default:
			break;
	} // state transitions

	switch(state) {
		case Start:
			break;
		case Buttn_Rel:
			break;
		case INC:
            if(cnt % 10 == 0) {
                tmpB += 0x01;
                if(tmpB > 0x09) {
                    tmpB = 0x09;
                }
            }
            PORTB = tmpB;
			break;
		case DEC:
            if(cnt % 10 == 0) {
                if(tmpB != 0x00) {
                    tmpB -= 0x01;
                }
            }
			PORTB = tmpB;
			break;
		case RSET:
			tmpB = 0x00;
			PORTB = tmpB;
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
	
	TimerSet(100); // UPDATED FOR THE GAME
	TimerOn();
	
	while(1) {
		//USER CODE
		Tick();
		while(!TimerFlag); // wait timer amount
		TimerFlag = 0;
	}
	return 1;
}

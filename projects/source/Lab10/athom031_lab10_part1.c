/*    Author: Alex Thomas
 *    Assignment: Lab #10  Exercise #1
 *
 *    Concurrent synchSMs
 *    Exercise Description:
 *    		SM 1: Turn ON and OFF 3 LEDS in Sequence
 *    		SM 2: BLINK different LED ON and OFF
 *   
 *
 *
 *    I acknowledge all content contained herein, excluding outTemplate or example
 *    code, is my own original work.
 */




#include <avr/io.h>
#include <avr/interrupt.h>


/////////////////////// TIMER SET UP FROM PREVIOUS LABS //////////////////////////
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_Three_Cntcurr = 0;
void TimerOn()
{
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_Three_Cntcurr = _avr_timer_M;
	SREG |= 0x80;
}
void TimerOff()
{
	TCCR1B = 0x00;
}
void TimerISR()
{
	TimerFlag = 1;
}
ISR(TIMER1_COMPA_vect)
{
	_avr_timer_Three_Cntcurr--;
	if (_avr_timer_Three_Cntcurr == 0)
	{
		TimerISR();
		_avr_timer_Three_Cntcurr = _avr_timer_M;
	}
}
void TimerSet(unsigned long M)
{
	_avr_timer_M = M;
	_avr_timer_Three_Cntcurr = _avr_timer_M;
}
//////////////////////////////////////////////////////////////////////////////////

/*tick function calls*/
void Three_LEDS();
void Blink_LED();
void Output();
///////////////////////


/*state enumerator*/
enum Three_States {Three_Start, LED1, LED2, LED3} Three_state;
enum Blinking_States{Blink_Start, ON, OFF} Blink_state;
enum OUT_States{OUT_Start, OUTPUT} Out_State;
////////////////////


/*global variable intialized*/
unsigned char Blink = 0x00;
unsigned char Three = 0x00;
unsigned char outTemp = 0x00;

unsigned short Blink_Cnt = 0x00;
unsigned short Three_Cnt = 0x00;
//////////////////////////////

int main(void) {
	//output
	DDRB = 0xFF; PORTB = 0x00;
	
	//Start States
	Three_state = Three_Start;
	Blink_state = Blink_Start;
	Out_State = OUT_Start;
	
	//counters
	Three_Cnt = 0;
	Blink_Cnt = 0;

	TimerSet(1);
	TimerOn();
    
	while(1) {
		Three_LEDS();
		Blink_LED();
		Output();
		while (!TimerFlag);
		TimerFlag = 0;
	}
}

//TICK FUNCTION CALLS
void Three_LEDS() {
	switch(Three_state) { // State Transitions
		case Three_Start: 
			Three_state = LED1;
			break;
		case LED1: 
			if(Three_Cnt < 1000) {
				Three_state = LED1;
				++Three_Cnt;
			}
			else {
				Three_state = LED2;
				Three_Cnt = 0;
			}
			break;
		case LED2: 
			if(Three_Cnt < 1000) {
				Three_state = LED2;
				++Three_Cnt;
			}
			else {
				Three_state = LED3;
				Three_Cnt = 0;
			}
			break;
		case LED3:
			if(Three_Cnt < 1000) {
				Three_state = LED3;
				++Three_Cnt;
			}
			else {
				Three_state = LED1;
				Three_Cnt = 0;
			}
			break;
		default:
			break;
	}

	switch(Three_state) { // State Actions
		case Three_Start:
			break;
		case LED1:
			Three = 0x01;
			break;
		case LED2:
			Three = 0x02;
			break;
		case LED3:
			Three = 0x04;
			break;
		default:
			break;
	}
}

void Blink_LED() {
	switch(Blink_state) { // State Transitions
		case Blink_Start:
			Blink_state = ON;
			break;
		case ON:
			if(Blink_Cnt < 1000) {
				Blink_state = ON;
				++Blink_Cnt;
			}
			else {
				Blink_state = OFF;
				Blink_Cnt = 0;
			}
			break;
		case OFF: 
			if(Blink_Cnt < 1000) {
				Blink_state = OFF;
				++Blink_Cnt;
			}
			else {
				Blink_state = ON;
				Blink_Cnt = 0;
			}
			break;
		default:
			break;
	}

	switch(Blink_state) { // State Actions
		case Blink_Start:
			break;
		case ON:
			Blink = 0x08;
			break;
		case OFF:
			Blink = 0x00;
		default:
			break;
	}
}

void Output() {
	switch(Out_State) { // State Transitions
		case OUT_Start:
			Out_State = OUTPUT;
			break;
		case OUTPUT:
			break;
		default:
			break;
	}

	switch(Out_State) { // State Actions
		case OUT_Start:
			break;
		case OUTPUT:
			outTemp = Blink | Three;
			PORTB = outTemp;
			break;
	}
}

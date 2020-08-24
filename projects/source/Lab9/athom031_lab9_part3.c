/*    Author: Alex Thomas
 *    Assignment: Lab #9  Exercise #3
 *
 *    SPEAKER INTRO -> MUSIC PLAYER
 *    CHALLENGE Exercise Description: Play a song using the C Scale
 *
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


/* ************GIVEN FUNCTIONS FOR SPEAKER PWM IN PRELAB************ */
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
        
        // prevents OCR3A from underflowing, using prescaler 64                    // 31250 is largest frequency that will not result in underflow
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

// ***********************************************************************//

/* ************TIMER SETUP USED IN PREVIOUS LABS************ */
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
void TimerOn()
{
    TCCR1B = 0x0B;
    OCR1A = 125;
    TIMSK1 = 0x02;
    TCNT1 = 0;
    _avr_timer_cntcurr = _avr_timer_M;
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
    _avr_timer_cntcurr--;
    if (_avr_timer_cntcurr == 0)
    {
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}
void TimerSet(unsigned long M)
{
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}
// ***********************************************************************//

//ATTEMPTING CONCURRENT MACHINES
enum Play_States{Play_Start, INIT, BUTTN_PUSH, BUTTN_REL} play_state;

unsigned char playToggle = 0x00;
unsigned char tmpA = 0x00;

//WAIT FOR BUTTON PRESS TO INITIATE SONG PLAY
void Play() {
    tmpA = (~PINA & 0x01);
    
    switch(play_state){ //state transitions
        case Play_Start:
            playToggle = 0x00;
            play_state = INIT;
            break;
        case INIT:
            if(tmpA) {
                play_state = BUTTN_PUSH;
            }
            else {
                play_state = INIT;
            }
            break;
        case BUTTN_PUSH:
            play_state = BUTTN_REL;
            break;
        case BUTTN_REL:
            if(tmpA) {
                play_state = BUTTN_REL;
            }
            else {
                play_state = INIT;
            }
            break;
        default:
            break;
    } //state transitions
    
    switch(play_state) { //state actions
        case Play_Start:
            break;
        case INIT:
            break;
        case BUTTN_PUSH:
            playToggle = 0x01;
            break;
        case BUTTN_REL:
            break;
    } //state actions
}

//WHEN TOGGLE ON PLAY ENTIRE SONG

/*      E5 - 659.25
        D5 - 587.33
        C5 - 523.55
        B4 - 493.88
        A4 - 440.00
        G4 - 392.00
        F4 - 349.23
*/

//playToggle


/*C5 B4 C5 B4 C5 B4 C5 E5 D5 C5 B4 A4 B4 A4 B4 0 -> 2x*/
unsigned char sz = 45;
double verseNoteArr[45] = {523.55, 0, 493.88, 523.55, 0, 493.88, 523.55, 0, 493.88, 523.55, 659.25, 587.33, 523.55, 493.88, 0, 440.00, 493.88, 0, 440.00, 493.88, 0, 392.00, 440.00, 523.55, 440.00, 0, 349.23, 392.00, 440.00, 392.00, 0, 392.00, 440.00, 523.55, 587.33, 523.55, 440.00, 392.00, 349.23, 0, 349.23, 392.00, 440.00, 392.00 };
unsigned char timer = 0x00;

unsigned char verseTimeArr[45] = {3, 1, 1, 3, 1, 1, 3, 1, 1, 2, 1, 1, 1, 3, 1, 1, 3, 1, 1, 4, 4, 3, 2, 1, 5, 5, 3, 2, 1, 5, 5, 2, 2, 1, 3, 1, 2, 1, 4, 4, 2, 2, 1, 6, 6};
//TEST
enum States{Start, ON, OFF} state;
unsigned char iter = 0x00;


void Tick() {
	switch(state) { //state transitions

		case Start:
			set_PWM(0);
			iter	= 0x00;
			if(playToggle) {
				state = ON;
			}
			else {
				state = Start;
			}
			break;
		case ON:
			if(iter < sz) {
				state = ON;
			}
			else {
				state = OFF;
			}
			break;
		case OFF:
			if(tmpA) {
				state = OFF;
			}
			else {
				playToggle = 0x00;
				state = Start;
			}
			break;
		default:
			break;	
	}

	switch(state) {
		case Start:
			break;
		case ON:
			set_PWM(verseNoteArr[iter]);
            if(timer < verseTimeArr[iter]) {
                timer += 1;
            }
            else {
                timer = 0x00;
                iter += 1;
            }
            break;
		case OFF:
			set_PWM(0);
            break;
		default:
			break;
	}
}


//unsigned char verseTimeArr[0x10] = {2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 2};

unsigned char verseIter = 0x00;

unsigned char chorusIter = 0x00;



//unsigned char timer = 0x00;

enum Song_States{Song_Start, S_INIT, VERSE1, VERSE2, CHORUS, END} song_state;

void Song() {
    switch(song_state) { //state transitions
        case Song_Start:
            verseIter = 0x00;
            chorusIter = 0x00;
	    //timer = 0x00;
            song_state = S_INIT;
            set_PWM(0);
            break;
        case S_INIT:
            if(playToggle) {
                song_state = VERSE1;
            }
            else {
                song_state = S_INIT;
            }
            break;
        case VERSE1:
            if(verseIter > 0x0F) {
                verseIter = 0x00;
                song_state = VERSE2;
            }
            else {
                song_state = VERSE1;
            }
            break;
        case VERSE2:
            if(verseIter > 0x0F) {
                verseIter = 0x00;
                chorusIter = 0x00;
                song_state = CHORUS;
            }
            else {
                song_state = VERSE2;
            }
            break;
        case CHORUS:
            song_state = END;
        case END:
            playToggle = 0x00;
            verseIter = 0x00;
            chorusIter = 0x00;
            song_state = S_INIT;
            break;
    } //state transitions
    
    switch(song_state) { //state actions
        case Song_Start:
            break;
        case S_INIT:
            set_PWM(0);
            break;
        case VERSE1:
            if(verseIter < 0x10) {
                set_PWM(verseNoteArr[verseIter]);
                /*
		if(timer < verseTimeArr[verseIter]) {
                    timer += 1;
                }
                else {
                    timer = 0x00;
                    verseIter += 1;
                }
		*/
		verseIter+=1;
            }
        case VERSE2:
            if(verseIter < 0x10) {
                set_PWM(verseNoteArr[verseIter]);
		/*
                if(timer < verseTimeArr[verseIter]) {
                    timer += 1;
                }
                else {
                    timer = 0;
                    verseIter++;
                }*/
		verseIter+=1;
            }
        case CHORUS:
            set_PWM(0);
        case END:
            set_PWM(0);
    } //state actions
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    
    /* PWM initialization */
    PWM_on();
    
    /* state machine start initializations*/
    play_state = Play_Start;
    song_state = Song_Start;
    state = Start;
    /* Timer Initialization */
    TimerSet(109); //approximation of 69 beats per miute
                   //but we have half beat notes so half that period
    TimerOn();
    
    while (1) {
        /*tick functions*/
 	Play();
        //Song();
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

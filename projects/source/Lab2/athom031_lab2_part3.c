/*	Author: Alex Thomas
 *  Assignment: Lab #2  Exercise #3
 *      Description:
 *  	    extend bit to assert bit if parking lot is full
 *      	(still give count of spaces available)
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
  	/* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; // config port A's 8 pins as input
	DDRC = 0xFF; PORTC = 0x00; // config port C's 8 pins as outputs
	unsigned char cntAvail = 0x00; // temp variable that holds avail park
	unsigned char tmpA = 0x00; // temp variable to hold values of A
	
	while (1) {
		//1) read input only the little nibble (A pins 0 to 3)
		tmpA = PINA & 0x0F;
		cntAvail = 0x00;
		
		//mask each single parking Space
		if((tmpA & 0x08) == 0x00) {
			cntAvail = cntAvail + 1;
		}
		if((tmpA & 0x04) == 0x00) {
			cntAvail = cntAvail + 1;
		}
		if((tmpA & 0x02) == 0x00) {
			cntAvail = cntAvail + 1;
		}
		if((tmpA & 0x01) == 0x00) {
			cntAvail = cntAvail + 1;
		}

		//part 3
		if(cntAvail == 0x00) {
			cntAvail = 0x80;
		}

		PORTC = cntAvail;
	}
	return 0;
}

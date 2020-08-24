/*	Author: alex
 *  Partner(s) Name: 
 *	Lab Section: 021
 *	Assignment: Lab #3  Exercise #5
 *	Exercise Description: 
 *      	CHALLENGE: Airbag Weight Sensor
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
	DDRD = 0x00; PORTD = 0xFF;
	DDRB = 0xFE; PORTB = 0x01;     
   	
	unsigned short weightSensor = 0x0000; //char's range is less than 9 bits
	unsigned char weightB = 0x00; //one bit input from B rest treated as output
    	unsigned char tmpB = 0x00; //temporary variable that holds output (B7...B1)
	
	while(1) {

        	weightSensor = 0x00FF & PIND;
		weightSensor = weightSensor << 1;
        	
		weightB =  PINB & 0x01;
		
		weightSensor = weightSensor | weightB;

		if(weightSensor >= 0x0046) { //put in terms of "short" values (equal to 70)
			// turn airbag on
			//set B1 to 1
			tmpB = 0x02;
		}
		else if(weightSensor > 0x0005 && weightSensor < 0x0046) {
			// airbag should be disabled 
			// set PB2 to 1
			tmpB = 0x04;
		}
		else { // weightSensor detects a weight of less than 5
			// no airbag light at all
			// both PB1 and PB2 should be 0 	
        		// tmpB = 0x00;
		}
        	
		PORTB = tmpB;
        	weightSensor =  0x0000;
		weightB = 0x00;
		tmpB = 0x00;
	}
	return 0;
}

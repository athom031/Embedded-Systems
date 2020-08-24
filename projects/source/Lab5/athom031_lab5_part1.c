/*	Author: Alex Thomas
 *  Assignment: Lab #5  Exercise #1
 *	Exercise Description: Redo of Lab 3 Exercise 2
 *		more so the implementation onto our circuit boards
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

	unsigned char inFuelLvl = 0x00; // we get input from port A this is our fuel level
	unsigned char outLDSensor = 0x00; //temp var to hold output sensor val
	unsigned char lowFuelChk = 0x01;

    /* Insert your solution below */
    while (1) {
	    inFuelLvl = (~PINA & 0x0F); //desire bits A0 ... A3
	    //hardware switch -> pin out method which means we need opposite

	    //check max gauge of fuel
	    if(inFuelLvl > 0) {
		    outLDSensor = (outLDSensor | 0x20);
	    }
	    if(inFuelLvl > 2) {
		    outLDSensor = (outLDSensor | 0x10);
	    }
	    if(inFuelLvl > 4) {
		    lowFuelChk = 0x00;
		    outLDSensor = (outLDSensor | 0x08);
            }
	    if(inFuelLvl > 6) {
		    outLDSensor = (outLDSensor | 0x04);
	    }
	    if(inFuelLvl > 9) {
		    outLDSensor = (outLDSensor | 0x02);
	    } 
	    if(inFuelLvl > 12) {
		    outLDSensor = (outLDSensor | 0x01);
	    }

	    //for the low fuel light
	    if(lowFuelChk) {
		    outLDSensor = (outLDSensor | 0x40);
	    }
	    else {
		    outLDSensor = (outLDSensor & 0xBF);
	    }


	    PORTC = outLDSensor;
	    outLDSensor = 0x00;
	    inFuelLvl = 0x00;
	    lowFuelChk = 0x01;




    }
    return 1;
}

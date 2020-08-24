/*	Author: alex
 *  Partner(s) Name: 
 *	Lab Section: 021
 *	Assignment: Lab #3  Exercise #3
 *	Exercise Description: 
 *      	update fuel-level sensor LED simulator
 * 		if seatbelt not fastened when driver seated and key in ignition, flash warning
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char inFuelLvl = 0x00; // we get input from port A this is our fuel level
	unsigned char outLdSensor = 0x00; //temporary variable to hold the output sensor value
	unsigned char lowFuelChk = 0x01;
	unsigned char seatBeltWarn = 0x00; //new temp variable for updated feature
	while(1) {
		inFuelLvl = (PINA & 0x0F);  //desire only the bits A0 to A3
		seatBeltWarn = (PINA & 0xF0);

		
        	//check maximum gauge of fuel
		if(inFuelLvl > 0) {
            		outLdSensor = (outLdSensor | 0x20);
       		}
        	if(inFuelLvl > 2) {
        	    outLdSensor = (outLdSensor | 0x10);
        	}
        	if(inFuelLvl > 4) {
        	    lowFuelChk = 0x00;
        	    outLdSensor = (outLdSensor | 0x08);
        	}
        	if(inFuelLvl > 6) {
        	    outLdSensor = (outLdSensor | 0x04);
        	}
        	if(inFuelLvl > 9) {
        	    outLdSensor = (outLdSensor | 0x02);
        	}
        	if(inFuelLvl > 12) {
            		outLdSensor = (outLdSensor | 0x01);
        	}
        
       	 	//for the low fuel light
        	if(lowFuelChk) {
         		outLdSensor = (outLdSensor | 0x40);
        	}
        	else {
            		outLdSensor = (outLdSensor & 0xBF);
        	}
		
        	if(seatBeltWarn == 0x30) {
			outLdSensor = (outLdSensor | 0x80);
		}
		else { 
			outLdSensor = (outLdSensor & 0x7F);
		}
       		
		PORTC = outLdSensor;
		outLdSensor = 0x00;
		inFuelLvl = 0x00;	
        	lowFuelChk = 0x01;
		seatBeltWarn = 0x00;
	}
    return 0;
}

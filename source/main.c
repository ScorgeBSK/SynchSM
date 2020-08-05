/*	Author: Trung Lam
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00;
    TimerSet(500);
    TimerOn();

    unsigned char tmpB = 0x00;

    /* Insert your solution below */
    while (1) {
    	tmpB = ~tmpB;
	PORTB = tmpB;
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

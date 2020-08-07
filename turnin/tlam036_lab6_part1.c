/*	Author: Trung Lam
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #1
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

enum States {start, seqB0, seqB1, seqB2} state;


void Tick(){
	unsigned char tmpB = 0;

	switch(state){
		case start:
			state = seqB0;
			break;
		case seqB0:
			state = seqB1;
			break;
		case seqB1:
			state = seqB2;
			break;
		case seqB2:
			state = seqB0;
			break;
		default:
			state = start;
			break;
	}

	switch(state){
		case seqB0:
			tmpB = 0x01;
			break;
		case seqB1:
			tmpB = 0x02;
			break;
		case seqB2:
			tmpB = 0x04;
			break;
		default:
			break;

	}

	PORTB = tmpB;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00;
    state = start;
    TimerSet(1000);
    TimerOn();


    /* Insert your solution below */
    while (1) {
	Tick();
	while(!TimerFlag) {};
	TimerFlag = 0;
    }
    return 1;
}

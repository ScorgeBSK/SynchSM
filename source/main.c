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

enum States {start, seqB0, seqB1, seqB2, seqB1Repeat, B0PausePress, B0PauseRelease, B1PausePress, B1PauseRelease, B2PausePress, B2PauseRelease, B1RepeatPausePress, B1RepeatPauseRelease} state;


void Tick(){
	
	unsigned char tmpB = 0;
	unsigned char button = PINA & 0x01;

	switch(state){
		case start:
			state = seqB0;
			break;
		case seqB0:
			state = button ? B0PausePress : seqB1;
			break;
		case seqB1:
			state = button ? B1PausePress : seqB2;
			break;
		case seqB2:
			state = button ? B2PausePress : seqB1Repeat;
			break;
		case seqB1Repeat:
			state = button ? B1RepeatPausePress : seqB0;
			break;
		case B0PausePress:
			state = button ? B0PausePress : B0PauseRelease;
			break;
		case B0PauseRelease:
			state = button ? seqB1 : B0PauseRelease;
			break;
		case B1PausePress:
			state = button ? B1PausePress : B1PauseRelease;
			break;
		case B1PauseRelease:
			state = button ? seqB2 : B1PauseRelease;
			break;
		case B2PausePress:
			state = button ? B2PausePress : B2PauseRelease;
			break;
		case B2PauseRelease:
			state = button ? seqB1Repeat : B2PauseRelease;
			break;
		case B1RepeatPausePress:
			state = button ? B1RepeatPausePress : B1RepeatPauseRelease;
			break;
		case B1RepeatPauseRelease:
			state = button ? seqB0 : B1RepeatPauseRelease;
			break;
		default:
			state = start;
			break;
	}

	switch(state){
		case seqB0:
			tmpB = 1;
			break;
		case seqB1:
			tmpB = 2;
			break;
		case seqB2:
			tmpB = 4;
			break;
		case seqB1Repeat:
			tmpB = 2;
			break;
                case B0PausePress:
			tmpB = 1;
                        break;
                case B0PauseRelease:
			tmpB = 1;
                        break;
                case B1PausePress:
			tmpB = 2;
                        break;
                case B1PauseRelease:
			tmpB = 2;
                        break;
                case B2PausePress:
			tmpB = 4;
                        break;
                case B2PauseRelease:
			tmpB = 4;
                        break;
                case B1RepeatPausePress:
			tmpB = 2;
                        break;
                case B1RepeatPauseRelease:
			tmpB = 2;
                        break;
		default:
			break;

	}

	PORTB = tmpB;

}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00;
    DDRA = 0x00; PORTA = 0xFF;
    TimerSet(300);
    TimerOn();


    /* Insert your solution below */
    while (1) {
	Tick();
	while(!TimerFlag) {};
	TimerFlag = 0;
    }
    return 1;
}

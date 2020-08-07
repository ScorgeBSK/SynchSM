/*	Author: Trung Lam
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #2
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

enum States {start, seqB0, seqB1, seqB2, seqB1Repeat, 
	B0PausePress, B0PauseRelease, B0ResetPress,
	B1PausePress, B1PauseRelease, B1ResetPress,
	B2PausePress, B2PauseRelease, B2ResetPress,
	B1RepeatPausePress, B1RepeatPauseRelease, B1RepeatResetPress} state;


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
			state = button ? B0ResetPress : B0PauseRelease;
			break;
		case B0ResetPress:
			state = button ? B0ResetPress : seqB1;
			break;

		case B1PausePress:
			state = button ? B1PausePress : B1PauseRelease;
			break;
		case B1PauseRelease:
			state = button ? B1ResetPress : B1PauseRelease;
			break;
		case B1ResetPress:
			state = button ? B1ResetPress : seqB2;
			break;

		case B2PausePress:
			state = button ? B2PausePress : B2PauseRelease;
			break;
		case B2PauseRelease:
			state = button ? B2ResetPress : B2PauseRelease;
			break;
		case B2ResetPress:
			state = button ? B2ResetPress : seqB1Repeat;
			break;

		case B1RepeatPausePress:
			state = button ? B1RepeatPausePress : B1RepeatPauseRelease;
			break;
		case B1RepeatPauseRelease:
			state = button ? B1RepeatResetPress : B1RepeatPauseRelease;
			break;
		case B1RepeatResetPress:
			state = button ? B1RepeatResetPress : seqB0;
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
		case B0ResetPress:
			tmpB = 1;
			break;

                case B1PausePress:
			tmpB = 2;
                        break;
                case B1PauseRelease:
			tmpB = 2;
                        break;
		case B1ResetPress:
			tmpB = 2;
			break;

                case B2PausePress:
			tmpB = 4;
                        break;
                case B2PauseRelease:
			tmpB = 4;
                        break;
		case B2ResetPress:
			tmpB = 4;
			break;

                case B1RepeatPausePress:
			tmpB = 2;
                        break;
                case B1RepeatPauseRelease:
			tmpB = 2;
                        break;
		case B1RepeatResetPress:
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

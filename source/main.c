/*	Author: Trung Lam
 *  Partner(s) Name: 
 *	Lab Section: B22
 *	Assignment: Lab #5  Exercise #3
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

enum States {start, init, increment, decrement, reset, result} state;

void tick(){
	unsigned char button = PINA & 0x03;
	signed char output = PINB;
	unsigned char counter = 0;

	switch(state){
		case start:
	       		state = init;
			break;
		case init:
			if(button == 1){
				state = increment;
			}
			else if(button == 2){
				state = decrement;
			}
			else if(button == 3){
				state = reset;
			}
			else{
				state = init;
			}
			break;
		case increment:
			state = (button == 1) ? increment : result;
			break;
		case decrement:
			state = (button == 1) ? decrement : result;
			break;
		case reset:
			state = result;
			break;
		case result:
			if(button == 1){
				state = increment;
			}
			else if(button == 2){
				state = decrement;
			}
			else if(button == 3){
				state = reset;
			}
			else{
				state = result;
			}
			break;
		default:
			state = start;
			break;	
	}

	switch(state){
                case init:
                        break;
                case increment:
			output++;
			if(output > 9){
				output = 9;
			}
                        break;
                case decrement:
			output--;
			if(output < 0){
				output = 0;
			}
			break;
		case reset:
			output = 0;
			break;
		case result:
			output = output;
			break;
		default:
			break;
        }

	PORTB = output;

}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x07;
    TimerSet(100);
    TimerOn();

    state = start;
    /* Insert your solution below */
    while (1) {
	tick();
	while(!TimerFlag) {};
	TimerFlag = 0;
    }
    return 1;
}

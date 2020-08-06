/*	Author: Trung Lam
 *  Partner(s) Name: 
 *	Lab Section: B22
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, init, increment, decrement, reset, result} state;

void tick(){
	unsigned char button = PINA & 0x03;
	signed char output = PINC;
	
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
			state = result;
			break;
		case decrement:
			state = result;
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

	PORTC = output;

}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x07;
	
    state = start;
    /* Insert your solution below */
    while (1) {
	tick();
    }
    return 1;
}

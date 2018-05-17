#include <avr/interrupt.h>
#include <avr/io.h>

#include <util/delay.h>

#include <stdio.h>
#include <stdlib.h>

#include "usart.h"

static int go, right, left, back;

void init_engines() {
	// set outputs
	DDRA |= (1 << PA0);
	DDRA |= (1 << PA1);
	DDRA |= (1 << PA2);
	DDRA |= (1 << PA3);
	DDRA |= (1 << PA4);
	DDRA |= (1 << PA5);

	// // Enable both engines
	PORTA |= (1 << PA0);
	PORTA |= (1 << PA3);
}

void control() {
	if (go == 1) {
		//go Forward
		PORTA |= (1 << PA1);
		PORTA |= (1 << PA5);

		if (right == 1) {
			// Deactivate right engine
			PORTA &= ~(1 << PA1);
		}

		if (left == 1) {
			// Deactivate left engine
			PORTA &= ~(1 << PA5);
		}
	} else if (back == 1) {
		// go backwards
		PORTA |= (1 << PA2);
		PORTA |= (1 << PA4);

		if (right == 1) {
			// Deactivate left engine
			PORTA &= ~(1 << PA4);
		}

		if (left == 1) {
			// Deactivate right engine
			PORTA &= ~(1 << PA2);
		}
	} else if (right == 1) {
		PORTA &= ~(1 << PA1);
		PORTA |= (1 << PA5);
	} else if (left == 1) {
		PORTA &= ~(1 << PA5);
		PORTA |= (1 << PA1);
	} else {
		// Deactivate engines
		PORTA &= ~(1 << PA1);
		PORTA &= ~(1 << PA2);
		PORTA &= ~(1 << PA4);
		PORTA &= ~(1 << PA5);
	}
}

int main(void) {
	// LEDs
	DDRD |= (1 << PD7);
	DDRA |= (1 << PA6);
	DDRB |= (1 << PB0);

	init_engines();

	USART0_init();

	char c;

	while (1) {
		c = USART0_receive();

		if (c == 'F') {
			PORTD |= (1 << PD7);
			PORTA &= ~(1 << PA6);
			PORTB &= ~(1 << PB0);
			go = 1;
		} else if (c == 'f') {
			PORTD &= ~(1 << PD7);
			PORTA |= (1 << PA6);
			PORTB |= (1 << PB0);
			go = 0;
		} else if (c == 'B') {
			PORTD |= (1 << PD7);
			PORTA &= ~(1 << PA6);
			PORTB &= ~(1 << PB0);
			back = 1;
		} else if (c == 'b') {
			PORTD &= ~(1 << PD7);
			PORTA |= (1 << PA6);
			PORTB |= (1 << PB0);
			back = 0;
		} else if (c == 'R') {
			PORTD |= (1 << PD7);
			PORTA &= ~(1 << PA6);
			PORTB &= ~(1 << PB0);
			right = 1;
		} else if (c == 'r') {
			PORTD &= ~(1 << PD7);
			PORTA |= (1 << PA6);
			PORTB |= (1 << PB0);
			right = 0;
		} else if (c == 'L') {
			PORTD |= (1 << PD7);
			PORTA &= ~(1 << PA6);
			PORTB &= ~(1 << PB0);
			left = 1;
		} else if (c == 'l') {
			PORTD &= ~(1 << PD7);
			PORTA |= (1 << PA6);
			PORTB |= (1 << PB0);
			left = 0;
		}

		control();
	}

}



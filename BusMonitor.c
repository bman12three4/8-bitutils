/*
 *	Created by Byron Lathi
 *	May 3 2017
 *	Purpose: To act as a monitor for the 8-bit computer that I am building.
 * 		 I should be able to trigger the MCU either by sending a serial 
 *		 command or by activating an interupt. It should then send back
 * 		 over serial the contents of the address and data busses. It
 *		 might also have a mode where it constantly does this.
 */

#include<avr/io.h>
#include<avr/interrupt.h>
#include<avr/iom162.h>

#define FOSC 8000000		 //Clock Speed
#define BAUD 9600   		 //Baud
#define myUBRR FOSC/16/BAUD-1    //Baud Rate Register value


ISR(INT0_vect){
	//do something
	//This is really just here for testing so that I can manually
	//activate it, in case the serial thing does not receive. The goal
	//is to have this all done over serial
}

void main(){
	cli();
	USART_init(myUBRR);
	sei();
	
}

void USART_init(unsigned int ubrr){

	UBRR0H = (unsigned char) (ubrr >> 8);	//set UBRRH to the first 8 bits of ubrr
	UBRR0L = (unsigned char) ubrr;		//set UBRRL to the last 8 bits of ubrr

	UCSR0B = (1 << RXEN0) | (1 << TXEN0); 	//Enable receiver and transmiter

	UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);	//set frame format: 8 data 2 stop bit.	
}

/*
 *	Created by Byron Lathi
 *	May 3 2017
 *	Purpose: To act as a monitor for the 8-bit computer that I am building.
 * 		 I should be able to trigger the MCU either by sending a serial 
 *		 command.  It should then send back over serial the contents of 
 *		 the address and data busses. It might also have a mode where it 
 *	   	 constantly does this.
 */

#define F_CPU 8000000

#include<avr/io.h>
#include<avr/interrupt.h>
#include<avr/iom162.h>
#include<util/delay.h>

//#define F_CPU 8000000		 //CPU speed
#define FOSC 8000000		 //Clock Speed
#define BAUD 9600   		 //Baud
#define myUBRR FOSC/16/BAUD-1    //Baud Rate Register value


/*	Initialize USART0
 *	ubrr is the UBRR, a function of the clock rate and baud rate, ase defined in the datasheet
 *	This code almost identical to the example code from the datashheet.
 */
void USART_init(unsigned int ubrr){

	UBRR0H = (unsigned char) (ubrr >> 8);	//set UBRRH to the first 8 bits of ubrr
	UBRR0L = (unsigned char) ubrr;		//set UBRRL to the last 8 bits of ubrr

	UCSR0B = (1 << RXEN0) | (1 << TXEN0); 	//Enable receiver and transmiter

	UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);	//set frame format: 8 data 2 stop bit.	
}

/* 	Transmit data over USART0 using 5-8 bit
 * 	data is what to be transfered.
 *	This code is similar if not identical to the example code in the datasheet.
 */
void USART_transmit(unsigned int data){

	while (!(UCSR0A & (1<<UDRE0)))		// Wait until the data is receied
	UDR0 = data;				// Put data into the buffer, which sends it.
}

/*	Receive data from USART0 using 5-8 bit
 *	returns the data received
 * 	This code is similar if not identical to the example code in the datasheet.
 */
unsigned int USART_receive( void ){
	while (!(UCSR0A & (1<<RXC0)))
		;

	return UDR0;
}

int main( void ){
	DDRB = 0x00;
	DDRC = 0x00;

	cli();
	USART_init(myUBRR);
	sei();

	while(1){
		USART_transmit(PORTB);
		USART_transmit(PORTC);
		_delay_ms(100);
	}
	
	return 0;
}

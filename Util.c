/*
 *	Created by Byron Lathi
 *	May 3 2017
 *	Purpose: To act as a monitor for the 8-bit computer that I am building.
 * 		 I should be able to trigger the MCU either by sending a serial 
 *		 command.  It should then send back over serial the contents of 
 *		 the address and data busses. It might also have a mode where it 
 *	   	 constantly does this.
 */

// This is 1/8 of the oscilator speed because the prescalar is set to 8.
#define F_CPU 1000000

#include<avr/io.h>
#include<avr/interrupt.h>
#include<avr/iom162.h>
#include<util/delay.h>

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

	while (!(UCSR0A & (1<<UDRE0)))		// Wait until transmit buffer is empty
	UDR0 = data;				// Put data into the buffer, which sends it.
}

/*	Receive data from USART0 using 5-8 bit
 *	returns the data received
 * 	This code is similar if not identical to the example code in the datasheet.
 */
unsigned int USART_receive( void ){	
	while (!(UCSR0A & (1<<RXC0)))	// Wait until data is received
		;

	return UDR0;			// Return the data
}

void USART_flush(){
	while (!(UCSR0A & (1<<RXC0)))	// Wait until data is received
		;
	unsigned int sink;
	
	sink = UDR0;			// clear the buffer
}

/*	Program the SRAM of the computer
 *	PORTC is the address, it is all 8 bits, but the computer only uses 4 right now
 *	PORTD is the data to be put in.
 */
void MemProgram(unsigned int addr, unsigned int data){
	PORTC |= (1<<PORTC7) + (1<<PORTC6);		// Send stop signal and switch memory into programming mode
	PORTC &=  ~(1<<PORTC5);		// Set enter to 0
	PORTC = addr;			// Set PORTC to addr
	PORTA = data;			// set PORTA to data
	PORTC |= (1<<PORTC5);		// set enter to 1	
	_delay_ms(10);			// delay to ensure memory is programmed
	PORTC = 0;			// set enter to 0
}

int main( void ){
	DDRB = 0x00;	// set PORTB direction to IN
	DDRC = 0xFF;	// set PORTC direction to OUT
	DDRA = 0xFF;	// set PORTD direction to OUT

	cli();		// disable interrupts for USART initialization
	USART_init(myUBRR); //initialize USART
	sei();		// re-enable interrupts

	while (1){
		if (USART_receive() == 0x50){ 	// If user sends a "P"
			USART_transmit(0x52);	// Send pack a "R"
			unsigned int addr = USART_receive();
			unsigned int data = USART_receive();
			while (addr != 0xFF){
				MemProgram(addr, data);
				addr = USART_receive();
				data = USART_receive();
			}
		}
	}	

	return 0;
}

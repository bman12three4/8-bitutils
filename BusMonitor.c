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
#include<avr/interupt.h>



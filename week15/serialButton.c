
//
//
// serialButton.c
//
// button hello-world
//    9600 baud FTDI interface
//
// Neil Gershenfeld
// 10/31/10
//
// (c) Massachusetts Institute of Technology 2010
// This work may be reproduced, modified, distributed,
// performed, and displayed for any purpose. Copyright is
// retained and must be preserved. The work is provided
// as is; no warranty is provided, and users accept all 
// liability.
//
// Modified by Hashim Nabil AL Sakkaf @Fabacedmy 2017 to do the following:
// - send 'x' if the button is pressed

#include <avr/io.h>
#include <util/delay.h>

#define output(directions,pin) (directions |= pin) // set port direction for output
#define input(directions,pin) (directions &= (~pin)) // set port direction for input
#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define pin_test(pins,pin) (pins & pin) // test for port pin
#define bit_test(byte,bit) (byte & (1 << bit)) // test for bit set
#define bit_delay_time 102 // bit delay for 9600 with overhead
#define bit_delay() _delay_us(bit_delay_time) // RS232 bit delay
#define half_bit_delay() _delay_us(bit_delay_time/2) // RS232 half bit delay

#define input_port PORTA
#define input_direction DDRA
#define input_pin (1 << PA3)
#define input_pins PINA

#define serial_port PORTA
#define serial_direction DDRA
#define serial_pin_out (1 << PA1)//TX

void put_char(volatile unsigned char *port, unsigned char pin, char txchar) {
   //
   // send character in txchar on port pin
   //    assumes line driver (inverts bits)
   //
   // start bit
   //
   clear(*port,pin);
   bit_delay();
   //
   // unrolled loop to write data bits
   //
   if bit_test(txchar,0)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,1)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,2)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,3)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,4)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,5)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,6)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,7)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   //
   // stop bit
   //
   set(*port,pin);
   bit_delay();
   //
   // char delay
   //
   bit_delay();
   }

int main(void) {
   //
   // main
   //


   // set clock divider to /1
   //
   CLKPR = (1 << CLKPCE);
   CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
   //
   // initialize pins
   //
   set(serial_port, serial_pin_out);
   output(serial_direction, serial_pin_out);

   set(input_port, input_pin); // turn on pull-up
   input(input_direction, input_pin);
   //
   // main loop
   //
   while (1) {
      //
      // wait for button down
      //
      while (0 != pin_test(input_pins,input_pin))
         ;
      put_char(&serial_port, serial_pin_out, 'x');
      //
      // wait for button up
      //
      while (0 == pin_test(input_pins,input_pin))
         ;
      put_char(&serial_port, serial_pin_out, 'y');
      }
   }
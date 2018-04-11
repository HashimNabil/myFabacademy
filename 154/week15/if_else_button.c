
//
//
// hello.bus.45.c
//
// 9600 baud serial bus hello-world
//
// Neil Gershenfeld
// 11/24/10
//
// (c) Massachusetts Institute of Technology 2010
// Permission granted for experimental and personal use;
// license for commercial sale available from MIT.
//

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <string.h>

#define output(directions,pin) (directions |= pin) // set port direction for output
#define input(directions,pin) (directions &= (~pin)) // set port direction for input
#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define pin_test(pins,pin) (pins & pin) // test for port pin
#define bit_test(byte,bit) (byte & (1 << bit)) // test for bit set
#define bit_delay_time 100 // bit delay for 9600 with overhead
#define bit_delay() _delay_us(bit_delay_time) // RS232 bit delay
#define half_bit_delay() _delay_us(bit_delay_time/2) // RS232 half bit delay
#define led_delay() _delay_ms(1000) // LED flash delay


#define serial_port PORTA
#define serial_direction DDRA
#define serial_pins PINA
#define serial_pin_in (1 << PA0)
#define serial_pin_out (1 << PA1)

#define node_id 'N'

void get_char(volatile unsigned char *pins, unsigned char pin, char *rxbyte) {
   //
   // read character into rxbyte on pins pin
   //    assumes line driver (inverts bits)
   //
   *rxbyte = 0;
   while (pin_test(*pins,pin))
      //
      // wait for start bit
      //
      ;
   //
   // delay to middle of first data bit
   //
   half_bit_delay();
   bit_delay();
   //
   // unrolled loop to read data bits
   //
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 0);
   else
      *rxbyte |= (0 << 0);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 1);
   else
      *rxbyte |= (0 << 1);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 2);
   else
      *rxbyte |= (0 << 2);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 3);
   else
      *rxbyte |= (0 << 3);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 4);
   else
      *rxbyte |= (0 << 4);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 5);
   else
      *rxbyte |= (0 << 5);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 6);
   else
      *rxbyte |= (0 << 6);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 7);
   else
      *rxbyte |= (0 << 7);
   //
   // wait for stop bit
   //
   bit_delay();
   half_bit_delay();
   }

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

void put_string(volatile unsigned char *port, unsigned char pin, PGM_P str) {
   //
   // send character in txchar on port pin
   //    assumes line driver (inverts bits)
   // function that send stinges letter by letter
   static char chr;
   static int index;
   index = 0;
   do {
      chr = pgm_read_byte(&(str[index]));
      put_char(&serial_port, serial_pin_out, chr);
      ++index;
      } while (chr != 0);
   }
int main(void) {
   //
   // main
   //
  DDRA &= ~(1 << PA3);
  // set PA3 as input in DDRA

  PORTA |= (1 << PA3);
  // SET PULL UP RESISTOR IN PA3
  DDRB |= (1 << PB2);

  // set PB2 as output in DDRB
   static char chr;
   //
   // set clock divider to /1
   //
   CLKPR = (1 << CLKPCE);
   CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
   //
   // initialize output pins
   //
   set(serial_port, serial_pin_out);
   input(serial_direction, serial_pin_in);
   output(serial_direction, serial_pin_out);

      		//PORTB &= ~(1 << PB2);
                PORTB |= ( 1<< PB2);
                led_delay();
      		//PORTB |= ( 1<< PB2);
      		PORTB &= ~(1 << PB2);
                led_delay();

   
   //
   // main loop
   //
   while (1) {
      //get_char(&serial_pins, serial_pin_in, &chr);// this is the command that check for serial messages (like serialRead() in arduino
   //  get_char(&serial_pins, serial_pin_in, &chr);

   //   if (chr == 'x') {  // -
      	//	PORTB &= ~(1 << PB2);
              //     }
     // else if (chr == 'z') {  // -
      	//	PORTB |= ( 1<< PB2);
             //      }
     if (PINA &(1<< PA3))//if button not pressed
    {

 	PORTB |= (1 << PB2);//turn off the LED
       

      }
     else // if button pressed
     {       
	PORTB &= ~(1 << PB2);//turn on the LED
     output(serial_direction, serial_pin_out);
	put_char(&serial_port, serial_pin_out, 'b'); //send 'b' to serial out (TX)
	input(serial_direction, serial_pin_out);
                //led_delay();

     }

// what is happening with this code is that when the button is pressed the 'b' will be sending more than one time
// depending on the clock speed
              }
              }
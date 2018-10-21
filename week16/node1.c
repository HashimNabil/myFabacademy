
// FAB Rover Node1: Front left wheel
// by Hashim Nabil Al Sakkaf, Fabacademy 2017
// uaefabtech@gmail.com, http://archive.fabacademy.org/archives/2017/fablabuae/students/154/
// based on hello.bus45 of Neil http://academy.cba.mit.edu/classes/networking_communications/index.html

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

    // function difentions

      void left (void)
     {
      // 1.5 ms PWM on time
      //
      OCR1B = 1250;


      //
     }
      void mid (void)
     {
      // 1.5 ms PWM on time
      //
      OCR1B = 1875;


      //
     }
      void right (void)
     {
      //
      // 2 ms PWM on time
      //
      OCR1B = 2500;


      //
     }

     void dcc (int v)
     {
     OCR0B = v;
     PORTB &= ~(1 << PB2);
     }
void stop (void)
{
     PORTB &= ~(1 << PB2);
     PORTA &= ~(1 << PA7);
}
void dca (int v)
{
     OCR0A = v;
     PORTA &= ~(1 << PA7);
}

void dca (int v)
{
     OCR0A = v;
     PORTA &= ~(1 << PA7);
}
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
   // set clock divider to /1
   //
   CLKPR = (1 << CLKPCE);
   CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
   //
   // Servo Setup
   // set up timer 1
   //
   TCCR1A = (1 << COM1B1) | (0 << COM1B0); // clear OC1B on compare match
   TCCR1B = (0 << CS12) | (1 << CS11) | (0 << CS10) | (1 << WGM13); // prescaler /8, phase and frequency correct PWM, ICR1 TOP
   ICR1 = 25000; // 20 ms frequency
   // set PA5 as output
   DDRA |= (1 << PA5);
   // intilize PA5 to 0
   PORTA &= ~(1 << PA5);
//-----------------------------------------------------------------------------------------------------------------
   //  
   // DC motor setup
   // set up timer 0
   //
   // clear OC0A & OC0B on compare match
   TCCR0A = (1 << COM0A1) | (0 << COM0A0) | (1 << COM0B1) | (0 << COM0B0) | (1 << WGM01) | (1 << WGM00); 
   // prescaler /8, Fast PWM Mode, 0xFF Top
   TCCR0B = (0 << CS12) | (1 << CS11) | (0 << CS10) | (0 << WGM02); 
   // intilize DC motor PINS to 0 (IN1 & IN2)
   DDRA |= (1 << PA7);
   PORTA &= ~(1 << PA7);
   DDRB |= (1 << PB2);
   PORTB &= ~(1 << PB2);
   // intilize speed
   int speed = 0;
   //
   // main loop
   //
   //_delay_ms(2000);

   while (1) {
   //this function checks for serial messages (like serialRead() in arduino
   speed = 255;
   get_char(&serial_pins, serial_pin_in, &chr);
   if (chr == 'f') {  
      		      dca(speed);
                   }
   
   if (chr == 'b') {  
      		      dcc(speed);
                   }
   else
                   {
                    stop();
                   }
      }
   }
  
// Hashim Al Sakkaf
// FabLab UAE @2017
// Creative Commons Attribution 4.0 International License.

#include <avr/io.h>


int main (void)
{

  DDRB |= (1 << PB2);
  // set PB2 as output (LED)

  DDRA &= ~(1 << PA3);
  // set PA3 as input (Buttun)

  PORTA |= (1 << PA3);
  // Activate Pull-up resistor at PA3

 while(1) {

if (PINA &(1<< PA3))
{
//if button pressed

  PORTB &= ~(1 << PB2);
  // set PB2 low = switch on LED
}

else
{  

  PORTB |= (1 << PB2);
 // set PB2 high = switch off LED
}

        }
}
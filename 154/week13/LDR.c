
#include <avr/io.h>
#include <util/delay.h>

// This program turns on the LED when there is no liight
// Works with attiny44
// by Hashim Nabil Al Sakkaf @ Fabacademy 2017
// based on https://www.adnbr.co.uk/articles/adc-and-pwm-basics


int analogRead (void)
{
    //start ADC conversion
    ADCSRA |= (1 << ADSC);

    // Wait for it to finish
    while (ADCSRA & (1 << ADSC));

    return ADC;
}






int main (void)
{

// set clock divider to /1
//
CLKPR = (1 << CLKPCE);
CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);

DDRA |= (1 << PA7); // LED output at PA7


//ADMUX = (0 << REFS1) | (0 << REFS0) // Vcc ref
     //| (0 << MUX5)  | (0 << MUX4) | (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0); // ADC0 channel = PA0
   ADCSRA = (1 << ADEN) // enable
      | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // prescaler /128

int light = 0;

 while(1) {

      ADCSRA |= (1 << ADSC);
      //
      // wait for completion
      //
      while (ADCSRA & (1 << ADSC))
         ;
      //
_delay_ms(100);

if ( ADC < 770 )
{

  PORTA |= (1 << PA7);

}

else 
{

  PORTA &= ~(1 << PA7);

}


        }
}
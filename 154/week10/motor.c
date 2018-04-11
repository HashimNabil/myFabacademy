

// Modified by Hashim Nabil AL Sakkaf, Fabacademy 2017 #154
// so the PWM output is at PIN A5.

#include <avr/io.h>
#include <util/delay.h>

    // function difentions

      void left (void)
     {
      // 1.5 ms PWM on time
      //
      OCR1B = 1250;
      _delay_ms(2000);


      //
     }
      void mid (void)
     {
      // 1.5 ms PWM on time
      //
      OCR1B = 1875;
      _delay_ms(2000);


      //
     }
      void right (void)
     {
      //
      // 2 ms PWM on time
      //
      OCR1B = 2500;
      _delay_ms(2000);


      //
     }

     void dcc (int v)
     {
     OCR0B = v;
     PORTB &= ~(1 << PB2);
     }

void dca (int v)
{
     OCR0A = v;
     PORTA &= ~(1 << PA7);
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
   speed = 255;
   while (1) {
   
   left();
   dcc(speed);

   mid ();
   dca(speed/1.5);
   right();
     

      }
   }
  
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include<util/delay.h>

int main()
{
  DDRD |= (1 << PD6); //Fast PWM output at OC0A pin

  //Setting up feedback output pins
  DDRB |= 0x07;
  PORTB |= 0X5;
  _delay_ms(25); //period of beep sound
  PORTB &= 0xFB;

  int i = 255;
  while(1){
    PORTB |= (1<<1);
    int j = 0;
    while (j < 50){
      int k = 0;
      while (k < 20){
        OCR0A = i; // Duty cycle of 75%
        TCCR0A |= (1<<COM0A1) | (1<<COM0A0) | (1<<WGM01); //Inverting Fast PWM mode 3
        TCCR0B |= (0<<CS02) | (1<<CS01) | (1<<CS00); // No-Prescalar
        _delay_ms(1000);
        k = k+1;
      }

      i = (i-5) % 256;
      if (i < 0){
        i = i + 255;
      }

      j = j + 1;
    };

    i = 0;
    int l = 0;
    while(l < 10){
      int k = 0;
      while(k < 20){
        OCR0A = i; //Duty cycle of 75%
        TCCR0A |= (1<<COM0A1) | (1<<COM0A0) | (1<<WGM01); //Inverting Fast PWM mode 3
        TCCR0B |= (0<<CS02) | (1<<CS01) | (1<<CS00); // No-Prescalar
        _delay_ms(1000);
        k = k + 1;
      }

      i = (i+25)%256;
      if (i < 0){
        break;
      }

      l = l + 1;
    };

    // Switching off PWM signal
    DDRD &= (0<<PD6); //Fast PWM output at OC0A pin

    //switching off greed LED
    DDRB &= 0x01;
    PORTB &= (0<<1);

    //feedback beeps
    PORTB |= 0x5;
    _delay_ms(25);
    PORTB &= 0xF9;
    _delay_ms(75);
    PORTB |= 0x5;
    _delay_ms(25);
    PORTB &= 0xF9;

    break;
  };

  return 0;
}

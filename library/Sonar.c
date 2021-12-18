#include "Sonar.h"

void Sonar_init(){
  //distance detection
 //Do not set prescale here, only 256
  TCCR1B &= ~(1<<CS10);
  TCCR1B &= ~(1<<CS11);
  TCCR1B |= (1<<CS12);
   
  //Set Timer 0 to fast phase PWM  (second mode, TOP determine by OCRA)
   TCCR1B &= ~(1<<WGM13);
   TCCR1B &= ~(1<<WGM12);
   TCCR1A &= ~(1<<WGM11);
   TCCR1A &= ~(1<<WGM10);
  
   TCCR1B |= (1<<ICES1); //look for rising edge
   TIFR1  |= (ICF1);     //clear flag

   TIMSK1 |= (1<<ICIE1);   //set timer1
   
   DDRK |= (1<<DDK6);
   DDRK &=~(1<<DDK7);
}

void Sonar_Trigger(){
	   PORTK |=(1<<PORTK6);
	   _delay_us(10);
	   PORTK &= ~(1<<PORTK6);
}

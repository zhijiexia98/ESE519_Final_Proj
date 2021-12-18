#include "servo.h"


void servo_init(){
	DDRE |= (1<<DDE3);
	TCCR0B |= (1<<CS01);
	TCNT0 = 0xEB;  //20micro second
	TIMSK0 |= (1<<TOIE0);
}


unsigned char  Convert_Angle(unsigned char  k)
{
	unsigned char timer_value;
	int temp;
	temp = k*5;
	timer_value = temp/9;                       /* Timer value=(100/180)+25i.e(5/9)+25 */
	timer_value = timer_value+25;
	_delay_ms(3);
	return timer_value;                         /* Return timer value                  */
}

int Servo_AnglePlus(int Servo_Angle, int k){
	return Servo_Angle += k;
}


int Servo_AngleMinus(int Servo_Angle,int k){
	return Servo_Angle -= k;
}

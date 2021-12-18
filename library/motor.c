/*
 * Mecanum wheel motion
 * Forward: 
 * 
 */ 


#include "motor.h"

void speedcontrol(int delay1, int delay2){
	/*
	for(int i=0;i<30;i++){
		PORTB |= (1<<PORTB1);
		PORTB |= (1<<PORTB2);
		PORTB |= (1<<PORTB3);
		PORTB |= (1<<PORTB4);
		_delay_ms(25);
		PORTB &= ~(1<<PORTB1);
		PORTB &= ~(1<<PORTB2);
		PORTB &= ~(1<<PORTB3);
		PORTB &= ~(1<<PORTB4);
		_delay_ms(10);
	}
	*/
	for(int i=0;i<6;i++){
		PORTH |= (1<<PORTH6);
		PORTB |= (1<<PORTB4);
		PORTB |= (1<<PORTB5);
		PORTB |= (1<<PORTB6);
		_delay_ms(delay1);
		PORTH &= ~(1<<PORTH6);
		PORTB &= ~(1<<PORTB4);
		PORTB &= ~(1<<PORTB5);
		PORTB &= ~(1<<PORTB6);
		_delay_ms(delay2);
	}
	
}

void SpeedStop(){
		for(int i=0;i<30;i++){
			PORTH &= ~(1<<PORTH6);
			PORTB &= ~(1<<PORTB4);
			PORTB &= ~(1<<PORTB5);
			PORTB &= ~(1<<PORTB6);
			_delay_ms(35);
		}
}

void motor_init(){
	//GPIO initial
	//speed pins
	DDRH |= (1<<DDH6);
	DDRB |= (1<<DDB4);
	DDRB |= (1<<DDB5);
	DDRB |= (1<<DDB6);
	//front motor direction pins
	DDRF |= (1<<DDF0);
	DDRF |= (1<<DDF1);
	DDRF |= (1<<DDF2);
	DDRF |= (1<<DDF3);
	//rear motor direction pins
	DDRE |= (1<<DDE5);
	DDRH |= (1<<DDH3);
	DDRH |= (1<<DDH4);
	DDRH |= (1<<DDH5);
}



void FR_fwd()  //front-right wheel forward turn
{
	PORTF |=(1<<PORTF0);
	PORTF &=~(1<<PORTF1);
}

void FL_fwd() // front-left wheel forward turn
{
	PORTF |=(1<<PORTF2);
	PORTF &=~(1<<PORTF3);
}

void RR_fwd()  //rear-right wheel forward turn
{
	PORTE |=(1<<PORTE5);
	PORTH &=~(1<<PORTH3);
}


void RL_fwd()  //rear-left wheel forward turn
{
	PORTH |=(1<<PORTH4);
	PORTH &=~(1<<PORTH5);
}


void FR_bck() // front-right wheel backward turn
{
	PORTF &=~(1<<PORTF0);
	PORTF |= (1<<PORTF1);
}

void FL_bck() // front-left wheel backward turn
{
	PORTF &=~(1<<PORTF2);
	PORTF |= (1<<PORTF3);
}


void RR_bck()  //rear-right wheel backward turn
{
	PORTE &=~(1<<PORTE5);
	PORTH |= (1<<PORTH3);
}

void RL_bck()    //rear-left wheel backward turn
{
	PORTH &=~(1<<PORTH4);
	PORTH |= (1<<PORTH5);
}


void Forward(){
	FR_fwd();
	FL_fwd();
	RR_fwd();
	RL_fwd();
}


void Stop(){
	SpeedStop();
	PORTF &=~(1<<PORTF0);
	PORTF &=~(1<<PORTF1);
	PORTF &=~(1<<PORTF2);
	PORTF &=~(1<<PORTF3);
	PORTE &=~(1<<PORTE5);
	PORTH &=~(1<<PORTH3);
	PORTH &=~(1<<PORTH4);
	PORTH &=~(1<<PORTH5);
}


void Backward(){
	FR_bck();
	FL_bck();
	RR_bck();
	RL_bck();
}

void Leftturn(){
   	FR_fwd();
   	FL_bck();
   	RR_fwd();
   	RL_bck();
}



void Rightturn(){
	FR_bck();
	FL_fwd();
	RR_bck();
	RL_fwd();
}





void leftTop_corner(){
	
}


void rightTop_corner(){
	
}


void rightback_corner(){
	
}



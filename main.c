/*
 * ESE519 final project
 *
 * Created: 9/21/2021 21:21:21 AM
 * Author : Xiao Zhong, Zhijie Xia
 *
 * 
 */ 

 
#include "library\print.h"
#include "library\motor.h"
#include "library\servo.h"
#include "library\Sonar.h"

int Timer_Count = 0;
int Servo_Angle   = 0;
int Servo_Value   = 0;

volatile unsigned long edge = 0;
volatile unsigned long period = 0;
volatile int flag = 0;
volatile int count = 0;


//detection avoidance
int LoopTime=2; ////Watch if something is around every LPT loops while moving forward
int CycleTime=0;
int CheckTime=0;




void Initialize()
{
	cli();
   	UART_init();
    motor_init();
	servo_init();
	char String[25];
	//configurations of pins from WIFI module
	DDRK &= ~(1<<DDK0);
	DDRK &= ~(1<<DDK1);
	DDRK &= ~(1<<DDK2);
	DDRK &= ~(1<<DDK3);
	DDRK &= ~(1<<DDK4);
	DDRK &= ~(1<<DDK5);
	DDRK &= ~(1<<DDK7);
	
    //Sonar_init();
  TCCR4B &= ~(1<<CS40);
  TCCR4B &= ~(1<<CS41);
  TCCR4B |= (1<<CS42);
  
  //Set Timer 0 to fast phase PWM  (second mode, TOP determine by OCRA)
  TCCR4B &= ~(1<<WGM43);
  TCCR4B &= ~(1<<WGM42);
  TCCR4A &= ~(1<<WGM41);
  TCCR4A &= ~(1<<WGM40);
  
  TCCR4B |= (1<<ICES4); //look for rising edge
  TIFR4  |= (ICF4);     //clear flag

  TIMSK4 |= (1<<ICIE4);   //set timer1
 
  DDRK |= (1<<DDK6);
  DDRL &=~(1<<DDL0);
	sei();
}


ISR(TIMER4_CAPT_vect){
	TCCR4B ^= (1<<ICES4);
	period = ICR4 - edge;
	edge = ICR4;
}


ISR(TIMER0_OVF_vect)
{

	Timer_Count++;                              /* Variable for count overflow         */
	
	if( Timer_Count < 125 )                     /* Count for 180 degree i.e. 2.5ms     */
	TCNT0=0XEB;                                /* Load timer value for 20us pulse     */
	
	if( Timer_Count == Servo_Value )
	PORTE &= ~(1 << PINE3);                        /* Clearing servo pin                  */
	
	if( Timer_Count >= 125 )                    /* Angle greater than 180              */
	{
		TCNT0=0X97;                                /* 3.5 ms  delay                       */
		PORTE |= (1 << PINE3);                                /* Set pin connected to servo          */
	}
	if( Timer_Count == 130 )                    /* 17.5ms(5*3.5) ie:2.5+17.5=20mS      */
	{
		PORTE  |= (1 << PINE3);                               /* Set pin connected to servo          */
		TCCR0B |= (1<<CS01);           //timer0 setup Prescale of 010
		TCNT0 = 0XEB;                              /* Load 20us pulse                     */
		Timer_Count = 0;                           /* Clear timer count                   */
	}
}



int watch(){
	       Sonar_Trigger();
	       int distance=(period*544)/2000;
		   return distance;
}

int Watching(){
	
	int obstacle_status= 0b100000; 
	int CenterDistance =  watch();
	if(CenterDistance < 20){
		Stop();
		obstacle_status = obstacle_status | 0b100;
	}
	Servo_Value = Convert_Angle(135); //120 degree
  	_delay_ms(100);
    int LeftDistance_D =  watch();
	if(LeftDistance_D < 20) {
		Stop();
		obstacle_status = obstacle_status | 0b1000;
	}
	Servo_Value = Convert_Angle(175); //180 degree
	_delay_ms(300);
	int LeftDistance =  watch();
	if(LeftDistance < 20) {
		Stop();
		obstacle_status = obstacle_status | 0b10000;
	}   
	Servo_Value = Convert_Angle(90); //90 degree
	_delay_ms(100);
    CenterDistance =  watch();
	if(CenterDistance < 20) {
		Stop();
		obstacle_status = obstacle_status | 0b100;
	}	
	Servo_Value = Convert_Angle(45); //40 degree
	_delay_ms(100);
	int RightDistance_D =  watch();
	if(RightDistance_D < 20) {
		Stop();
		obstacle_status = obstacle_status | 0b10;
	}
	Servo_Value = Convert_Angle(0); 
	int RightDistance =  watch();
	if(RightDistance < 20) {
		Stop();
		obstacle_status = obstacle_status | 1;
	}
	Servo_Value = Convert_Angle(90); //90 degree
	_delay_ms(300);
	
	    sprintf(String,"data: %d \r\n",obstacle_status);
	    UART_putstring(String);
	
	
	return obstacle_status;
}

void Auto_avoidance(){
	CycleTime+=1;
	//char Obstacle[5] = "";
	int Obstacle=0;
	if(CycleTime>=LoopTime){

	   //Stop();
	   //strcat(Obstacle,Watching());
	   Obstacle = Watching();
	   if(Obstacle==32 || Obstacle==48){
		   //10000
		   speedcontrol(25,10);
		   Forward();
		   	_delay_ms(250);
		   //Stop();
	   }else if(Obstacle==33){
		   //00001
		   	speedcontrol(25,10);
		    Forward();
		    _delay_ms(250);
		    //Stop();
	   }else if (Obstacle==60 || Obstacle==40 || Obstacle == 56 || Obstacle == 52  || Obstacle == 44 || Obstacle == 36  ){
	       //11100  01000 11000  10100  01100 00100 01000
	       speedcontrol(25,10);
		   		    sprintf(String,"case right \r\n");
		   		    UART_putstring(String);
	       Rightturn();
		    _delay_ms(250);
		   //Stop();
	   }
	   else if (Obstacle == 34 || Obstacle == 39 || Obstacle == 35 || Obstacle == 37  ||  Obstacle == 38 || Obstacle == 42 ){
		   //00010 00111 00011 00101 00110 01010
		   speedcontrol(25,10);
		   		    sprintf(String,"case left \r\n");
		   		    UART_putstring(String);
		   Leftturn();
		   _delay_ms(250);
		   //Stop();
	   }
	   else if  (Obstacle == 47 || Obstacle == 55 || Obstacle == 63){
		   //01111 10111 11111
		   speedcontrol(25,10);
		      sprintf(String,"case backward \r\n");
		      UART_putstring(String);	   
		   	Backward();
			speedcontrol(25,10);
		   	Rightturn();
		    _delay_ms(250);
		   //Stop();
	   }else if  (Obstacle == 59 || Obstacle == 61 || Obstacle == 62 || Obstacle == 46){
		   //11011 11101 11110 01110 
		   speedcontrol(25,10);
		    sprintf(String,"case backward \r\n");
		    UART_putstring(String);
		   Backward();
		   speedcontrol(25,10);
		   Leftturn();
		   _delay_ms(250);
		   //Stop();
	   }	

	 CycleTime = 0; //reset count for cycles
	   
	}
/**
	else {
		speedcontrol();
		 _delay_ms(100);
	    Forward();
		//Stop();
	}
**/
	int distance1 =  watch();
	if(distance1<20){
	    speedcontrol(25,10);
		Backward();
		 _delay_ms(100);
		 CheckTime+=1;
	}
	if(distance1>20){
		CheckTime=0;
	}
	if(CheckTime>10){
		Stop();
		CheckTime=0;
	}

 }


int main(void)
{
	Initialize();
	int flagTurn = 0;
	unsigned int distance = 0;
	int delay1=15;
	int delay2=20;
	while (1) 
    {
	  // Auto_avoidance();

	 
      if(PINK & (1<<PINK4)){
		  if(flag == 0){
			  flag = 1;
			  count += 1;
		  }
	  }else{
		  flag = 0;
	  }
	  if(count == 1){
		  Auto_avoidance();
		 // sprintf(String,"auto shit \r\n");
		 // UART_putstring(String);
	  }else{
		  
		   if(PINK & (1<<PINK5)){
			   delay1=25;
			   delay2=10;
		   }
		   if(PINK & (1<<PINK7)){
			   delay1=15;
			   delay2=20;
		   }

       
	  if(PINK & (1<<PINK0)){
		sprintf(String,"left \r\n");
	    UART_putstring(String);
		speedcontrol(delay1,delay2);
		Forward();
	  }
	  
	  if(PINK & (1<<PINK1)){
		sprintf(String,"right \r\n");
		UART_putstring(String);
		speedcontrol(delay1,delay2);
		Backward();  
	  }
	  
	   if(PINK & (1<<PINK2)){
		   sprintf(String,"right \r\n");
		   UART_putstring(String);
		   speedcontrol(delay1,delay2);
		   Leftturn();
	   }
	   
	    if(PINK & (1<<PINK3)){
		    sprintf(String,"right \r\n");
		    UART_putstring(String);
		    speedcontrol(delay1,delay2);
		    Rightturn();
	    }
		count = 0;
	  }
	
	}
}
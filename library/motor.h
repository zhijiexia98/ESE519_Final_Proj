#ifndef _MOTOR_H
#define _MOTOR_H  //It is used to check if define has been given for other file earlier

#include "norm_lib.h"

void Forward();
void speedcontrol(int delay1, int delay2);
//void Stop();
void Backward();
void Leftturn();
void Rightturn();
void motor_init();
void Stop();

#define speedPinR 9   //  Front Wheel PWM pin connect Right MODEL-X ENA
#define RightMotorDirPin1  A0    //Front Right Motor direction pin 1 to Right MODEL-X IN1  (K1)
#define RightMotorDirPin2  A1   //Front Right Motor direction pin 2 to Right MODEL-X IN2   (K1)
#define LeftMotorDirPin1  A2    //Front Left Motor direction pin 1 to Right MODEL-X IN3 (K3)
#define LeftMotorDirPin2  A3   //Front Left Motor direction pin 2 to Right MODEL-X IN4 (K3)
#define speedPinL 10   //  Front Wheel PWM pin connect Right MODEL-X ENB

#define speedPinRB 11   //  Rear Wheel PWM pin connect Left MODEL-X ENA
#define RightMotorDirPin1B  5    //Rear Right Motor direction pin 1 to Left  MODEL-X IN1 ( K1)
#define RightMotorDirPin2B 6    //Rear Right Motor direction pin 2 to Left  MODEL-X IN2 ( K1)
#define LeftMotorDirPin1B 7    //Rear Left Motor direction pin 1 to Left  MODEL-X IN3  (K3)
#define LeftMotorDirPin2B 8  //Rear Left Motor direction pin 2 to Left  MODEL-X IN4 (K3)
#define speedPinLB 12    //  Rear Wheel PWM pin connect Left MODEL-X ENB

#define FAST_SPEED  160   //both sides of the motor speed
#define SPEED  120     //both sides of the motor speed
#define TURN_SPEED  120   //both sides of the motor speed
#define BACK_SPEED1  160   //back speed
#define BACK_SPEED2  90    //back speed
#endif 
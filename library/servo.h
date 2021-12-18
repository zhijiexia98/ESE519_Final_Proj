#ifndef _MOTOR_H
#define _MOTOR_H  //It is used to check if define has been given for other file earlier
#include "norm_lib.h"



void servo_init();
int Servo_AnglePlus(int Servo_Angle,int k);
int Servo_AngleMinus(int Servo_Angle,int k);


#endif
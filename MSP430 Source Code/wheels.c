//------------------------------------------------------------------------------
//  File: wheels.c
//  Description: This file performs the logic to make the car go in a circle,
//               a figure 8, and a triangle
//
//  Zach Hannum
//  Feb 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//
// Globals
// --------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

extern volatile unsigned int leftForwardRate;
extern volatile unsigned int leftReverseRate;
extern volatile unsigned int rightForwardRate;
extern volatile unsigned int rightReverseRate;

void Left_Wheel_Off(void){
  leftForwardRate = OFF;
  leftReverseRate = OFF;
  TB2CCR1 = leftForwardRate;
  TB2CCR2 = leftReverseRate;

}

void Right_Wheel_Off(void){
  rightForwardRate = OFF;
  rightReverseRate = OFF;
  TB1CCR1 = rightForwardRate;
  TB1CCR2 = rightReverseRate;
}

void Wheels_Off(void){
  leftForwardRate = OFF;
  leftReverseRate = OFF;
  rightForwardRate = OFF;
  rightReverseRate = OFF;
  TB1CCR1 = rightForwardRate;
  TB1CCR2 = rightReverseRate;
  TB2CCR1 = leftForwardRate;
  TB2CCR2 = leftReverseRate;
}

void Wheels_Forward_On(int duty){
  Wheels_Off();
  rightForwardRate = duty;
  leftForwardRate = duty;
  TB1CCR1 = rightForwardRate;
  TB2CCR1 = leftForwardRate;
}

void Wheels_Reverse_On(int duty){
  Wheels_Off();
  rightReverseRate = duty;
  leftReverseRate = duty;
  TB1CCR2 = rightReverseRate;
  TB2CCR2 = leftReverseRate;
}

void Right_Wheel_Forward_On(int duty){
  Right_Wheel_Off();
  rightForwardRate = duty;
  TB1CCR1 = rightForwardRate;
}

void Right_Wheel_Reverse_On(int duty){
  Right_Wheel_Off();
  rightReverseRate = duty;
  TB1CCR2 = rightReverseRate;
}

void Left_Wheel_Forward_On(int duty){
  Left_Wheel_Off();
  leftForwardRate = duty;
  TB2CCR1 = leftForwardRate;
}

void Left_Wheel_Reverse_On(int duty){
  Left_Wheel_Off();
  leftReverseRate = duty;
  TB2CCR2 = leftReverseRate;
}



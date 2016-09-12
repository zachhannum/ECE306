//------------------------------------------------------------------------------
//  File: TimerA0.c
//  Description: This file sets up TimerA0
//
//
//  Zach Hannum
//  Feb 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

volatile unsigned int rightForwardRate;
volatile unsigned int rightReverseRate;

void Init_Timer_B1(void){
//----------------------------------------------------------------------------
// 
//===========================================================================
// Function name: Init_Timer_B1
//
// Description: Initializes timer B1 for use with right wheel forward and reverse pwm
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: 
//
// Author:  Zach Hannum
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//===========================================================================
  
  TB1CTL = TBSSEL__SMCLK; //SMCLK
  TB1CTL |= MC_1;         //UP MODE
  TB1CTL |= TBCLR;        //CLEAR TAR
  
  rightForwardRate = OFF;
  rightReverseRate = OFF;
  
  TB1CCR0 = WHEEL_PERIOD;
  TB1CCTL1 = OUTMOD_7;
  TB1CCR1 = rightForwardRate;
  TB1CCTL2 = OUTMOD_7;
  TB1CCR2 = rightReverseRate;
  
  
  
}





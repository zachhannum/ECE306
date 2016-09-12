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

volatile unsigned int leftForwardRate;
volatile unsigned int leftReverseRate;

void Init_Timer_B2(void){
//----------------------------------------------------------------------------
// 
//===========================================================================
// Function name: Init_Timer_B2
//
// Description: Initializes timer B2 for use with left wheel forward and reverse pwm
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
  
  TB2CTL = TBSSEL__SMCLK; //SMCLK
  TB2CTL |= MC_1;         //UP MODE
  TB2CTL |= TBCLR;        //CLEAR TAR
  
  leftForwardRate = OFF;
  leftReverseRate = OFF;
  
  TB2CCR0 = WHEEL_PERIOD;
  TB2CCTL1 = OUTMOD_7;
  TB2CCR1 = leftForwardRate;
  TB2CCTL2 = OUTMOD_7;
  TB2CCR2 = leftReverseRate;
  
  
  
}





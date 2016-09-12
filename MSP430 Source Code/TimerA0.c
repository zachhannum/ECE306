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

void Init_Timer_A0(void){
//----------------------------------------------------------------------------
// 
//===========================================================================
// Function name: Init_Timer_A0 
//
// Description: Initializes timer A0 and sets timer A0 interrupt
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: 
//  extern int sw1IsDebouncing;
//  extern int sw2IsDebouncing;
//  extern volatile unsigned int sw1DebounceCount;
//  extern volatile unsigned int sw2DebounceCount;
//
// Author:  Zach Hannum
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//===========================================================================
  
  TA0CTL = TASSEL__SMCLK;
  TA0CTL |= TACLR;
  TA0CTL |= MC__CONTINUOUS;
  TA0CTL |= ID__2; // Divide clock by 2
  TA0CTL &= ~TAIE; // Disable Overflow Interrupt
  TA0CTL &= ~TAIFG; 
  
  TA0EX0 = TAIDEX_7; // Divide clock by an additional 8
 
  TA0CCR0 = TA0CCR0_INTERVAL; // CCR0
  TA0CCTL0 |= CCIE; // CCR0 enable interrupt

  // TA0CCR1 = TA0CCR1_INTERVAL; // CCR1
 // TA0CCTL1 |= CCIE; // CCR1 enable interrupt

// TA0CCR2 = TA0CCR2_INTERVAL; // CCR2
// TA0CCTL2 |= CCIE; // CCR2 enable interrupt 
  
  
  
}





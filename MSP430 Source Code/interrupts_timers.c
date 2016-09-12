//------------------------------------------------------------------------------
//  File: main.c
//  Description: This file contains the Main Routine - "While" Operating System
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

extern int sw1IsDebouncing;
extern int sw2IsDebouncing;
extern volatile unsigned int sw1DebounceCount;
extern volatile unsigned int sw2DebounceCount;
volatile unsigned int timer;
extern volatile unsigned long int time;
extern volatile int countTime; 
volatile int minuteTime = 0;

extern volatile int adc_time;
extern volatile int count_adc_time;

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void){
//===========================================================================
// Function name: Timer0_A0_ISR 
//
// Description: This timer interrupt controls the debounce time for SW1 and
//              SW2. It also turns itself off when the debounce is complete.
//
// Interrupt Trigger: CCR0
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
  
  if(countTime){
  
    time = time + 1;
  }
  if(count_adc_time){
    adc_time = adc_time + 1;
  }
  if(timer > TIMER_MAX) timer = ZERO;
  timer = timer + ONE;
  TA0CCR0 += TA0CCR0_INTERVAL; // Add Offset to TACCR0
}
//----------------------------------------------------------------------------
// 
//===========================================================================
// Function name: Timer0_A1_ISR 
//
// Description: TimerA0 1-TWO, Overflow Interrupt Vector (TAIV) handler.
//              Does nothing right now, Overflow is disabled.
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
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void){
  switch(__even_in_range(TA0IV,FOURTEEN)){
  case ZERO: break; // No interrupt
  case TWO: // CCR1 not used
    //TA0CCR1 += TA0CCR1_INTERVAL; // Add Offset to TACCR1
    break;
  case FOUR: // CCR2 not used
    //TA0CCR2 += TA0CCR2_INTERVAL; // Add Offset to TACCR2
    break;
  case FOURTEEN: // overflow
    break;
  default: break;
  }
}
//----------------------------------------------------------------------------

#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR(void){
//===========================================================================
// Function name: Timer1_A0_ISR 
//
// Description: This timer interrupt controls the debounce time for SW1 and
//              SW2. It also turns itself off when the debounce is complete.
//
// Interrupt Trigger: CCR0
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
  
  Display_Process();
  TA1CCR0 += TA1CCR0_INTERVAL; // Add Offset to TACCR0
}
//----------------------------------------------------------------------------
// 
//===========================================================================
// Function name: Timer1_A1_ISR 
//
// Description: TimerA0 1-TWO, Overflow Interrupt Vector (TAIV) handler.
//              Does nothing right now, Overflow is disabled.
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
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR(void){
  switch(__even_in_range(TA1IV,FOURTEEN)){
  case ZERO: break; // No interrupt
  case TWO: // CCR1 not used
    //TA0CCR1 += TA0CCR1_INTERVAL; // Add Offset to TACCR1
    break;
  case FOUR: // CCR2 not used
    //TA0CCR2 += TA0CCR2_INTERVAL; // Add Offset to TACCR2
    break;
  case FOURTEEN: // overflow
    break;
  default: break;
  }
}
//----------------------------------------------------------------------------
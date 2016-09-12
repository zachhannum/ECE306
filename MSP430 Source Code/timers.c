//------------------------------------------------------------------------------
//  File: timers.c
//  Description: This file initializes timers contains functions 
//               for timers
//
//  Zach Hannum
//  Feb 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//
// Globals
// --------
// extern volatile unsigned int Time_Sequence;
// extern volatile char one_time;
// extern volatile unsigned int five_msec_count;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
extern volatile unsigned int five_msec_count;
extern volatile unsigned int timer;
extern volatile int black_line_detected;


void Init_Timers(void){
//----------------------------------------------------------------------------
// 
//===========================================================================
// Function name: Init_Timers 
//
// Description: Initializes Timers
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
  Init_Timer_A0(); //
  Init_Timer_A1(); // 
//  Init_Timer_B0(); // 
  Init_Timer_B1(); //  
  Init_Timer_B2();   //  Required for provided compiled code to work
//------------------------------------------------------------------------------
}

void sleep(int sleepTime){
//----------------------------------------------------------------------------
// 
//===========================================================================
// Function name: sleep 
//
// Description: sleeps for the amount sleepTime
//
// Passed : sleepTime
// Locals: no variables declared
// Returned: no values returned
// Globals: timer
//
// Author:  Zach Hannum
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//===========================================================================
  
  timer = ZERO;
  black_line_detected = 0;
  while(timer < sleepTime);
  
}

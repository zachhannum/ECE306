//------------------------------------------------------------------------------
//  File: timers.c
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

extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;
extern volatile unsigned int Time_Sequence;

void shape(void){
//===========================================================================
// Function name: shape
//
// Description: This function drives the car forward 1 sec, reverse 2 secs,
//              forward 1 sec, clockwise for 1 sec, and counter-clockwise for 1 sec
//
// Passed : no variables passed
// Locals: count
// Returned: no values returned
// Globals: 
//
// Author:  Zach Hannum
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//===========================================================================

  
}
  
  
  
  

//------------------------------------------------------------------------------
//  File: LED.c
//  Description: This file initializes LEDs
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

void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//
// Port J
// PJOUT
// LED1  (0x01)
// LED2  (0x02)
// LED3  (0x04)
//  
// PORT 3
// PJOUT
// LED5  (0x10)
// LED6  (0x20)
// LED7  (0x40)
// LED8  (0x80)
//------------------------------------------------------------------------------
// Turns on all 8 LEDs
  PJOUT &= ~IOT_WAKEUP;
  PJOUT &= ~IOT_FACTORY;
  PJOUT &= ~IOT_STA_MINIAP;
//------------------------------------------------------------------------------
}
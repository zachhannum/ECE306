//------------------------------------------------------------------------------
//  File display.c
//  Description: This file processes the LCD display
//
//
//  Zach Hannum
//  Feb 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//
// Globals
// -------
// extern char *display_1;
// extern char *display_2;
// extern char *display_3;
// extern char *display_4;
// extern char posL1;
// extern char posL2;
// extern char posL3;
// extern char posL4;
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

void Display_Process(void){
//------------------------------------------------------------------------------
// Output display lines 1-4 to LCD
//
// Globals
// -------
// extern char *display_1;
// extern char *display_2;
// extern char *display_3;
// extern char *display_4;
// extern char posL1;
// extern char posL2;
// extern char posL3;
// extern char posL4;
//
// Ports
// LCD_HOME_L1
// LCD_HOME_L2
// LCD_HOME_L3
// LCD_HOME_L4
//------------------------------------------------------------------------------
  ClrDisplay();
  lcd_out(display_1, LCD_HOME_L1, posL1);
  lcd_out(display_2, LCD_HOME_L2, posL2);
  lcd_out(display_3, LCD_HOME_L3, posL3);
  lcd_out(display_4, LCD_HOME_L4, posL4);
}
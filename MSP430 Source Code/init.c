//------------------------------------------------------------------------------
//  File: init.c
//  Description: This file initializes 
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

extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char display_line_1[ELEVEN];
extern char display_line_2[ELEVEN];
extern char display_line_3[ELEVEN];
extern char display_line_4[ELEVEN];


void Init_Conditions(void){
  //------------------------------------------------------------------------------
  // Initializations Configurations
  //
  // Globals
  // --------
  // extern char *display_1;
  // extern char *display_2;
  // extern char *display_3;
  // extern char *display_4;
  // extern char display_line_1[ELEVEN];
  // extern char display_line_2[ELEVEN];
  // extern char display_line_3[ELEVEN];
  // extern char display_line_4[ELEVEN];
  //------------------------------------------------------------------------------
  // Interrupts are disabled by default, enable them. 
  enable_interrupts();
  display_1 = &display_line_1[ZERO];
  display_2 = &display_line_2[ZERO];
  display_3 = &display_line_3[ZERO];
  display_4 = &display_line_4[ZERO];
  
  
  //------------------------------------------------------------------------------
}


//------------------------------------------------------------------------------
//  File: main.c
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Zach Hannum
//  Feb 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//
//
// Globals 
//---------
// volatile unsigned char control_state[CNTL_STATE_INDEX]; //
// volatile unsigned int Time_Sequence;
// char led_smclk;
// volatile char one_time;
// volatile unsigned int five_msec_count;
// extern char display_line_1[11];             
// extern char display_line_2[11];            
// extern char display_line_3[11];             
// extern char display_line_4[11];             
// extern char *display_1;                     // Line 1 of LCD Display 
// extern char *display_2;                     // Line 2 of LCD Display  
// extern char *display_3;                     // Line 3 of LCD Display  
// extern char *display_4;                     // Line 4 of LCD Display 
// char posL1;
// char posL2;
// char posL3;
// char posL4;
// char size_count;
// char big;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

// global variables
volatile unsigned int fram_rx_ring_wr;
volatile unsigned int cpu_rx_ring_wr;
extern volatile char FRAM_Char_Rx[SMALL_RING_SIZE];
extern volatile char CPU_Char_Rx[SMALL_RING_SIZE];
extern volatile int send_ready;
extern volatile int increment;
int command_flag = ZERO;
//------------------------------------------------------------------------------
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){
  unsigned int temp;
  char tempchar;
  unsigned int tempUCA = UCA0IV;
  switch(tempUCA){
  case ONE: // Vector 0 - no interrupt
    break;
  case TWO: // Vector 2 - RXIFG
    increment = ONE;
    temp = fram_rx_ring_wr;
    tempchar = UCA0RXBUF;
    if(temp && (tempchar == '.')) command_flag = ONE;
    UCA0TXBUF = tempchar;
    FRAM_Char_Rx[temp] = tempchar; // RX -> USB_Char_Rx character
    if (++fram_rx_ring_wr >= (SMALL_RING_SIZE)){
      fram_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
    }
    if(tempchar == '\r') fram_rx_ring_wr = BEGINNING;
    break;
  case FOUR: // Vector 4 – TXIFG
    
    break;
  default: break;
  }
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void){
  unsigned int temp;
  unsigned int tempUCA = UCA1IV;
  char tempchar;
  switch(tempUCA){
  case ZERO: // Vector 0 - no interrupt
    break;
  case TWO: // Vector 2 - RXIFG
    increment = ONE;
    temp = cpu_rx_ring_wr;
    tempchar = UCA1RXBUF;
    CPU_Char_Rx[temp] = tempchar; // RX -> USB_Char_Rx character
    if (++cpu_rx_ring_wr >= (SMALL_RING_SIZE)){
      cpu_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
    }
    break;
  case FOUR: // Vector 4 – TXIFG
    break;
  default: break;
  }
}
//------------------------------------------------------------------------------


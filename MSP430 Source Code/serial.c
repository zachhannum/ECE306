//------------------------------------------------------------------------------
//  File: serial.c
//  Description: This file handles serial communications initializations and interrupts
//
//  Zach Hannum
//  Feb 2016
//  Built with IAR Embedded Workbench Version: V7.3.YES.3987 (6.40.YES)
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

extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char display_line_1[ELEVEN];
extern char display_line_2[ELEVEN];
extern char display_line_3[ELEVEN];
extern char display_line_4[ELEVEN];
volatile char CPU_Char_Rx[SMALL_RING_SIZE];
volatile char FRAM_Char_Rx[SMALL_RING_SIZE];
volatile unsigned int fram_rx_ring_wr;
volatile unsigned int fram_tx_ring_wr;
volatile unsigned int fram_tx_ring_rd;
volatile unsigned int fram_rx_ring_rd;
volatile unsigned int cpu_rx_ring_wr;
extern int BAUD_MODE;
extern volatile int increment;
volatile int command_flag = CLR;
volatile int command_received = CLR;

volatile int send_iot_command = CLR;
volatile int reset_iot = CLR;
char DISASSOCIATION[EIGHT]= "+WIND:41";
char IPADD[EIGHT] = "WiFi Up:";
char IP[SIXTEEN];
volatile int ip_detected;
volatile char command[MAX_COMMAND_LENGTH];
volatile int command_sent;
char BSSLOST[BSSLOST_STRING_MAX] = "+WIND:30:";


void Init_Serial_UCA0(int MODE){
  //===========================================================================
  // Function name: Init_Serial_UCA0
  //
  // Description: Initializes Serial communications for USB
  //
  // Passed : int MODE
  // Locals: no variables declared
  // Returned: no values returned
  // Globals: 
////extern char *display_1;
////extern char *display_2;
////extern char *display_3;
////extern char *display_4;
////extern char display_line_1[ELEVEN];
////extern char display_line_2[ELEVEN];
////extern char display_line_3[ELEVEN];
////extern char display_line_4[ELEVEN];
////volatile char CPU_Char_Rx[SMALL_RING_SIZE];
////volatile char FRAM_Char_Rx[SMALL_RING_SIZE];
////volatile unsigned int fram_rx_ring_wr;
////volatile unsigned int fram_tx_ring_wr;
////volatile unsigned int fram_tx_ring_rd;
////volatile unsigned int fram_rx_ring_rd;
////volatile unsigned int cpu_rx_ring_wr;
////extern int BAUD_MODE;
////extern volatile int increment;
////volatile int command_flag = CLR;
////volatile int command_received = CLR;
////
////volatile int send_iot_command = CLR;
////volatile int reset_iot = CLR;
////char DISASSOCIATION[EIGHT]= "+WIND:41";
////char IPADD[EIGHT] = "WiFi Up:";
////char IP[SIXTEEN];
////volatile int ip_detected;
////volatile char command[MAX_COMMAND_LENGTH];
////volatile int command_sent;
  //
  // Author:  Zach Hannum
  // Date: Feb 2016
  // Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.YES)
  //===========================================================================
  int i;
  for(i=CLR; i<SMALL_RING_SIZE; i++){
    FRAM_Char_Rx[i] = CLR_REG; // USB Rx Buffer
  }
  fram_rx_ring_wr = BEGINNING;
  fram_rx_ring_rd = BEGINNING;
  
  fram_tx_ring_wr = BEGINNING;
  fram_tx_ring_rd = BEGINNING;
  // Configure UART CLR
  UCA0CTLW0 = CLR; // Use word register
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA0CTLW0 |= UCSWRST; // Set Software reset enable
  switch (MODE){ 
  case LOW_BAUD:
    UCA0BRW = LOW_BAUD_BRW;
    UCA0MCTLW = LOW_BAUD_MCTLW ;
    
    break;
    
  case HIGH_BAUD:
    UCA0BRW = HIGH_BAUD_BRW;
    UCA0MCTLW = HIGH_BAUD_MCTLW;
    
    break;
    
  default:
    UCA0BRW = LOW_BAUD_BRW;
    UCA0MCTLW = LOW_BAUD_MCTLW;
    
    break;
    
  }
  
  UCA0CTL1 &= ~UCSWRST; // Release from reset
  UCA0IE |= UCRXIE; // Enable RX interrupt
  
}

void Init_Serial_UCA1(int MODE){
  //===========================================================================
  // Function name: Init_Serial_UCA1
  //
  // Description: initializes IoT serial communications
  //
  // Passed : int MODE
  // Locals: no variables declared
////extern char *display_1;
////extern char *display_2;
////extern char *display_3;
////extern char *display_4;
////extern char display_line_1[ELEVEN];
////extern char display_line_2[ELEVEN];
////extern char display_line_3[ELEVEN];
////extern char display_line_4[ELEVEN];
////volatile char CPU_Char_Rx[SMALL_RING_SIZE];
////volatile char FRAM_Char_Rx[SMALL_RING_SIZE];
////volatile unsigned int fram_rx_ring_wr;
////volatile unsigned int fram_tx_ring_wr;
////volatile unsigned int fram_tx_ring_rd;
////volatile unsigned int fram_rx_ring_rd;
////volatile unsigned int cpu_rx_ring_wr;
////extern int BAUD_MODE;
////extern volatile int increment;
////volatile int command_flag = CLR;
////volatile int command_received = CLR;
////
////volatile int send_iot_command = CLR;
////volatile int reset_iot = CLR;
////char DISASSOCIATION[EIGHT]= "+WIND:41";
////char IPADD[EIGHT] = "WiFi Up:";
////char IP[SIXTEEN];
////volatile int ip_detected;
////volatile char command[MAX_COMMAND_LENGTH];
////volatile int command_sent;
  //
  // Author:  Zach Hannum
  // Date: Feb 2016
  // Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.YES)
  //===========================================================================
  int i;
  for(i=CLR; i<SMALL_RING_SIZE; i++){
    FRAM_Char_Rx[i] = CLR_REG; // USB Rx Buffer
  }
  fram_rx_ring_wr = BEGINNING;
  fram_rx_ring_rd = BEGINNING;
  
  fram_tx_ring_wr = BEGINNING;
  fram_tx_ring_rd = BEGINNING;
  // Configure UART CLR
  UCA1CTLW0 = CLR; // Use word register
  UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA1CTLW0 |= UCSWRST; // Set Software reset enable
  switch (MODE){ 
  case LOW_BAUD:
    UCA1BRW = LOW_BAUD_BRW;
    UCA1MCTLW = LOW_BAUD_MCTLW ;
    
    break;
    
  case HIGH_BAUD:
    UCA1BRW = HIGH_BAUD_BRW;
    UCA1MCTLW = HIGH_BAUD_MCTLW;
    
    break;
    
  default:
    UCA1BRW = LOW_BAUD_BRW;
    UCA1MCTLW = LOW_BAUD_MCTLW;
    
    break;
    
  }
  
  UCA1CTL1 &= ~UCSWRST; // Release from reset
  UCA1IE |= UCRXIE; // Enable RX interrupt
  
  
}

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){
  //===========================================================================
  // Function name: USCI_A0_ISR
  //
  // Description: controls USB interrupts
  //
  // Passed : int MODE
  // Locals: no variables declared
////extern char *display_1;
////extern char *display_2;
////extern char *display_3;
////extern char *display_4;
////extern char display_line_1[ELEVEN];
////extern char display_line_2[ELEVEN];
////extern char display_line_3[ELEVEN];
////extern char display_line_4[ELEVEN];
////volatile char CPU_Char_Rx[SMALL_RING_SIZE];
////volatile char FRAM_Char_Rx[SMALL_RING_SIZE];
////volatile unsigned int fram_rx_ring_wr;
////volatile unsigned int fram_tx_ring_wr;
////volatile unsigned int fram_tx_ring_rd;
////volatile unsigned int fram_rx_ring_rd;
////volatile unsigned int cpu_rx_ring_wr;
////extern int BAUD_MODE;
////extern volatile int increment;
////volatile int command_flag = CLR;
////volatile int command_received = CLR;
////
////volatile int send_iot_command = CLR;
////volatile int reset_iot = CLR;
////char DISASSOCIATION[EIGHT]= "+WIND:41";
////char IPADD[EIGHT] = "WiFi Up:";
////char IP[SIXTEEN];
////volatile int ip_detected;
////volatile char command[MAX_COMMAND_LENGTH];
////volatile int command_sent;
  //
  // Author:  Zach Hannum
  // Date: Feb 2016
  // Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.YES)
  //===========================================================================
  unsigned int temp;
  char tempchar;
  unsigned int tempUCA = UCA0IV;
  switch(tempUCA){
  case YES: // Vector CLR - no interrupt
    break;
  case TWO: // Vector 2 - RXIFG
    increment = YES;
    temp = fram_rx_ring_wr;
    tempchar = UCA0RXBUF;
    
    //Send back to terminal
    UCA0TXBUF = tempchar;
    
    //Send to IoT
    UCA1TXBUF = tempchar;
  
    FRAM_Char_Rx[temp] = tempchar; // RX -> USB_Char_Rx character
    if (++fram_rx_ring_wr >= (SMALL_RING_SIZE)){
      fram_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
    }
    if(tempchar == '\r'){
      send_iot_command = YES;
      fram_rx_ring_wr = BEGINNING;
      
    }
    
    break;
  case FOUR: // Vector 4 – TXIFG
    
    break;
  default: break;
  }
}
//------------------------------------------------------------------------------
// Iot Interrupt
//------------------------------------------------------------------------------
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void){
    //===========================================================================
  // Function name: USCI_A1_ISR
  //
  // Description: controls IoT interrupts
  //
  // Passed : int MODE
  // Locals: no variables declared
////extern char *display_1;
////extern char *display_2;
////extern char *display_3;
////extern char *display_4;
////extern char display_line_1[ELEVEN];
////extern char display_line_2[ELEVEN];
////extern char display_line_3[ELEVEN];
////extern char display_line_4[ELEVEN];
////volatile char CPU_Char_Rx[SMALL_RING_SIZE];
////volatile char FRAM_Char_Rx[SMALL_RING_SIZE];
////volatile unsigned int fram_rx_ring_wr;
////volatile unsigned int fram_tx_ring_wr;
////volatile unsigned int fram_tx_ring_rd;
////volatile unsigned int fram_rx_ring_rd;
////volatile unsigned int cpu_rx_ring_wr;
////extern int BAUD_MODE;
////extern volatile int increment;
////volatile int command_flag = CLR;
////volatile int command_received = CLR;
////
////volatile int send_iot_command = CLR;
////volatile int reset_iot = CLR;
////char DISASSOCIATION[EIGHT]= "+WIND:41";
////char IPADD[EIGHT] = "WiFi Up:";
////char IP[SIXTEEN];
////volatile int ip_detected;
////volatile char command[MAX_COMMAND_LENGTH];
////volatile int command_sent;
  //
  // Author:  Zach Hannum
  // Date: Feb 2016
  // Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.YES)
  //===========================================================================
  unsigned int temp;
  unsigned int tempUCA = UCA1IV;
  char tempchar;
  switch(tempUCA){
  case CLR: // Vector CLR - no interrupt
    break;
  case TWO: // Vector 2 - RXIFG
    increment = YES;
    temp = cpu_rx_ring_wr;
    tempchar = UCA1RXBUF;
    UCA0TXBUF = tempchar;
    CPU_Char_Rx[temp] = tempchar; // RX -> USB_Char_Rx character
    if (++cpu_rx_ring_wr >= (SMALL_RING_SIZE)){
      cpu_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
    }
    
    
    //Detect Disassociation
    
    if(tempchar == '\r'){
      cpu_rx_ring_wr = BEGINNING;
      for(int i = CLR; i < SMALL_RING_SIZE; i ++){
        int k = CLR;
        if(CPU_Char_Rx[i] == DISASSOCIATION[k]){
          k++;
          if(k == EIGHT){
            reset_iot = YES;
            Wheels_Off();
          }
        }
      }
      
      //Detect BSS Lost
      for(int i = CLR; i <SMALL_RING_SIZE; i ++){
        int k = CLR;
        if(CPU_Char_Rx[i] == BSSLOST[k]){
          k++;
          if(k == BSSLOST_STRING_MAX){
            Wheels_Off();
          }
        }
      }
      
      //Detect IP Address
      
      int j = CLR;
      int k = CLR;
      for(j = CLR; CPU_Char_Rx[j] != '\r'; j++){
        if(CPU_Char_Rx[j] == IPADD[k]){
          k++;
          if(k == IP_HALF){
            ip_detected = YES;
            break;
          }
        }
      }
      
      k = CLR;
      if(ip_detected){
        while(CPU_Char_Rx[++j] != '\r'){
          IP[k] = CPU_Char_Rx[j];
          k++;
        }
        while(k++ < IP_LENGTH){   
          IP[k] = '\0';
        }
      }
      
      //Detect Commands issued from web
      
      j = YES;
      k = CLR;
      if(CPU_Char_Rx[j] == '*'){ //Command sequence detected
        while(CPU_Char_Rx[j++] != '\r'){
          command[k++] = CPU_Char_Rx[j];
        }
        command_sent = YES;
      }
    }
    
    
    
    break;
  case FOUR: // Vector 4 – TXIFG
    break;
  default: break;
    }
  }
         //------------------------------------------------------------------------------
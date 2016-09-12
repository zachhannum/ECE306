//------------------------------------------------------------------------------
// File: ports.c
//  Description: This file initailizes Ports 1,2,3,4, and J on the MSP430 
//               to their appropriate functions, outputs (if applicable),
//               pull-up/down resistors (if applicable), and output/input
//  Zach Hannum
//  Feb 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

void Init_Ports(void){
  Init_Port1();
  Init_Port2();
  Init_Port3(LED);
  Init_Port4();
  Init_PortJ(LED);
}

void Init_Port1(void){
// Init_Port1
// Purpose: Initialize Port 1
//
// Various options for Pin 0
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA0 CCR1 capture: CCI1A input
// 0 1 1 - TA0 CCR1 compare: Out1
// 1 0 0 - External DMA trigger
// 1 0 1 - RTC clock calibration output
// 1 1 X - Analog input A0 - ADC, Comparator_D input CD0, Vref- External applied reference
//
// Various options for Pin 1
// SEL0 SEL1 DIR
// 0 0 I:0 0:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA0 CCR2 capture: CCI2A input,
// 0 1 1 - TA0 CCR2 compare: Out2
// 1 0 0 - TA1 input clock
// 1 0 1 - Comparator_D output
// 1 1 X - Analog input A1 - ADC, Comparator_D input CD1, Input for an external reference voltage to
//the ADC
//
// Various options for Pin 2
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA1 CCR1 capture: CCI1A input
// 0 1 1 - TA1 CCR1 compare: Out1
// 1 0 0 - TA0 input clock
// 1 0 1 - Comparator_D output
// 1 1 X - Analog input A2 - ADC, Comparator_D input CD2
//
// Various options for Pin 3
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA1 CCR2 capture: CCI2A input
// 0 1 1 - TA1 CCR2 compare: Out2
// 1 0 X - Slave transmit enable - eUSCI_B0 SPI mode
// 1 1 X - Analog input A3 - ADC, Comparator_D input CD3
//
// Various options for Pin 4
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB0 CCR1 capture: CCI1A input
// 0 1 1 - TB0 CCR1 compare: Out1
// 1 0 X - Slave transmit enable - eUSCI_A0 SPI mode
// 1 1 X - Analog input A4 - ADC, Comparator_D input CD4
//
// Various options for Pin 5
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB0 CCR2 capture: CCI2A input
// 0 1 1 - TBO CCR2 compare: Out2
// 1 0 X - Clock signal input - eUSCI_A0 SPI slave, Clock signal output - eUSCI_A0 SPI master
// 1 1 X - Analog input A5 - ADC, Comparator_D input CD5
//
// Various options for Pin 6
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB1 CCR1 capture: CCI1A input
// 0 1 1 - TB1 CCR1 compare: Out1
// 1 0 X - *Slave in, master out - eUSCI_B0 SPI mode, I2C data - eUSCI_B0 I2C mode
// 1 1 0 - TA0 CCR0 capture: CCI0A input
// 1 1 1 - TA0 CCR0 compare: Out0
//
// Various options for Pin 7
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB1 CCR2 capture: CCI2A input
// 0 1 1 - TB1 CCR2 compare: Out2 (not available on devices without TB1)
// 1 0 X - Slave out, master in - eUSCI_B0 SPI mode, I2C clock - eUSCI_B0 I2C mode
// 1 1 0 - TA1 CCR0 capture: CCI0A input
// 1 1 1 - TA1 CCR0 compare: Out0
//
// Passed: No variables passed
// Locals: No local variables
// Returned: No values returned
//
// Author: Zach Hannum
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
// Version: 1.0
//-----------------------------------------------------------------------------

  P1SEL0 = CLR_REG;         // P1 Port Pins as I/O
  P1SEL1 = CLR_REG;         // P1 Port Pins as I/O
  P1DIR = CLR_REG;          // P1 Port Pins all set default to inputs
  P1OUT = CLR_REG;          // P1 Port Pins all set default to low
  
  // Port P1.0
  P1SEL0 |= V_DETECT_R;       // Select function 4 
  P1SEL1 |= V_DETECT_R;       // For V_DETECT_R
  
  // Port P1.1
  P1SEL0 |= V_DETECT_L;       // Select function 4
  P1SEL1 |= V_DETECT_L;       // For V_DETECT_L
  
  // Port P1.2
  P1SEL0 &= ~IR_LED;       // Select function 0
  P1SEL1 &= ~IR_LED;       // for IR_LED
  P1OUT  &= ~IR_LED;       // initial value for output: Set to 0
  P1DIR  |= IR_LED;        // direction: Set to Output
  
  // Port P1.3
  P1SEL0 |= V_THUMB;       // Select function 4
  P1SEL1 |= V_THUMB;       // for V_THUMB
  
  // Port P1.4
  P1SEL0 &= ~SPI_CS_LCD;       // Select function 0
  P1SEL1 &= ~SPI_CS_LCD;       // for SPI_CS_LCD
  P1OUT  |= SPI_CS_LCD;        // initial value for output: set to 1
  P1DIR  |= SPI_CS_LCD;        // direction: set to output
  
  // Port P1.5
  P1SEL0 &= ~RESET_LCD;       // Select function 0
  P1SEL1 &= ~RESET_LCD;       // for RESET_LCD
  P1OUT &= ~RESET_LCD;        // initial value for output: set to 0
  P1DIR |= RESET_LCD;         // direction: set to output
  
  // Port P1.6
  P1SEL0 &= ~SPI_SIMO;       // Select function 3
  P1SEL1 |= SPI_SIMO;        // for SPI_SIMO
  P1DIR  |= SPI_SIMO;        // direction: set to output
  
  // Port P1.7
  P1SEL0 &= ~SPI_SOMI;       // Select function 3
  P1SEL1 |= SPI_SOMI;        // for SPI_SOMI 
  P1OUT &= ~SPI_SOMI;        // Set to pull-down 
  P1DIR  &= ~SPI_SOMI;       // direction: set to Input
  P1REN |= SPI_SOMI;         // enable pull-up resistor
  
  //------------------------------------------------------------------------------
}

void Init_Port2(void){
// Init_Port2
// Purpose: Initialize Port 2
//
// Various options for Pin 0
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
//
// Various options for Pin 1
// SEL0 SEL1 DIR
// 0 0 I:0 0:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
//
// Various options for Pin 2
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB2.CCI2A
// 0 1 1 - TB2.2
// 1 0 0 - UCB0CLK
// 1 0 1 - UCB0CLK
// 1 1 0 - TB1.CCI0A
// 1 1 1 - TB1.0
//
// Various options for Pin 3
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
//
// Various options for Pin 4
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
//
// Various options for Pin 5
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
//
// Various options for Pin 6
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - General-purpose digital I/O with port interrupt and wake up from LPMx.5
//
// Various options for Pin 7
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
//
// Passed: No variables passed
// Locals: No local variables
// Returned: No values returned
//
// Author: Zach Hannum
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
// Version: 1.0
//-----------------------------------------------------------------------------
  P2SEL0 = CLR_REG;         // P2 Port Pins as I/O
  P2SEL1 = CLR_REG;         // P2 Port Pins as I/O
  P2DIR = CLR_REG;          // P2 Port Pins all set default to inputs
  P2OUT = CLR_REG;          // P2 Port Pins all set default to low
  
  // Port P2.0
  P2SEL0 &= ~USB_TXD;      // Select function 3
  P2SEL1 |= USB_TXD;       // for USB_TXD
  
  // Port P2.1
  P2SEL0 &= ~USB_RXD;       // Select function 3
  P2SEL1 |= USB_RXD;        // for USB_RXD
  P2OUT |= USB_RXD;
  P2REN |= USB_RXD;
  
  // Port P2.2
  P2SEL0 &= ~SPI_SCK;      // Select function 3
  P2SEL1 |= SPI_SCK;       // for SPI_SCK
  P2OUT  |= SPI_SCK;       // Initial value set to 1
  P2DIR  |= SPI_SCK;       // Set to output
  
  // Port P2.3
  P2SEL0 &= ~UNKNOWNPORT2PIN3;       // Select function 0
  P2SEL1 &= ~UNKNOWNPORT2PIN3;       // for Unknown pin
  P2OUT  &= ~UNKNOWNPORT2PIN3;       // set to 0
  P2DIR  &= ~UNKNOWNPORT2PIN3;       // set to input
  P2REN  &= ~UNKNOWNPORT2PIN3;       // disable resistor
  
  // Port P2.4
  P2SEL0 &= ~UNKNOWNPORT2PIN4;       // select function 0
  P2SEL1 &= ~UNKNOWNPORT2PIN4;       // for Unknown pin
  P2OUT  &= ~UNKNOWNPORT2PIN4;       // set to 0
  P2DIR  &= ~UNKNOWNPORT2PIN4;       // set to input
  P2REN  &= ~UNKNOWNPORT2PIN4;       // disable resistor   
  
  // Port P2.5
  P2SEL0 &= ~CPU_TXD;       // Select function 3
  P2SEL1 |= CPU_TXD;        // for CPU_TXD
  
  // Port P2.6
  P2SEL0 &= ~CPU_RXD;       // Select function 3
  P2SEL1 |= CPU_RXD;      // for CPU_RXD
  P2OUT |= CPU_RXD;
  P2REN |= CPU_RXD;
  
  // Port P2.7
  P2SEL0 &= ~UNKNOWNPORT2PIN7;       // Select function 0
  P2SEL1 &= ~UNKNOWNPORT2PIN7;       // for Unknown pin
  P2OUT  &= ~UNKNOWNPORT2PIN7;       // set to 0
  P2DIR  &= ~UNKNOWNPORT2PIN7;       // set to input
  P2REN  &= ~UNKNOWNPORT2PIN7;       // disable resistor
  
  //------------------------------------------------------------------------------
}

void Init_Port3(char TOGGLE){
// Init_Port3
// Purpose: Initialize Port 3
//
// Various options for Pin 0
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
//
// Various options for Pin 1
// SEL0 SEL1 DIR
// 0 0 I:0 0:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
//
// Various options for Pin 2
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
//
// Various options for Pin 3
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 1 1 X - A15, CD15 
//
// Various options for Pin 4
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB1.CCI1B
// 0 1 1 - TB1.1 
// 1 1 0 - TB2CLK
// 1 1 1 - SMCLK
//
// Various options for Pin 5
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB1.CCI2B
// 0 1 1 - TB1.2
// 1 1 1 - CDOUT
//
// Various options for Pin 6
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB2.CCI1B
// 0 1 1 - TB2.1
// 1 1 0 - TB1CLK
//
// Various options for Pin 7
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB2.CCI2B
// 0 1 1 - TB2.2
//
// Passed: No variables passed
// Locals: No local variables
// Returned: No values returned
//
// Author: Zach Hannum
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
// Version: 1.0
//-----------------------------------------------------------------------------
  P3SEL0 = CLR_REG;         // P3 Port Pins as I/O
  P3SEL1 = CLR_REG;         // P3 Port Pins as I/O
  P3DIR = CLR_REG;          // P3 Port Pins all set default to inputs
  P3OUT = CLR_REG;          // P3 Port Pins all set default to low
  
  // Port P3.0
  P3SEL0 &= ~x;       // Select function 0
  P3SEL1 &= ~x;       // for x
  P3OUT  &= ~x;       // set pull - down
  P3DIR &= ~x;        // direction: set input
  P3REN |= x;         // enable resistor
  
  // Port P3.1
  P3SEL0 &= ~y;       // Select function 0
  P3SEL1 &= ~y;       // for y
  P3OUT  &= ~y;       // set pull - down
  P3DIR &= ~y;        // direction: set input
  P3REN |= y;         // enable resistor
  
  // Port P3.2
  P3SEL0 &= ~z;       // Select function 0
  P3SEL1 &= ~z;       // for z
  P3OUT  &= ~z;       // set pull - down
  P3DIR &= ~z;        // direction: set input
  P3REN |= z;         // enable resistor
  
  // Port P3.3
  P3SEL0 &= ~LCD_BACKLITE;      // Select function 0
  P3SEL1 &= ~LCD_BACKLITE;      // for 3
  P3OUT  &= ~LCD_BACKLITE;      // initial value for output: set to 0
  P3DIR |= LCD_BACKLITE ;       // direction: set output
  
  // Port P3.4
  P3SEL0 |= R_FORWARD;       // Select function 1 (TB1.1)
  P3SEL1 &= ~R_FORWARD;       // for R_FORWARD
  P3OUT  &= ~R_FORWARD;       // initial value for output: set to 0
  P3DIR |= R_FORWARD ;        // direction: set output
  
  // Port P3.5
  P3SEL0 |= R_REVERSE;       // Select function 1 (TB1.2)
  P3SEL1 &= ~R_REVERSE;       // for R_REVERSE
  P3OUT  &= ~R_REVERSE;       // initial value for output: set to 0
  P3DIR |= R_REVERSE ;        // direction: set output
  
  // Port P3.6
  P3SEL0 |= L_FORWARD;       // Select function 1 (TB2.1)
  P3SEL1 &= ~L_FORWARD;       // for L_FORWARD
  P3OUT  &= ~L_FORWARD;       // initial value for output: set to 0
  P3DIR |= L_FORWARD ;        // direction: set output
  
  // Port P3.7
  P3SEL0 |= L_REVERSE;       // Select function 1 (TB2.2)
  P3SEL1 &= ~L_REVERSE;       // for L_REVERSE
  P3OUT  &= ~L_REVERSE;       // initial value for output: set to 0
  P3DIR |= L_REVERSE ;        // direction: set output
  //------------------------------------------------------------------------------
}

void Init_Port4(void){
// Init_Port4
// Purpose: Initialize Port 4
//
// Various options for Pin 0
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB2.CCI0B
// 0 1 1 - TB2.0
//
// Various options for Pin 1
// SEL0 SEL1 DIR
// 0 0 I:0 0:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
//
// Passed: No variables passed
// Locals: No local variables
// Returned: No values returned
//
// Author: Zach Hannum
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
// Version: 1.0
//-----------------------------------------------------------------------------
  P4SEL0 = CLR_REG;         // P4 Port Pins as I/O
  P4SEL1 = CLR_REG;         // P4 Port Pins as I/O
  P4DIR = CLR_REG;          // P4 Port Pins all set default to inputs
  P4OUT = CLR_REG;          // P4 Port Pins all set default to low
  
  // Port P4.0
  P4SEL0 &= ~SW1 ;       // Select function 0
  P4SEL1 &= ~SW1;        // for SW1
  P4OUT  |= SW1 ;        // set pull - up
  P4DIR  &= ~SW1;        // direction: set input
  P4REN  |= SW1;         // enable resistor

  
  // Port P4.1
  P4SEL0 &= ~SW2 ;       // Select function 0
  P4SEL1 &= ~SW2;        // for SW2
  P4OUT  |= SW2;         // set pull - up
  P4DIR  &= ~SW2;        // direction: set input
  P4REN  |= SW2;         // enable resistor

  //------------------------------------------------------------------------------
}

void Init_PortJ(char TOGGLE){
// Init_PortJ
// Purpose: Initialize Port J
//
// Various options for Pin 0
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// X X X - TDO
// 0 1 0 - TB0OUTH
// 0 1 1 - SMCLK
// 1 1 X - CD6
//
// Various options for Pin 1
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// X X X - TDI/TCLK
// 0 1 0 - TB1OUTH
// 0 1 1 - MCLK
// 1 1 X - CD7
//
// Various options for Pin 2
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// X X X - TMS
// 0 1 0 - TB2OUTH
// 0 1 1 - ACLK
// 1 1 X - CD8
//
// Various options for Pin 3
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// X X X - TCK
// 1 1 X - CD9
//
// Passed: No variables passed
// Locals: No local variables
// Returned: No values returned
//
// Author: Zach Hannum
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
// Version: 1.0
//-----------------------------------------------------------------------------
  PJSEL0 = CLR_REG;         // PJ Port Pins as I/O
  PJSEL1 = CLR_REG;         // PJ Port Pins as I/O
  PJDIR = CLR_REG;          // PJ Port Pins all set default to inputs
  PJOUT = CLR_REG;          // PJ Port Pins all set default to low
  
  // Port PJ.0
  PJSEL0 &= ~IOT_WAKEUP;       // Select function 0
  PJSEL1 &= ~IOT_WAKEUP;       // for IOT_WAKEUP
  PJDIR |= IOT_WAKEUP;         // direction: set output
  
  // Port PJ.1
  PJSEL0 &= ~IOT_FACTORY;       // Select function 0
  PJSEL1 &= ~IOT_FACTORY;       // for IOT_FACTORY
  PJDIR |= IOT_FACTORY;         // direction: set output
  
  // Port PJ.2
  PJSEL0 &= ~IOT_STA_MINIAP;       // Select function 0
  PJSEL1 &= ~IOT_STA_MINIAP;       // for IOT_STA_MINIAP
  PJDIR |= IOT_STA_MINIAP;         // direction: set output
  PJOUT |= IOT_STA_MINIAP;         // Set initial high
  
  // Port PJ.3
  PJSEL0 &= ~IOT_RESET;       // Select function 0
  PJSEL1 &= ~IOT_RESET;       // for IOT_RESET
  PJDIR |= IOT_RESET;         // direction: set output
  
  //------------------------------------------------------------------------------  
}
//------------------------------------------------------------------------------
//  File: macros.h
//  Description: This file contains macro definitions for all ports and pins, etc.
//               to be initialized to ports 1,2,3,4, and J.
//
//  Zach Hannum
//  Feb 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

// Required defines
// In the event the universe no longer exists, this bit will reset
#define ALWAYS                 1
#define CNTL_STATE_INDEX       3 // Control States
#define CNTL_STATE_INDEX       3

#define YES 1

#define LED            0 //Set Ports 3.4-3.7 and Ports J.0-J.3 to LED use
#define CONTROL        1 //Set Ports 3.4-3.7 and Ports J.0-J.3 to CONTROL use
// LCD
#define LCD_HOME_L1	        0x80
#define LCD_HOME_L2         	0xA0
#define LCD_HOME_L3         	0xC0
#define LCD_HOME_L4         	0xE0

#define CLR_REG                 0x00
#define CLR 0

#define ONEMSEC 100

#define DISPLAY_SIZE 9

#define RESET_STRING_MAX 9
#define IP_LINE_MAX 8
#define DUTY40R 425
#define DUTY40L 400
#define DUTY20  200

#define SAVE_STRING_MAX 4
#define BAUD_STRING_MAX 29
#define SSID_STRING_MAX 22
#define PASS_STRING_MAX 36
#define PRIV_STRING_MAX 26
#define NET_STRING_MAX 21
#define BSSLOST_STRING_MAX 9


//MOTORS
#define WHEEL_PERIOD            1000
#define OFF                        0
#define RIGHT_SPEED              8250
#define LEFT_SPEED               800
#define SPIN_SPEED              1000

#define HALFMSEC 50
#define TWOSECONDS 2000
#define TENTHMSEC 10
#define HALFSECOND 500

#define INT_JUMP 4

//ADC
#define DEFAULT_WHITE_VALUE 50
#define DEFAULT_BLACK_VALUE 800

//Modes
#define DISPLAYMODE 0
#define ENGAGEMODE  1
#define DEFAULT     3
#define DETECT_RIGHT 0x01
#define DETECT_LEFT  0x00
#define DETECT_THUMB 0x03

#define BEGINNING (0)
#define SMALL_RING_SIZE (32)
#define LARGE_RING_SIZE  32

#define LOW_BAUD 0
#define HIGH_BAUD 1
#define LOW_BAUD_MCTLW 0x4911
#define LOW_BAUD_BRW 52
#define HIGH_BAUD_MCTLW 0x5551
#define HIGH_BAUD_BRW 4


//Menu
#define MENU_ITEM_1 1
#define MENU_ITEM_2 2
#define MENU_ITEM_3 3

//Commands
#define FORWARD  0
#define BACKWARD 1
#define RIGHT    3
#define LEFT     4
#define MAX_COMMAND_LENGTH 100

#define IP_LENGTH 16
#define IP_HALF 8

// Timers
#define TA0CCR0_INTERVAL 233 // 1 ms
#define TA1CCR0_INTERVAL 62500 //250 ms
#define DEBOUNCE_COUNT 10

// Numbers
#define ZERO               0
#define THREE              3
#define FOUR               4
#define EIGHT              8
#define TEN               10
#define ELEVEN            11
#define TWELVE            12
#define FOURTEEN          14
#define FIFTY             50
#define TWO                2
#define NINETYNINE        99
#define ONEHUNDRED       100
#define TWOHUNDRED       200
#define TWOHUNDREDFIFTY  250
#define SIXSEVENFIVE     675
#define SEVENHUNDRED     700
#define FOURHUNDRED      400
#define SEVENTYTHREE      73
#define ONE                1
#define SIX                6
#define SIXTEEN           16
#define FIVE               5
#define FORTYNINE         49
#define TWENTY            20
#define SEVEN              7
#define EIGHTEEN          18
#define NINE               9
#define ONETHOUSAND     1000
#define FIFTEENHUNDRED  1500
#define SEVENTYFIVE       75 
#define ONEHUNDREDFIFTY  150
#define TIMER_MAX       10000

#define ONE_SEC    1000
#define TWO_SECS   2000
#define FIVE_SECS  5000
#define THREE_SECS 3000
#define FOUR_SECS  4000

#define HEX_CONVERT 0x30


//Port 1
#define V_DETECT_R   0x01  // 
#define V_DETECT_L   0x02  //
#define IR_LED       0x04  //
#define V_THUMB      0x08  //
#define SPI_CS_LCD   0x10  // LCD Chip Select
#define RESET_LCD    0x20  // LCD Reset
#define SPI_SIMO     0x40  // SPI mode - slave in/master out of USCI_B0
#define SPI_SOMI     0x80  // SPI mode - slave out/master in of USCI_B0 

// Port 2
#define USB_TXD           0x01 // 
#define USB_RXD           0x02 // 
#define SPI_SCK           0x04 // 
#define UNKNOWNPORT2PIN3  0x08 //
#define UNKNOWNPORT2PIN4  0x10 //
#define CPU_RXD           0x20 //
#define CPU_TXD           0x40 //
#define UNKNOWNPORT2PIN7  0x80 //

//Port 3
#define x             0x01 //
#define y             0x02 //
#define z             0x04 //
#define LCD_BACKLITE  0x08 //
#define R_FORWARD     0x10 //
#define R_REVERSE     0x20 //
#define L_FORWARD     0x40 //
#define L_REVERSE     0x80 //

//Port 4
#define SW1     0x01 //Switch 1
#define SW2     0x02 //Switch 2

//Port J
#define IOT_WAKEUP        0x01
#define IOT_FACTORY       0x02
#define IOT_STA_MINIAP    0x04
#define IOT_RESET         0x08


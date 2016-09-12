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
// extern char display_line_1[ELEVEN];             
// extern char display_line_2[ELEVEN];            
// extern char display_line_3[ELEVEN];             
// extern char display_line_4[ELEVEN];             
// extern char *display_1;                     // Line 1 of LCD Display 
// extern char *display_2;                     // Line 2 of LCD Display  
// extern char *display_3;                     // Line 3 of LCD Display  
// extern char *display_4;                     // Line INT_JUMP of LCD Display 
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
#include "stdio.h"


// Global Variables
volatile unsigned char control_state[CNTL_STATE_INDEX];
volatile unsigned int Time_Sequence;
char led_smclk;
volatile char one_time;
volatile unsigned int five_msec_count;
extern char display_line_1[ELEVEN];
extern char display_line_2[ELEVEN];
extern char display_line_3[ELEVEN];
extern char display_line_4[ELEVEN];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
char posL1;
char posL2;
char posL3;
char posL4;
char size_count;
char big;
extern int mode;
extern int count;
int BAUD_MODE = LOW_BAUD;
volatile int increment;
extern volatile int command_received;

extern volatile int send_iot_command;
extern volatile char FRAM_Char_Rx[SMALL_RING_SIZE];
char RESET_STRING[NINE] = "AT+CFUN=1";
extern volatile int reset_iot;
extern char IP[IP_LENGTH];
extern volatile int ip_detected;
int command_time;
extern volatile char command[ONEMSEC];
extern volatile int command_sent;
int j = CLR;
extern volatile int black_line_detect;

int rightForwardDuty;
int rightReverseDuty;
int leftForwardDuty;
int leftReverseDuty;

extern volatile unsigned long int time;
extern volatile int countTime;
extern volatile int minuteTime;
volatile int controls_enabled = CLR;

volatile int display_adc = CLR;
extern volatile int calibrate_white;
extern volatile int calibrate_black;

extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int ADC_Left_Detector;

char count_array[10];

void main(void){
  //------------------------------------------------------------------------------
  // Main Program
  // This is the main routine for the program. Execution of code starts here.
  // The operating system is Back Ground Fore Ground.
  // 
  // Globals 
  //---------
  // volatile unsigned char control_state[CNTL_STATE_INDEX]; //
  // volatile unsigned int Time_Sequence;
  // char led_smclk;
  // volatile char one_time;
  // volatile unsigned int five_msec_count;
  // extern char display_line_1[ELEVEN];             
  // extern char display_line_2[ELEVEN];            
  // extern char display_line_3[ELEVEN];             
  // extern char display_line_4[ELEVEN];             
  // extern char *display_1;                     // Line 1 of LCD Display 
  // extern char *display_2;                     // Line 2 of LCD Display  
  // extern char *display_3;                     // Line 3 of LCD Display  
  // extern char *display_4;                     // Line INT_JUMP of LCD Display 
  // char posL1;
  // char posL2;
  // char posL3;
  // char posL4;
  // char size_count;
  // char big;
  //------------------------------------------------------------------------------
  Init_Ports();                             // Initialize Ports
  Init_Clocks();                            // Initialize Clock System 
  Init_Conditions();
  Time_Sequence = CLR;                        // 
  Init_Timers();                            // Initialize Timers
  Init_LCD();                               // Initialize LCD
  Init_ADC();
  Init_Serial_UCA0(LOW_BAUD);
  Init_Serial_UCA1(HIGH_BAUD);
  mode = DEFAULT;

  
  
  
  display_1 = "ECE 306";
  posL1 = CLR;
  display_2 = "Project 8";
  posL2 = CLR;
  display_3 = "";
  posL3 = CLR;
  display_4 = "ZHANNUM";
  posL4 = CLR;
  Display_Process();
  sleep(ONE_SEC);
  PJOUT |= IOT_RESET;
  display_1 = "     ";
  display_2 = "    ";
  posL4 = CLR;
  display_4 = " ";
  
  //P1OUT |= IR_LED;
  //------------------------------------------------------------------------------
  // Begining of the "While" Operating System
  //------------------------------------------------------------------------------
  while(ALWAYS) {  
    Switches_Process();
    
    if(reset_iot){
      for(int i = CLR; i < RESET_STRING_MAX; i++){
        display_4 = "resetting...";
        UCA1TXBUF = RESET_STRING[i];
        sleep(TENTHMSEC);
      }
      UCA1TXBUF = '\r';
      sleep(ONEMSEC);
      PJOUT = ~IOT_RESET;
      sleep(ONEMSEC);
      PJOUT |= IOT_RESET;
      display_4 = " ";
      reset_iot = CLR;
      
    }
    
    if(ip_detected){
      char ip_line_1 [DISPLAY_SIZE];
      char ip_line_2 [DISPLAY_SIZE];
      for ( int i = CLR; i < IP_LINE_MAX; i++){
        ip_line_1[i] = IP[i];
      }
      
      for( int i = CLR; i < IP_LINE_MAX; i ++){
        ip_line_2[i] = IP[i+IP_LINE_MAX];
      }
      ip_line_1[IP_LINE_MAX] = '\0';
      ip_line_2[IP_LINE_MAX] = '\0';
      display_1 = ip_line_1;
      display_2 = ip_line_2;
      ip_detected = CLR;
      
      sleep(2000);
      
      display_1 = "";
      display_2 = "";
      
      
    }
    
    if(command_sent){
      
      j = CLR;
      while(command[j] != '\r'){
        switch (command[j]){
        case 'R':
          if(controls_enabled){
            countTime = YES;
            toInt();
            rightForwardDuty = command_time;
            if(rightForwardDuty > 0){
              if(rightForwardDuty > 900)
                rightForwardDuty = 0;
              Right_Wheel_Forward_On(rightForwardDuty);
            }
            toInt();
            rightReverseDuty = command_time;
            if(rightReverseDuty > 0){
              if(rightReverseDuty > 900)
                rightReverseDuty = 0;
              Right_Wheel_Reverse_On(rightReverseDuty);
            }
            if((rightForwardDuty == 0) && (rightReverseDuty == 0))
              Right_Wheel_Off();
          }
          else{
            toInt();
            toInt();
            Right_Wheel_Off();
          }
          command_sent = CLR;
          break;
        case 'L':
          if(controls_enabled){
            countTime = YES;
            toInt();
            leftForwardDuty = command_time;
            if(leftForwardDuty > 0){
              if(leftForwardDuty > 900)
                leftForwardDuty = 0;
              Left_Wheel_Forward_On(leftForwardDuty);
            }
            
            toInt();
            leftReverseDuty = command_time;
            if(leftReverseDuty > 0){
              if(leftReverseDuty > 900)
                leftReverseDuty = 0;
              Left_Wheel_Reverse_On(leftReverseDuty);
            }
            if((leftForwardDuty == 0) && (leftReverseDuty == 0))
              Left_Wheel_Off();
          }
          else{
            toInt();
            toInt();
            Left_Wheel_Off();
          }
          command_sent = CLR;
          break;
        case 'C':
          toInt();
          display_1 = "Connected!";
          display_2 = "";
          sleep(500);
          command_sent = CLR;
          break;
        case 'S':
          toInt();
          display_1 = "Stop";
          display_2 = "";
          Wheels_Off();
          P1OUT &= ~IR_LED; 
          black_line_detect = CLR;
          display_adc = CLR;
          command_sent = CLR;
          countTime = CLR;
          time = 0;
          break;
        case 'F':
          toInt();
          display_1 = "Following"; 
          display_2 =   "Line...";
          P1OUT |= IR_LED;
          black_line_detect = YES;
          controls_enabled = CLR;
          command_sent = CLR;
          break;
        case 'E':
          toInt();
          if(command_time){
            display_1 = "Joystick";
            display_2 = "Enabled";
            controls_enabled = YES;
            black_line_detect = CLR;
            Wheels_Off();
           
          }
          else{
            display_1 = "Joystick";
            display_2 = "Disabled";
            Wheels_Off();
            controls_enabled = CLR;
        
          }
          command_sent = CLR;
          break;
        case 'A':
          toInt();
          display_adc = YES;
          P1OUT |= IR_LED;
          command_sent = CLR;
          break;
        case 'B':
          toInt();
          P1OUT |= IR_LED;
          display_1 = "Calibrate";
          display_2 = "Black...";
          sleep(500);
          display_1 = "";
          display_2 = "B";
          calibrate_black = YES;
          command_sent = CLR;
          break;
        case 'W':
          toInt();
          P1OUT |= IR_LED;
          display_1 = "Calibrate";
          display_2 = "White...";
          sleep(500);
          display_1 = "";
          display_2 = "";
          calibrate_white = YES;
          command_sent = CLR;
          break;
          
        }
        
  
        
      }
    }
    
    if(black_line_detect){
      ADC_Process();
      Right_Wheel_Forward_On(525);
      Left_Wheel_Forward_On(500);
      
      while(ADC_Left_Detector < 400){
        Left_Wheel_Forward_On(400);
        Right_Wheel_Reverse_On(400);
        if(command[0] == 'E')
          break;
        if(command[0] == 'S')
          break;
        ADC_Process();
      }
      
      while(ADC_Right_Detector < 400){
        Right_Wheel_Forward_On(400);
        Left_Wheel_Reverse_On(400);
        if(command[0] == 'E')
          break;
        if(command[0] == 'S')
          break;
        ADC_Process();
      }
    }

      ADC_Process();
      
   
    
    
    
    
    if(countTime){
      counter();
    }
  }
}
//------------------------------------------------------------------------------

void toInt(void){
  j++;
  command_time = CLR;
  for(int i = j; i < j + INT_JUMP; i++){
    command_time = command_time*TEN + (command[i] - '0');
  }
  j = j + INT_JUMP;
}

void counter(void){
  HEXtoBCD(time);
  display_4 = count_array;
  
}

void HEXtoBCD(unsigned long int hex_value){
  int value;
  count_array[ZERO] = '0';
  value = 0;
  TA1CCR0 = CLR;
  
  //10 millions place
  value = CLR;
  if(hex_value < 10000000) count_array[0] = '0';
  while (hex_value > 9999999){
    hex_value = hex_value - 10000000;
    value = value + ONE;
    count_array[ZERO] = 0x30 + value;
  }
  
  //1 millions place
  value = CLR;
  if(hex_value < 1000000) count_array[1] = '0';
  while (hex_value > 999999){
    hex_value = hex_value - 1000000;
    value = value + ONE;
    count_array[1] = 0x30 + value;
  }
  
   //100 thousands place
  value = CLR;
  if(hex_value < 100000) count_array[2] = '0';
  while (hex_value > 99999){
    hex_value = hex_value - 100000;
    value = value + ONE;
    count_array[2] = 0x30 + value;
  }
  
   //10 thousands place
  value = CLR;
  if(hex_value < 10000) count_array[3] = '0';
  while (hex_value > 9999){
    hex_value = hex_value - 10000;
    value = value + ONE;
    count_array[3] = 0x30 + value;
  }
  
  //1 thousands place
  value = CLR;
  if(hex_value < ONETHOUSAND) count_array[4] = '0';
  while (hex_value > 999){
    hex_value = hex_value - ONETHOUSAND;
    value = value + ONE;
    count_array[4] = 0x30 + value;
  }
  
  //100s place
  value = ZERO;
  if(hex_value < 100) count_array[5] = '0';
  while(hex_value > 99){
    hex_value = hex_value - 100;
    value = value + ONE;
    count_array[5] = 0x30 + value;
  }
  
  //tens place
  value=ZERO;
  if(hex_value < 10) count_array[6] = '0';
  while (hex_value > 9){
    hex_value = hex_value - 10;
    value = value + ONE;
    count_array[6] = 0x30 + value;
  }
  
  //1's place
  count_array[7] = 0x30 + hex_value;
}




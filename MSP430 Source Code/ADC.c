//------------------------------------------------------------------------------
//  File: ADC.c
//  Description: This file initializes 
//
//
//  Zach Hannum
//  Feb 2016
//  Built with IAR Embedded Workbench Version: V7.3.ONE.3987 (SIX.40.ONE)
//
// Globals
// --------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

volatile unsigned int ADC_Right_Detector;
volatile unsigned int ADC_Left_Detector;
volatile unsigned int ADC_Thumb;
int current_ADC_channel;
volatile int black_line_detected = ZERO;
extern volatile int do_not_detect_black_line;
volatile int black_line_detect = CLR;

extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
char adc_char[FOUR];
char r_adc_char[8] = "R: ";
char l_adc_char[8] = "L: ";
char v_adc_char[FIVE];

volatile int white_value = 50;
volatile int black_value = 800;
int threshold;

volatile int calibrate_white = CLR;
volatile int calibrate_black = CLR;

extern volatile int display_adc;
volatile int adc_time = ZERO;
volatile int count_adc_time = CLR;

int try_back = CLR;
int try_forward = CLR;
int all_stop = CLR;



void Init_ADC(void){
  //------------------------------------------------------------------------------
  // Initializations Configurations
  //
  // Globals
  // --------
  //----------------------------------------------------------------------------
  ADC10CTL0 = CLR_REG; // Clear ADC10CTL0
  ADC10CTL0 |= ADC10SHT_2; // 16 ADC clocks
  ADC10CTL0 &= ~ADC10MSC; // Single Sequence
  ADC10CTL0 |= ADC10ON; // ADC ON - Core Enabled
  ADC10CTL1 = CLR_REG; // Clear ADC10CTL1
  ADC10CTL1 |= ADC10SHS_0; // ADC10SC bit
  ADC10CTL1 |= ADC10SHP; // SAMPCON signal sourced from sampling timer
  ADC10CTL1 &= ~ADC10ISSH; // The sample-input signal is not inverted.
  ADC10CTL1 |= ADC10DIV_0; // ADC10_B clock divider – Divide by ONE.
  ADC10CTL1 |= ADC10SSEL_0; // MODCLK
  ADC10CTL1 |= ADC10CONSEQ_0; // Single-channel, single-conversion
  ADC10CTL2 = CLR_REG; // Clear ADC10CTL2
  ADC10CTL2 |= ADC10DIV_0; // Pre-divide by ONE
  ADC10CTL2 |= ADC10RES; // TEN-bit resolution
  ADC10CTL2 &= ~ADC10DF; // Binary unsigned
  ADC10CTL2 &= ~ADC10SR; // supports up to approximately 200 ksps
  ADC10MCTL0 = CLR_REG; // Clear ADC10MCTL0
  ADC10MCTL0 |= ADC10SREF_0; // V(R+) = AVCC and V(R-) = AVSS
  ADC10MCTL0 |= ADC10INCH_3; // Channel A3 Thumb Wheel
  ADC10IE |= ADC10IE0; // Enable ADC conversion complete interrupt
}

//------------------------------------------------------------------------------
// ADC10 interrupt service routine
// ADC_Right_Detector; // A00 ADC10INCH_0 - P1.ZERO
// ADC_Left_Detector; // A01 ADC10INCH_1 - P1.ONE
// ADC_Thumb; // A03 ADC10INCH_3 - P1.3
// ADC_Temp; // A10 ADC10INCH_10 – Temperature REF module
// ADC_Bat; // A11 ADC10INCH_11 - Internal
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){
  switch(__even_in_range(ADC10IV,TWELVE)) {
  case ZERO: break; // No interrupt
  case TWO: break; // conversion result overflow
  case FOUR: break; // conversion time overflow
  case SIX: break; // ADC10HI
  case EIGHT: break; // ADC10LO
  case TEN: break; // ADC10IN
  case TWELVE:
    ADC10CTL0 &= ~ADC10ENC;
    switch (ADC10MCTL0){
    case DETECT_LEFT:
      ADC10MCTL0 = ADC10INCH_1;
      ADC_Left_Detector = ADC10MEM0; //Channel A0
      break;
    case DETECT_RIGHT:
      ADC10MCTL0 = ADC10INCH_3;
      ADC_Right_Detector = ADC10MEM0; // Channel A1
      break;
    case DETECT_THUMB:
      ADC10MCTL0 = ADC10INCH_0;
      ADC_Thumb = ADC10MEM0; // Channel A3
      break;
    default:
      break;
    }
    ADC10CTL0 |= ADC10ENC;
    // ADC10CTL0 | =  //start next sample
    
    
    
  default: break;
  }
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void ADC_Process(void){
  
 // int right_edge_detected = CLR;
 // int left_edge_detected = CLR;
  
  
  
//  if(calibrate_white){
//    int tempLeft = ADC_Left_Detector;
//    int tempRight = ADC_Right_Detector;
//    white_value = (tempRight + tempLeft) / 2;
//    calibrate_white = CLR;
//  }
//  
//  if(calibrate_black){
//    int tempLeft = ADC_Left_Detector;
//    int tempRight = ADC_Right_Detector;
//    black_value = (tempRight + tempLeft) /2;
//    calibrate_black = CLR;
//  }
  
  int tempBlack = black_value;
  int tempWhite = white_value;
  threshold = 400;
 
  while (ADC10CTL1 & BUSY); // Wait if ADC10 core is active
  ADC10CTL0 |= ADC10ENC + ADC10SC; // Sampling and conversion start
   
  
  if(display_adc){
    HEXtoBCD_l(ADC_Left_Detector);
    HEXtoBCD_r(ADC_Right_Detector);
    display_1 = l_adc_char;
    display_2 = r_adc_char;
  }

   
  
  if(black_line_detect){
    
   
    /*  int tempLeft = ADC_Left_Detector;
    int tempRight = ADC_Right_Detector;
    if(tempLeft < threshold){
      left_edge_detected = YES;
    }
    if(tempRight < threshold){
      right_edge_detected = YES;
    }
    
    if(left_edge_detected && right_edge_detected){
//      count_adc_time = YES;
//      if(!all_stop){
//      if(try_back){
//        Right_Wheel_Reverse_On(500);
//        Left_Wheel_Reverse_On(450);
//        if(adc_time == 300){
//          adc_time = ZERO;
//          try_forward = YES;
//          try_back = CLR;
//        }
//      }
//      else if (try_forward){
//        Right_Wheel_Forward_On(500);
//        Left_Wheel_Forward_On(450);
//        if(adc_time == 600){
//          adc_time = ZERO;
//          try_forward =CLR;
//          all_stop = YES;
//          Wheels_Off();
//        }
//        
//      }
//      else
//        try_back = YES;
//      }
      Wheels_Off();
    }
    
    if(left_edge_detected && (right_edge_detected - 1)){
      Wheels_Off();
      sleep(100);
      
      Left_Wheel_Reverse_On(350);
      Right_Wheel_Reverse_On(400);
      sleep(150);
      Wheels_Off();
      sleep(100);
      Right_Wheel_Reverse_On(400);
      Left_Wheel_Forward_On(500);
      sleep(150);
      Right_Wheel_Forward_On(350);
      Left_Wheel_Forward_On(320);
      sleep(150);
      Wheels_Off();
    }
    else if(right_edge_detected && (left_edge_detected - 1)){
      Wheels_Off();
      sleep(100);
      Left_Wheel_Reverse_On(350);
      Right_Wheel_Reverse_On(400);
      sleep(150);
      Wheels_Off();
      sleep(100);
      Left_Wheel_Reverse_On(400);
      Right_Wheel_Forward_On(500);
      sleep(150);
      Right_Wheel_Forward_On(350);
      Left_Wheel_Forward_On(320);
      sleep(150);
      Wheels_Off();
    }
    else if ((right_edge_detected -1) && (left_edge_detected - 1)) {
      Right_Wheel_Forward_On(350);
      Left_Wheel_Forward_On(320);
      
      
    } */
    
    
  }
}
//------------------------------------------------------------------------------

void HEXtoBCD_l(int hex_value){
  int value;
  l_adc_char[3] = '0';
  if (hex_value > ONETHOUSAND){
    hex_value = hex_value - ONETHOUSAND;
    l_adc_char[3] = '1';
  }
  
  value = ZERO;
  if(hex_value < 100) l_adc_char[4] = '0';
  while(hex_value > 99){
    hex_value = hex_value - 100;
    value = value + 1;
    l_adc_char[4] = 0x30 + value;
  }
  
  value=ZERO;
  while (hex_value > 9){
    hex_value = hex_value - 10;
    value = value + 1;
    l_adc_char[5] = 0x30 + value;
  }
  l_adc_char[6] = 0x30 + hex_value;
}

void HEXtoBCD_r(int hex_value){
  int value;
  r_adc_char[3] = '0';
  if (hex_value > ONETHOUSAND){
    hex_value = hex_value - ONETHOUSAND;
    r_adc_char[3] = '1';
  }
  
  value = ZERO;
  if(hex_value < 100) r_adc_char[4] = '0';
  while(hex_value > 99){
    hex_value = hex_value - 100;
    value = value + 1;
    r_adc_char[4] = 0x30 + value;
  }
  
  value=ZERO;
  while (hex_value > 9){
    hex_value = hex_value - 10;
    value = value + 1;
    r_adc_char[5] = 0x30 + value;
  }
  r_adc_char[6] = 0x30 + hex_value;
}









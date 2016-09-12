//------------------------------------------------------------------------------
//  File: switch.c
//  Description: This file Processes the switches and changes LCD text.
//
//
//  Zach Hannum
//  Feb 2016
//  Built with IAR Embedded Workbench Version: V7.3.ONE.3987 (6.40.ONE)
//
// Globals
// --------
// extern char *display_1;
// extern char *display_2;
// extern char *display_3;
// extern char *display_1;
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
extern char *display_1;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;
extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int ADC_Left_Detector;
extern volatile unsigned int ADC_Thumb;
extern int current_ADC_channel;
extern volatile int black_line_detected;
int volatile do_not_detect_black_line = ZERO;
int mode;
int count = ZERO;
volatile unsigned long int time = ZERO;
volatile int countTime = ZERO;
volatile int countFive = ZERO;
char time_recorded[5];
extern int BAUD_MODE;
char message[TEN] = "NCSU  #1";  
int i = ZERO;
extern volatile char FRAM_Char_Rx[SMALL_RING_SIZE];
extern volatile unsigned int fram_rx_ring_wr;
extern char RESET_STRING[RESET_STRING_MAX];
char SSID[SSID_STRING_MAX] = "AT+S.SSIDTXT=AndroidAP";
char PASS[PASS_STRING_MAX] = "AT+S.SCFG=wifi_wpa_psk_text,jalapeno";
char PRIV[PRIV_STRING_MAX] = "AT+S.SCFG=wifi_priv_mode,2";
char NET[NET_STRING_MAX] = "AT+S.SCFG=wifi_mode,1";
char SAVE[SAVE_STRING_MAX] = "AT&W";

char BAUD[BAUD_STRING_MAX] = "AT+S.SCFG=console1_speed,9600";
extern volatile int black_line_detect;

extern volatile int ip_detected;
extern char IP[SIXTEEN];




void Switches_Process(void){
  //------------------------------------------------------------------------------
  // Controls IoT Settings
  //
  // Globals
  // --------
  // extern char *display_1;
  ////extern char *display_1;
  ////extern char *display_2;
  ////extern char *display_3;
  ////extern char *display_1;
  ////extern char posL1;
  ////extern char posL2;
  ////extern char posL3;
  ////extern char posL4;
  ////extern char r_adc_char[5];
  ////extern char l_adc_char[5];
  ////extern char v_adc_char[5];
  ////extern volatile unsigned int ADC_Right_Detector;
  ////extern volatile unsigned int ADC_Left_Detector;
  ////extern volatile unsigned int ADC_Thumb;
  ////extern int current_ADC_channel;
  ////extern volatile int black_line_detected;
  ////int volatile do_not_detect_black_line = ZERO;
  ////int mode;
  ////int count = ZERO;
  ////volatile unsigned int time = ZERO;
  ////volatile int countTime = ZERO;
  ////volatile int countFive = ZERO;
  ////char time_recorded[5];
  ////extern int BAUD_MODE;
  ////char message[TEN] = "NCSU  #1";  
  ////int i = ZERO;
  ////extern volatile char FRAM_Char_Rx[SMALL_RING_SIZE];
  ////extern volatile unsigned int fram_rx_ring_wr;
  ////extern char RESET_STRING[RESET_STRING_MAX];
  ////char SSID[SSID_STRING_MAX] = "AT+S.SSIDTXT=AndroidAP";
  ////char PASS[PASS_STRING_MAX] = "AT+S.SCFG=wifi_wpa_psk_text,jalapeno";
  ////char PRIV[PRIV_STRING_MAX] = "AT+S.SCFG=wifi_priv_mode,2";
  ////char NET[NET_STRING_MAX] = "AT+S.SCFG=wifi_mode,1";
  ////char SAVE[SAVE_STRING_MAX] = "AT&W";
  ////
  ////char BAUD[BAUD_STRING_MAX] = "AT+S.SCFG=console1_speed,9600";
  //
  // Ports
  // -----
  // P4IN
  // SW1  // Switch ONE
  // SW2  // Switch TWO
  //------------------------------------------------------------------------------
  if (!(P4IN & SW1)){
    
    /*    char ip_line_1 [DISPLAY_SIZE];
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
    display_2 = ""; */
    P1OUT |= IR_LED;
    black_line_detect = YES;
    
    
  }  
  
  
  if (!(P4IN & SW2)) {
    for(int i = CLR; i < SSID_STRING_MAX; i++){
      display_1="SSID...";
      UCA1TXBUF = SSID[i];
      sleep(TENTHMSEC);
    }
    UCA1TXBUF = '\r';
    sleep(ONEMSEC);
    for(int i = CLR; i < PASS_STRING_MAX; i++){
      display_1="Pass...";
      UCA1TXBUF = PASS[i];
      sleep(TENTHMSEC);
    }
    UCA1TXBUF = '\r';
    sleep(ONEMSEC);
    for(int i = CLR; i < PRIV_STRING_MAX; i++){
      display_1="Privacy...";
      UCA1TXBUF = PRIV[i];
      sleep(TENTHMSEC);
    }
    UCA1TXBUF = '\r';
    sleep(ONEMSEC);
    for(int i = CLR; i < NET_STRING_MAX; i++){
      display_1="Network...";
      UCA1TXBUF = NET[i];
      sleep(TENTHMSEC);
    }
    UCA1TXBUF = '\r';
    sleep(ONEMSEC);
    for(int i = CLR; i < SAVE_STRING_MAX; i++){
      display_1="Saving...";
      UCA1TXBUF = SAVE[i];
      sleep(TENTHMSEC);
    }
    UCA1TXBUF = '\r';
    sleep(ONEMSEC);
    
    for(int i = CLR; i < RESET_STRING_MAX; i++){
      posL4 = CLR;
      display_1 = "resetting...";
      UCA1TXBUF = RESET_STRING[i];
      sleep(TENTHMSEC);
    }
    
    UCA1TXBUF = '\r';
    sleep(ONEMSEC);
    PJOUT = ~IOT_RESET;
    sleep(ONEMSEC);
    PJOUT |= IOT_RESET;
    display_1 = " ";
    display_1 = "Done!";
    
  }
//------------------------------------------------------------------------------
}





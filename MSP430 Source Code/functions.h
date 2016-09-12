// Function prototypes main
void main(void);
void Init_Conditions(void);
void Switches_Process(void);
void Init_Timers(void);
void Init_LEDs(void);
void Display_Process(void);
void five_msec_sleep(unsigned int fivemsec);
void Timer_code(void);
void ADC_Process(void);
void Init_ADC(void);
void HEXtoBCD(unsigned long int hex_value);
void HEXtoBCD_r(int hex_value);
void HEXtoBCD_l(int hex_value);
void HEXtoBCD_v(int hex_value);
void stringcpy(char* s1, char* s2);
void displayMode(void);
void engage(void);
void fiveseconddisplay(void);
void Init_Serial_UCA0(int MODE);
void Init_Serial_UCA1(int MODE);
void Init_Timer_A1(void);
void toInt(void);
void counter(void);

// Function prototypes clocks
void Init_Clocks(void);

// Function prototypes systems
void enable_interrupts(void);

// Function prototypes
__interrupt void Timer2_B0_ISR(void);
 __interrupt void TIMER2_B1_ISR(void);
__interrupt void ADC10_ISR(void);
void Init_Timer_A0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void measure_delay(void);
void usleep10(unsigned int usec);

// Function prototypes ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(char TOGGLE);
void Init_Port4(void);
void Init_PortJ(char TOGGLE);

// LCD
void Init_LCD(void);
void WriteIns(char instruction);
void WriteData(char data);
void ClrDisplay(void);
void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);

void grab_a_character(void);
int wait_for_character(void);
void menu(void);

// SPI
void Init_SPI_B0(void);
void SPI_B0_write(char byte);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);

// Wheels
void Left_Wheel_Off(void);
void Right_Wheel_Off(void);
void Wheels_Off(void);
void Wheels_Forward_On(int duty);
void Wheels_Reverse_On(int duty);
void Right_Wheel_Forward_On(int duty);
void Right_Wheel_Reverse_On(int duty);
void Left_Wheel_Forward_On(int duty);
void Left_Wheel_Reverse_On(int duty);

// Shapes
void shape(void);
void Circle(void);
void Triangle(void);
void FigureEight(void);

//timers
void sleep(int sleepTime);


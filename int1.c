#include "p24hj64gp202.h"
#include "int1.h"
#include "lcd.h"
#include "accel.h"

unsigned char interrupts;

void INT1Configuration(void){  
  interrupts = 0;
  INTCON2bits.INT1EP = 0; //Interrupt on low-to-high edge
  IFS1bits.INT1IF = 0;    //Clear INT1 interrupt flag
  IEC1bits.INT1IE = 1;    //Enagle INT1 interrupts
}

void _ISR _INT1Interrupt(void){
  IFS1bits.INT1IF = 0;
  accelerationReady = 1;
  //LCDWriteChar('.',1,interrupts++);
  //LCDWriteText("OPA",1,4);
  
}

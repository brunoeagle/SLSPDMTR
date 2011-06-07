#include "p24hj64gp202.h"
#include "int2.h"

void INT2Configuration(void){  
  INTCON2bits.INT2EP = 0; //Interrupt on low-to-high edge
  IFS1bits.INT2IF = 0;    //Clear INT1 interrupt flag
  IEC1bits.INT2IE = 1;    //Enagle INT1 interrupts
}

void _ISR _INT2Interrupt(void){
  IFS1bits.INT2IF = 0;
}

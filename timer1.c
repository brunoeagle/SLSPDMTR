#include "p24hj64gp202.h"
#include "timer1.h"

char T1_OK;

void TIMER1Configuration(void){  
  T1CONbits.TON = 0;    //Disable TIMER1 module
  T1CONbits.TCS = 0;    //Internal clock for TIMER1
  T1CONbits.TGATE = 0;  //Disable gated mode
  T1CONbits.TCKPS = 3;  //256:1 prescaler > 156.250 KHz (6.4uSec)
  TMR1 = 0x0000;
  IPC0bits.T1IP = 0x01; //Priority 1 for TIMER1
  IFS0bits.T1IF = 0;    //Clear TIMER1 interrupt flag
  IEC0bits.T1IE = 1;    //Enable TIMER1 interrupt
  T1_OK = 0;
  
}

void TIMER1SleepMS(unsigned int mSec){
  while(mSec > 419){
    mSec -= 419;
    TMR1 = 0x0000;	//clears the TMR register
    PR1 = 0xFFFF;
    T1CONbits.TON = 1;
    while(!T1_OK);
    T1_OK = 0;
  }
  TMR1 = 0x0000;
  PR1 = (mSec)/0.0064;
  T1CONbits.TON = 1;
  while(!T1_OK);
  T1_OK = 0;
}

void TIMER1SleepUS(unsigned int uSec){
  TMR1 = 0x0000;
  PR1 = (uSec)/6.4;
  if(uSec < 7) PR1 = 1;
  T1CONbits.TON = 1;
  while(!T1_OK);
  T1_OK = 0;  
}

void _ISR _T1Interrupt(void){
  IFS0bits.T1IF = 0;    //Clear Timer1 interrupt flag
  T1CONbits.TON = 0;
  T1_OK = 1;
}

/*Timer 1 configuration and sleep functions*/
#ifndef __TIMER1_H
#define __TIMER1_H

void TIMER1Configuration(void);		//Configurations
void TIMER1SleepMS(unsigned int);	//Provides a miliseconds delay
void TIMER1SleepUS(unsigned int);	//Provides a microseconds delay
void _ISR _T1Interrupt(void);		//Timer 1 interrupt service routine


#endif

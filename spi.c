#include "p24hj64gp202.h"
#include "spi.h"
#include "timer1.h"

TransferByte transferByte;

void SPIConfiguration(void){
  IFS0bits.SPI1IF = 0;      //Clear SPI1 interrupt flag
  IEC0bits.SPI1IE = 0;      //Disabele SPI1 interrupts
  
  SPI1CON1bits.DISSCK = 0;  //Module controls the SCK1 pin
  SPI1CON1bits.DISSDO = 0;  //Module controls the SDO1 pin
  SPI1CON1bits.MODE16 = 1;  //Module operates in 16-bit mode
  SPI1CON1bits.SMP = 0;     //Module samples the input data at the middle of the output
  SPI1CON1bits.CKE = 1;     //SDO1 changes in High-to-Low (Active-to-Idle) transiction of SCK1
  SPI1CON1bits.CKP = 0;     //SCK1 has its idle state in low-level
  SPI1CON1bits.PPRE = 2;    //SPI1 primary prescaler is 1:1
  SPI1CON1bits.SPRE = 3;    //SPI1 secondary prescaler is 5:1 resulting in 8 MHz clock for SPI1 module
  SPI1CON1bits.MSTEN = 1;   //SPI1 module in master mode
  SPI1STATbits.SPIEN = 1;   //Enable SPI1 module
  
  IFS0bits.SPI1IF = 0;      //Clear SPI1 interrupt flag
  
  CS_ACCEL = 1;
}

void SPIWrite(unsigned char address, unsigned char value){
  SPI1STATbits.SPIROV = 0;
  IFS0bits.SPI1IF = 0;
  CS_ACCEL = 0;
  TIMER1SleepMS(1);
  transferByte.integer = 0;
  transferByte.chars[1] = (address << 1) | 0x80;
  transferByte.chars[0] = value;
  SPI1BUF = transferByte.integer;
  while(!IFS0bits.SPI1IF);
  TIMER1SleepMS(1);
  IFS0bits.SPI1IF = 0;
  TIMER1SleepMS(1);
  CS_ACCEL = 1;
}

unsigned char SPIRead(unsigned char address){
  unsigned char value;
  SPI1STATbits.SPIROV = 0;
  IFS0bits.SPI1IF = 0;
  CS_ACCEL = 0;
  TIMER1SleepMS(1);
  transferByte.integer = 0;
  transferByte.chars[1] = (address << 1) & 0x7F;  
  SPI1BUF = transferByte.integer;
  while(!IFS0bits.SPI1IF);
  IFS0bits.SPI1IF = 0;
  TIMER1SleepMS(1);
  CS_ACCEL = 1;
  TIMER1SleepMS(1);
  value = SPI1BUF;
  return value;
}

#include "p24hj64gp202.h"
#include "MCUConfig.h"

void OSCConfiguration(void){
  OSCTUN = 21;            // FRC oscillator in 8.00 MHz
  CLKDIVbits.PLLPRE = 0;  // FRC/2 = 4.00 MHz
  PLLFBDbits.PLLDIV = 40; // (FRC/2) x 40 = 160 MHz
  CLKDIVbits.PLLPOST = 0; // ((FRC/2) x 40) /2 = 80 MHz (Fosc = 80Mhz)
  __builtin_write_OSCCONH(0x01);    // Internal FRC with PLL selected
  __builtin_write_OSCCONL(0x01);    // Switch clock to mode selected
  while(OSCCONbits.COSC != 0b001);  // Wait the clock to be switched
  while(OSCCONbits.LOCK != 1);      // Wait PLL to lock
}

void IOConfiguration(void){
  AD1PCFGL = 0xFFFF;
  CMCON = 0x0000;
  
  //INT1_ACCEL
  RPINR0bits.INT1R &= 9;   // External INT1 tied to RP9  
  Nop();
  //INT2_ACCEL
  RPINR1bits.INT2R &= 8;   // External INT2 tied to RP8  
  Nop();
  //MISO_ACCEL
  RPINR20bits.SDI1R &= 12; // MISO from accelerometer tied to RP12  
  Nop();
  //MOSI_ACCEL
  RPOR6bits.RP13R |= 7;    // MOSI to accelerometer tied to RP13  
  Nop();
  //SCK_ACCEL
  RPOR7bits.RP14R |= 8;    // SCK to accelerometer tied to RP14  
  Nop();
  //CS_ACCEL
  RPOR7bits.RP15R |= 9;    // CS to accelerometer tied to RP15  
  Nop();
  
  TRISA = 0x0000;   // PORTA is output
  Nop();
  PORTA = 0x0000;
  Nop();
  TRISB = 0x1300;   // RB8, RB9 and RB12 are input
  Nop();
  PORTB = 0x0000;
  Nop();
}

/*SPI configuration*/
#ifndef __SPI_H
#define __SPI_H

#define CS_ACCEL    LATBbits.LATB15
#define SCK_ACCEL   LATBbits.LATB14
#define MOSI_ACCEL  LATBbits.LATB13
#define MISO_ACCEL  LATBbits.LATB12

void SPIConfiguration(void);					//Initializes and setup the operation modes
void SPIWrite(unsigned char,unsigned char);		//Write a byte
unsigned char SPIRead(unsigned char);			//Read a byte

typedef union{
  unsigned int integer;
  unsigned char chars[2];  
}TransferByte;				//Struct to provide access a value through different types

extern TransferByte transferByte;

#endif

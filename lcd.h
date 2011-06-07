/*LCD pins and initialization configurations and some stuff*/
#ifndef __LCD_H
#define __LCD_H

#define LCD_DATA            LATB        //PORTB<7:0> <> DB7:DB0
#define LEFT_HALF              0
#define RIGHT_HALF             1
#define CS2       LATAbits.LATA4
#define CS1       LATAbits.LATA3
#define ENABLE    LATAbits.LATA1
#define RS        LATAbits.LATA0
#define COMMAND                0
#define DATA                   1

void LCDInitialization(void);										//Initialization sequence of the display
void LCDWriteCommand(unsigned char,unsigned char);					//Command write to display controller
void LCDWriteData(unsigned char,unsigned char);						//Data write to display controller
void LCDPutData(unsigned char,unsigned char);						//Data write to display controller
void LCDWriteImage(unsigned char *);								//Image write to display controller
void LCDWriteChar(unsigned char,unsigned char,unsigned char);		//Writes a character to the display
void LCDWriteText(unsigned char *,unsigned char,unsigned char);		//Writes a string to the display 
void LCDClearScreen(void);											//Clears the display
void LCD200ns(void);												//200 nanoseconds delay for some operations
void LCD500ns(void);												//500 nanoseconds delay for some operations

#endif

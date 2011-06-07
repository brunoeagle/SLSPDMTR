#include "p24hj64gp202.h"
#include "lcd.h"
#include "timer1.h"
#include "font.h"

unsigned char initializationBytes[] = {0xC0,0x40,0xB8,0x3F};

void LCDInitialization(void){
  unsigned char cfgCont;
  TIMER1SleepMS(100);
  for(cfgCont = 0; cfgCont <= 3; cfgCont++){
    LCDWriteCommand(initializationBytes[cfgCont],0);
  }
  for(cfgCont = 0; cfgCont <= 3; cfgCont++){
    LCDWriteCommand(initializationBytes[cfgCont],1);
  }
}

void LCDWriteCommand(unsigned char value, unsigned char half){
  RS = COMMAND;
  LCDPutData(value,half);
}

void LCDWriteData(unsigned char value, unsigned char half){
  RS = DATA;
  LCDPutData(value,half);
}  

void LCDPutData(unsigned char value,unsigned char half){
  if(half == LEFT_HALF) CS1 = 1;
  else CS2 = 1;
  LCD_DATA |= value;
  LCD200ns();   //tAS
  LCD200ns();
  ENABLE = 1;
  LCD500ns();   //PWEH
  LCD500ns();
  ENABLE = 0;
  LCD500ns();   //PWEL
  LCD500ns();
  LCD_DATA &= 0xFF00;
  CS2 = 0;
  CS1 = 0;
  LCD500ns();
}

void LCDWriteImage(unsigned char *imagePointer){
  unsigned char xCount, yCount, pixels;
  unsigned char *pointer;
  pointer = imagePointer;
  xCount = 0x40;
  yCount = 0xB8;
  while(yCount <= 0xBF){
    LCDWriteCommand(yCount,LEFT_HALF);      //write the row address
    LCDWriteCommand(xCount,LEFT_HALF);      //write the column command (auto-increment)
    while(xCount <= 0x7F){
      pixels = *pointer++;
      LCDWriteData(pixels,LEFT_HALF);
      xCount++;
    }
    xCount = 0x40;
    LCDWriteCommand(yCount,RIGHT_HALF);      //write the row address
    LCDWriteCommand(xCount,RIGHT_HALF);      //write the column command (auto-increment)
    while(xCount <= 0x7F){
      pixels = *pointer++;
      LCDWriteData(pixels,RIGHT_HALF);
      xCount++;
    }
    yCount++;
    xCount = 0x40;    //initial column counter
  }
}

void LCDWriteChar(unsigned char character, unsigned char row, unsigned char column){
  unsigned char fontSize, pixels;
  unsigned char *pointer;
  fontSize = FONT_SIZE;
  
  pointer = font;
  pointer += (character - 0x20) * fontSize;
  
  while(fontSize--){
    if(column < 64){
      LCDWriteCommand(0x40 + column,LEFT_HALF);
      LCDWriteCommand(0xB8 + row,LEFT_HALF);
      pixels = *pointer++;
      pixels = ~pixels;
      LCDWriteData(pixels,LEFT_HALF);
    }
    if(column >= 64 && column < 128){
      LCDWriteCommand(0x40 + (column-64),RIGHT_HALF);
      LCDWriteCommand(0xB8 + row,RIGHT_HALF);
      pixels = *pointer++;
      pixels = ~pixels;
      LCDWriteData(pixels,RIGHT_HALF);
    }
    column++;
  }
}

void LCDWriteText(unsigned char *text, unsigned char row, unsigned char column){
  unsigned char *pointer, columnCount;  
  
  pointer = text;
  columnCount = 0;  
  while(*pointer != 0x00){
    LCDWriteChar(*pointer++,row,column + columnCount);
    columnCount += 6;
  }
}

void LCDClearScreen(void){
  unsigned char xCount, yCount;
  xCount = 0x40;
  yCount = 0xB8;
  while(yCount <= 0xBF){
    LCDWriteCommand(yCount,LEFT_HALF);      //write the row address
    LCDWriteCommand(xCount,LEFT_HALF);      //write the column command (auto-increment)
    while(xCount <= 0x7F){
      LCDWriteData(0xFF,LEFT_HALF);
      xCount++;
    }
    xCount = 0x40;
    LCDWriteCommand(yCount,RIGHT_HALF);      //write the row address
    LCDWriteCommand(xCount,RIGHT_HALF);      //write the column command (auto-increment)
    while(xCount <= 0x7F){
      LCDWriteData(0xFF,RIGHT_HALF);
      xCount++;
    }
    yCount++;
    xCount = 0x40;    //initial column counter
  }
}


void LCD200ns(void){
  Nop(); Nop();  Nop();  Nop(); //100ns
  Nop(); Nop();  Nop();  Nop(); //200ns
  Nop(); Nop();  Nop();  Nop(); //100ns
  Nop(); Nop();  Nop();  Nop(); //200ns
  Nop(); Nop();  Nop();  Nop(); //100ns
  Nop(); Nop();  Nop();  Nop(); //200ns
  Nop(); Nop();  Nop();  Nop(); //100ns
  Nop(); Nop();  Nop();  Nop(); //200ns
  Nop(); Nop();  Nop();  Nop(); //100ns
  Nop(); Nop();  Nop();  Nop(); //200ns
  Nop(); Nop();  Nop();  Nop(); //100ns
  Nop(); Nop();  Nop();  Nop(); //200ns
  Nop(); Nop();  Nop();  Nop(); //100ns
  Nop(); Nop();  Nop();  Nop(); //200ns
  Nop(); Nop();  Nop();  Nop(); //100ns
  Nop(); Nop();  Nop();  Nop(); //200ns
}

void LCD500ns(void){
  Nop(); Nop();  Nop();  Nop(); //100ns
  Nop(); Nop();  Nop();  Nop(); //200ns
  Nop(); Nop();  Nop();  Nop(); //300ns
  Nop(); Nop();  Nop();  Nop(); //400ns
  Nop(); Nop();  Nop();  Nop(); //500ns
  Nop(); Nop();  Nop();  Nop(); //100ns
  Nop(); Nop();  Nop();  Nop(); //200ns
  Nop(); Nop();  Nop();  Nop(); //300ns
  Nop(); Nop();  Nop();  Nop(); //400ns
  Nop(); Nop();  Nop();  Nop(); //500ns
  Nop(); Nop();  Nop();  Nop(); //100ns
  Nop(); Nop();  Nop();  Nop(); //200ns
  Nop(); Nop();  Nop();  Nop(); //300ns
  Nop(); Nop();  Nop();  Nop(); //400ns
  Nop(); Nop();  Nop();  Nop(); //500ns
  Nop(); Nop();  Nop();  Nop(); //100ns
  Nop(); Nop();  Nop();  Nop(); //200ns
  Nop(); Nop();  Nop();  Nop(); //300ns
  Nop(); Nop();  Nop();  Nop(); //400ns
  Nop(); Nop();  Nop();  Nop(); //500ns
}

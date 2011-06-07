/*Framebuffer functions to 128x64 display*/
#include "p24hj64gp202.h"
#include "FB.h"
#include "lcd.h"

unsigned char frameBuffer[128][8];

/*Put a black pixel on a defined location of framebuffer*/
void FBPutPixel(unsigned char x, unsigned char y){
  unsigned char masterLine = y/8;
  unsigned char subLine = y % 8;
  unsigned char mask = 0x01 << subLine;
  mask = ~mask;
  
  frameBuffer[x][masterLine] &= mask;

}

/*Makes a raw copy from framebuffer to the display*/
void FBWrite(void){
  unsigned char xCount, yCount, pixels;
  xCount = 0x40;
  yCount = 0xB8;
  while(yCount <= 0xBF){
    LCDWriteCommand(yCount,LEFT_HALF);      //write the row address
    LCDWriteCommand(xCount,LEFT_HALF);      //write the column command (auto-increment)
    while(xCount <= 0x7F){
      pixels = frameBuffer[xCount - 64][yCount - 184];
      LCDWriteData(pixels,LEFT_HALF);
      xCount++;
    }
    xCount = 0x40;
    LCDWriteCommand(yCount,RIGHT_HALF);      //write the row address
    LCDWriteCommand(xCount,RIGHT_HALF);      //write the column command (auto-increment)
    while(xCount <= 0x7F){
      pixels = frameBuffer[xCount][yCount - 184];
      LCDWriteData(pixels,RIGHT_HALF);
      xCount++;
    }
    yCount++;
    xCount = 0x40;    //initial column counter
  }
}

/*Blank the framebuffer*/
void FBClear(void){
  unsigned char x, y;
  for(y = 0; y < 8; y++){
    for(x = 0; x < 128; x++){
      frameBuffer[x][y] = 0xFF;
    }
  }
}

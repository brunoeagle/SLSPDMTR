/*Framebuffer raw accesses*/
#ifndef __FB_H
#define __FB_H

void FBPutPixel(unsigned char,unsigned char);	//Put a pixel on a determined location on framebuffer
void FBClear(void);								//Blank the framebuffer
void FBWrite(void);								//Write the framebuffer on display

extern unsigned char frameBuffer[128][8];



#endif

/*Drawning functions for a 128x64 graphical display*/
#include "p24hj64gp202.h"
#include "FB.h"
#include "lcd.h"
#include "math.h"
#include "DRAW.h"


void DrawArc(char xi,char yi, unsigned char angle,unsigned char force){
  float angle_rad, t;
  char x, y;
  x = xi;
  y = yi;
  angle_rad = (3.141592653 * (float)angle) / 180;
  t = 0.1;
  while(1){
    x += force * cos(angle_rad) * t;
    y -= force * sin(angle_rad) * t - 9.8 * pow(t,2)/2;
    if (x > 127 || x < 0 || y < 0 || y > 63) break;
    FBPutPixel(x,y);
    t += 0.1;
  }
}

void DrawSphere(unsigned char x ,unsigned char y,unsigned char radius){
  int _y, _x;
  int minX = ((int)x-(int)radius);
	int maxX = ((int)x+(int)radius);
	int minY = ((int)y-(int)radius);
	int maxY = ((int)y+(int)radius);

	for (_y=minY; _y<maxY; _y++)
	{
		for (_x=minX; _x<maxX; _x++)
		{
			if (_x>=128 || _y>=64 || _x<0 || _y<0)
				continue;
			const int diffX = (int)x-_x;
			const int diffY = (int)y-_y;
			if (sqrtf((float)diffX*(float)diffX + (float)diffY*(float)diffY) < (float)radius)
			{
				FBPutPixel((unsigned char)_x, (unsigned char)_y);
			}
		}
	}
}


/*float fastSqrt(float x)
{
	float xhalf = 0.5f*x;
	int i = *(int*)&x;
	i = 0x5f3759df - (i >> 1);
	x = *(float*)&i;
	x = x*(1.5f - xhalf*x*x);
	return 1/x;
}
*/
/*
void drawSphere(unsigned char x, unsigned char y, unsigned char radius)
{
	const int minX = int(x-radius);
	const int maxX = int(x+radius);
	const int minY = int(y-radius);
	const int maxY = int(y+radius);

	for (int _y=minY; _y<maxY; _y++)
	{
		for (int _x=minX; _x<maxX; _x++)
		{
			if (_x>=128 || _y>=64 || _x<0 || _y<0)
				continue;
			const int diffX = (int)x-_x;
			const int diffY = (int)y-_y;
			if (fastSqrt((float)diffX*(float)diffX + (float)diffY*(float)diffY) < (float)radius)
			{
				putPixel((unsigned char)_x, (unsigned char)_y);
			}
		}
	}
}
*/

#include "p24hj64gp202.h"
#include "MCUConfig.h"
#include "spi.h"
#include "int1.h"
#include "int2.h"
#include "lcd.h"
#include "timer1.h"
#include "images.h"
#include "accel.h"
#include "MMA7455_REGISTERS.h"
#include "FB.h"
#include "DRAW.h"
//#include "stdlib.h"

#define X_AXIS8  0x06
#define Y_AXIS8  0x07
#define Z_AXIS8  0x08

#define RADIUS_SPHERE   5
#define XSPHERE_INITIAL 64
#define YSPHERE_INITIAL 32

void PutLCDAcceleration(char,unsigned char);
void SplashScreen(void);
void GetRandomCoordinates(void);
void ShowVelocity(void);

char xAxis, yAxis, zAxis, average, averageShow;
float accelerationx, accelerationy, lastAccelerationx, lastVelocityx, velocityx, sample;
unsigned char velocidadeX[5];
//int xSphere, ySphere;
//unsigned char posRandX, posRandY;

int main(){
  unsigned char statusAccel, accelerationReady;
  OSCConfiguration();     //Running at 40 MIPS
  IOConfiguration();      //EINT and SPI pins mapped
  SPIConfiguration();     //SPI1 configuration for accelerometer 
  INT1Configuration();    //INT1 configuration for accelerometer
  INT2Configuration();    //INT2 configuration for accelerometer
  TIMER1Configuration();  //TIMER1 configuration
  LCDInitialization();

  //SplashScreen();
  LCDClearScreen();
  ACCELInitialization();
  statusAccel = SPIRead(MCTL);

  average = 0;
  averageShow = 0;
  accelerationx = 0;
  lastAccelerationx = 0;  
  velocityx = 0;
  lastVelocityx = 0;

  while(1) {
    statusAccel = ACCELGetStatus();
    if (statusAccel & 0x01) {   //if data is ready in accelerometer
      xAxis = ACCELReadAxis(X_AXIS8);
      yAxis = ACCELReadAxis(Y_AXIS8);
      zAxis = ACCELReadAxis(Z_AXIS8);
      accelerationx += (float)xAxis;
      average++;
      if (average == 5){
        accelerationx /= average;
        accelerationx *= -1;
        average = 0;
        if (accelerationx > 3 || accelerationx < -3){
          accelerationx = (accelerationx* 19.6) / 127;
          accelerationx *= 0.08;
          velocityx = lastVelocityx + lastAccelerationx + ((accelerationx - lastAccelerationx) / 2);
          lastVelocityx = velocityx;
          lastAccelerationx = accelerationx;
          accelerationx = 0;
          if(velocityx < 0) velocityx = 0;
        }
      }
      if(averageShow++ == 7){
        averageShow = 0;
        ShowVelocity();
      }
    }
  }
  return 1;
}

void ShowVelocity(void){
  unsigned char centena, dezena, unidade;
  float kmh;
  //velocityx é a velocidade atual.  

  kmh = velocityx * 3.6;
  centena = kmh / 100;
  dezena = (kmh - (centena * 100)) / 10;
  unidade = kmh - (centena * 100) - (dezena * 10);

  LCDWriteChar(centena | 0x30,2,30);
  LCDWriteChar(dezena | 0x30,2,36);
  LCDWriteChar(unidade | 0x30,2,42);

  LCDWriteText("km/h",2,48);
  
  
}


/*void PutLCDAcceleration(char acceleration, unsigned char row){
  unsigned char x; 
  
  acceleration /= 2;
  
  if(acceleration < 0){
    acceleration *= -1;
    x = 128;
    LCDWriteCommand(0xB8 + row,LEFT_HALF);
    while(acceleration--){     
      LCDWriteCommand(x,LEFT_HALF);
      LCDWriteData(0x00,LEFT_HALF);
      x--;
      if(x < 64) acceleration = 0;
    }
    while(x-- > 64){
      LCDWriteCommand(x,LEFT_HALF);
      LCDWriteData(0xFF,LEFT_HALF);
      if(x < 64) x = 0;
    }
    x = 64;
    LCDWriteCommand(0xB8 + row,RIGHT_HALF);
    do{
      LCDWriteCommand(x,RIGHT_HALF);
      LCDWriteData(0xFF,RIGHT_HALF);      
    }while(x++ < 128);
  }
  else{
    x = 64;
    LCDWriteCommand(0xB8 + row,RIGHT_HALF);
    while(acceleration--){
      LCDWriteCommand(x,RIGHT_HALF);
      LCDWriteData(0x00,RIGHT_HALF);
      x++;
      if(x > 127) acceleration = 0;
    }
    while(x++ < 128){
      LCDWriteCommand(x,RIGHT_HALF);
      LCDWriteData(0xFF,RIGHT_HALF);
    }
    x = 128;
    LCDWriteCommand(0xB8 + row,LEFT_HALF);
    do{
      LCDWriteCommand(x,LEFT_HALF);
      LCDWriteData(0xFF,LEFT_HALF);      
    }while(x-- > 63);
  }
}*/

void SplashScreen(void){
  LCDWriteImage(logoJeraFundoPreto);
  TIMER1SleepMS(2000);
}

/*void GetRandomCoordinates(void){
  do{
    posRandX = (unsigned char)rand();
  }while(posRandX > (127 - RADIUS_SPHERE) || posRandX < RADIUS_SPHERE);
  do{
    posRandY = rand();
  }while(posRandY > (63 - RADIUS_SPHERE) || posRandY < RADIUS_SPHERE);
}
*/
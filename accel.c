/*Functions to provide basica access to the accelerometer*/
#include "p24hj64gp202.h"
#include "accel.h"
#include "spi.h"
#include "timer1.h"
#include "MMA7455_REGISTERS.h"

unsigned char accelerationReady;

void ACCELInitialization(void){
  accelerationReady = 0;
  SPIWrite(MCTL,0x05);    //Measurement Mode - 2G
  TIMER1SleepMS(500);
}

unsigned char ACCELGetStatus(void){
  unsigned char status;
  status = SPIRead(STATUS);
  return status;
}

unsigned char ACCELReadAxis(unsigned char axis){
  unsigned char xAxis;
  xAxis = SPIRead(axis);
  return xAxis;
}

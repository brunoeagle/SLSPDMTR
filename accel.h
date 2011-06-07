/*Accelerometer header functions*/
#ifndef __ACCEL_H
#define __ACCEL_H

void ACCELInitialization(void);				//Initialize the accelerometer
unsigned char ACCELGetStatus(void);			//Get status of accelerometer (if new data is ready for example)
unsigned char ACCELReadAxis(unsigned char);	//Read acceleration data on a determined axis

extern unsigned char accelerationReady;		//New data ready

#endif

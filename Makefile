# MPLAB IDE generated this makefile for use with GNU make.
# Project: SLSPDMTR.mcp
# Date: Tue Feb 08 18:23:30 2011

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

SLSPDMTR.hex : SLSPDMTR.cof
	$(HX) "SLSPDMTR.cof"

SLSPDMTR.cof : accel.o int1.o int2.o lcd.o main.o MCUConfig.o spi.o timer1.o FB.o
	$(CC) -mcpu=24HJ64GP202 "accel.o" "int1.o" "int2.o" "lcd.o" "main.o" "MCUConfig.o" "spi.o" "timer1.o" "FB.o" -o"SLSPDMTR.cof" -Wl,-Tp24HJ64GP202.gld,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD2=1,--defsym=__ICD2RAM=1,-Map="SLSPDMTR.map",--report-mem

accel.o : MMA7455_REGISTERS.h timer1.h spi.h accel.h c:/program\ files\ (x86)/microchip/mplabc30/v3.25/support/PIC24H/h/p24hj64gp202.h accel.c
	$(CC) -mcpu=24HJ64GP202 -x c -c "accel.c" -o"accel.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

int1.o : accel.h lcd.h int1.h c:/program\ files\ (x86)/microchip/mplabc30/v3.25/support/PIC24H/h/p24hj64gp202.h int1.c
	$(CC) -mcpu=24HJ64GP202 -x c -c "int1.c" -o"int1.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

int2.o : int2.h c:/program\ files\ (x86)/microchip/mplabc30/v3.25/support/PIC24H/h/p24hj64gp202.h int2.c
	$(CC) -mcpu=24HJ64GP202 -x c -c "int2.c" -o"int2.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

lcd.o : font.h timer1.h lcd.h c:/program\ files\ (x86)/microchip/mplabc30/v3.25/support/PIC24H/h/p24hj64gp202.h lcd.c
	$(CC) -mcpu=24HJ64GP202 -x c -c "lcd.c" -o"lcd.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

main.o : c:/program\ files\ (x86)/microchip/mplabc30/v3.25/include/math.h FB.h MMA7455_REGISTERS.h accel.h images.h timer1.h lcd.h int2.h int1.h spi.h MCUConfig.h c:/program\ files\ (x86)/microchip/mplabc30/v3.25/support/PIC24H/h/p24hj64gp202.h main.c
	$(CC) -mcpu=24HJ64GP202 -x c -c "main.c" -o"main.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

MCUConfig.o : MCUConfig.h c:/program\ files\ (x86)/microchip/mplabc30/v3.25/support/PIC24H/h/p24hj64gp202.h MCUConfig.c
	$(CC) -mcpu=24HJ64GP202 -x c -c "MCUConfig.c" -o"MCUConfig.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

spi.o : timer1.h spi.h c:/program\ files\ (x86)/microchip/mplabc30/v3.25/support/PIC24H/h/p24hj64gp202.h spi.c
	$(CC) -mcpu=24HJ64GP202 -x c -c "spi.c" -o"spi.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

timer1.o : timer1.h c:/program\ files\ (x86)/microchip/mplabc30/v3.25/support/PIC24H/h/p24hj64gp202.h timer1.c
	$(CC) -mcpu=24HJ64GP202 -x c -c "timer1.c" -o"timer1.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

FB.o : lcd.h timer1.h FB.h c:/program\ files\ (x86)/microchip/mplabc30/v3.25/support/PIC24H/h/p24hj64gp202.h FB.c
	$(CC) -mcpu=24HJ64GP202 -x c -c "FB.c" -o"FB.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

clean : 
	$(RM) "accel.o" "int1.o" "int2.o" "lcd.o" "main.o" "MCUConfig.o" "spi.o" "timer1.o" "FB.o" "SLSPDMTR.cof" "SLSPDMTR.hex"


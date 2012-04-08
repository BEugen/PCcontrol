
/*****************************************************************************
* 
* File              : TerminalDemo.c
* Compiler          : avr-gcc 3.4.3 / avr-libc 1.2.3
* Version           : 2.2(gcc)
* Last modified     : 21. Aug. 2005
* Description       : Terminal demo application
*
* This is an avr-gcc port of the orignal version 2.1
* Copyright (C) 2003 Atmel Corporation
* for the IAR EWAAVR 2.28a Compiler
*
* Ported and a little bit extended by: 
*  Martin Thomas <evermsith@heizung-thomas.de>
*  http://www.siwawi.arubi.uni-kl.de/avr_projects
*  
* Tested with Windows2000 Hyperterm in "ANSIW" emulation
*
****************************************************************************/

#include <pgmspace.h>
#include <ioavr.h>
#include <intrinsics.h>
#include <pgmspace.h>
#include "types.h"
#include "usart.h"
#include "configpin.h"

#include "TerminalDriver.h"
#include "command.h"
#include "menu.h"
#include "timer.h"
#include "checkstatesignals.h"
#include "events.h"

#define BAUDRATE 19200



int main(void)
{
	//uart_init( UART_BAUD_SELECT(BAUDRATE, F_CPU) );
        valGroup.usbStatus = 1;
        valGroup.powerStatus = 1;
        valGroup.powerGoodStatus = 1;
        valGroup.tValue[0] = 34.5f;
        valGroup.Counter = 12;
        parmGroup.timeWaitOffImm = 10;
        parmGroup.timeWaitOffSafety = 10;
        parmGroup.fan1Div = 2.0;
        parmGroup.fan2Div = 2.0;
        OWI_Init(BUS);
	init_usart();
        PinInit();
        InitTimer0();
        InitCommandTimers();
        InitFanControl();
        __enable_interrupt();       
	DrawMenuAll();
	while (1) {
	  CheckCmd();
          CheckWatchdog();
          CheckCmdForExecute();
          CheckSateSignals(&valGroup);
          DrawValues();	
	}	
	return 0;
}

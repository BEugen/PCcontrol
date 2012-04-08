
/*****************************************************************************
* 
* File              : TerminalDriver.h
* Compiler          : avr-gcc 3.4.3 / avr-libc 1.2.3
* Version           : 2.2(gcc)
* Last modified     : 21. Aug. 2005
*
* Description       : Terminal emulation interface header file
*
* This code is an avr-gcc port of the orignal version 2.1
* Copyright (C) 2003 Atmel Corporation
* for the IAR EWAAVR 2.28a Compiler
*
* ported by Martin Thomas 
*  http://www.siwawi.arubi.uni-kl.de/avr_projects
*  <evermsith@heizung-thomas.de>
*
****************************************************************************/

#ifndef TERMINALDRIVER_H
#define TERMINALDRIVER_H

#include <ioavr.h>
#include <intrinsics.h>
// Fleury's uart-libary used here
#include "usart.h"

//***************************
// Misc definitions
//***************************

/*** Text modes ***/
#define MODE_NONE         '0'
#define MODE_BOLD         '1'
#define MODE_DIM          '2'
#define MODE_UNDERLINE    '4'
#define MODE_BLINK        '5'
#define MODE_REVERSED     '7'
#define MODE_CONCEALED    '8'


/*** Text colours ***/
#define COL_FOREGROUND    '3'
#define COL_BACKGROUND    '4'

#define COL_BLACK         '0'
#define COL_RED           '1'
#define COL_GREEN         '2'
#define COL_YELLOW        '3'
#define COL_BLUE          '4'
#define COL_MAGENTA       '5'
#define COL_CYAN          '6'
#define COL_WHITE         '7'


/*** Cursor move direction ***/
#define MOVE_UP           'A'
#define MOVE_DOWN         'B'
#define MOVE_RIGHT        'C'
#define MOVE_LEFT         'D'



//***************************
// Function prototypes
//***************************

unsigned char Term_Get(void);
unsigned char Term_Handle_Menu( const unsigned char * menu, unsigned char selectPos,
                                unsigned char top, unsigned char left, unsigned char doubleFrame );
unsigned char Term_Draw_Menu( const unsigned char * menu, unsigned char selectPos,
                              unsigned char top, unsigned char left, unsigned char doubleFrame );
unsigned int  Term_Get_Sequence(void);
unsigned char Term_Send_FlashStr( const unsigned char * str );
unsigned char Term_Send_RAMStr( unsigned char * str );
void Term_Draw_Frame( unsigned char top, unsigned char left, 
                      unsigned char height, unsigned char width, unsigned char doubleFrame );
void Term_Erase_Line(void);
void Term_Erase_Screen(void);
void Term_Erase_ScreenBottom(void);
void Term_Erase_ScreenTop(void);
void Term_Erase_to_End_of_Line(void);
void Term_Erase_to_Start_of_Line(void);
void Term_Initialise(void);
void Term_Move_Cursor( unsigned char distance, unsigned char direction );
void Term_Print_Screen(void);
void Term_Restore_Cursor_Position(void);
void Term_Save_Cursor_Position(void);
void Term_Send( unsigned char data );
void Term_Send_Value_as_Digits( unsigned char value );
void Term_Set_Cursor_Position( unsigned char row, unsigned char column );
void Term_Set_Display_Attribute_Mode( unsigned char mode );
void Term_Set_Display_Colour( unsigned char fg_bg, unsigned char colour );
void Term_Set_Scroll_Mode_All(void);
void Term_Set_Scroll_Mode_Limit( unsigned char start, unsigned char end );


#endif

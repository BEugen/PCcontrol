
/*****************************************************************************
* 
* File              : TerminalDriver.c
* Compiler          : avr-gcc 3.4.3 / avr-libc 1.2.3
* Version           : 2.2(gcc)
* Last modified     : 21. Aug. 2005
*
* Description       : Terminal emulation interface
*
* This is an avr-gcc port of the orignal version 2.1
* Copyright (C) 2003 Atmel Corporation
* for the IAR EWAAVR 2.28a Compiler
*
* ported by Martin Thomas 
*  http://www.siwawi.arubi.uni-kl.de/avr_projects
*  <evermsith@heizung-thomas.de>
*
****************************************************************************/

#include <pgmspace.h>
#include "types.h"
#include "vars.h"

#include "TerminalDriver.h"


/*** Send escape sequence start ***/
static inline void send_esc(void)
{
    Term_Send( 27 );       \
    Term_Send( '[' );
}

//***************************
// Convert byte to 3 ASCII digits and send
//***************************
void Term_Send_Value_as_Digits( unsigned char value )
{
    unsigned char digit;
    
    digit = '0';
    while( value >= 100 )                // Still larger than 100 ?
    {
        digit++;                         // Increment first digit
        value -= 100;
    }
    
    Term_Send( digit );                  // Send first digit
    
    digit = '0';
    while( value >= 10 )                 // Still larger than 10 ?
    {
        digit++;                         // Increment second digit
        value -= 10;
    }
    
    Term_Send( digit );                  // Send second digit
    
    Term_Send( '0' + value );            // Send third digit
}


//***************************
// Initialize UART Terminal
//***************************
void Term_Initialise()
{
    Term_Set_Display_Attribute_Mode( MODE_NONE ); // Disable all previous modes
    Term_Erase_Screen();                          // Clear screen
    Term_Set_Cursor_Position( 1, 1 );             // Move to top-left corner
}


//****************************
// Transmit one byte
//****************************
void Term_Send( unsigned char data )
{
    putch(data);
}


//***************************
// Receive one byte
//***************************
/*unsigned char Term_Get()
{
	unsigned int d;
	
    while( ( d = uart_getc() ) == UART_NO_DATA  );        // Wait for receive complete
   
    return ( (uint8_t) d ) ;                    // Return byte
}*/


//***************************
// Decode incoming ESC sequence
//***************************
unsigned int Term_Get_Sequence()
{
  //  unsigned char val;
    unsigned int ret;
    
   char c;
   static u8 cmdlen = 0;
  // static u8 Esc1Bstate = 0;

   if (cmdlen >= MAX_TEXT_INPUT_LEN)
   {
        outDataRX = inDataRX;
        cmdlen = 0;
        return 0;
   }
   if (inDataRX==outDataRX)
      return 0;
   c = rxData[outDataRX++];
   outDataRX &= RX_BUF_MASK;
    
    //val = Term_Get();
    if( c != 27 )                      // Received ESC ?
    {
        ret = c;                       // If not, return char
    }
    else
    {
        //val = Term_Get();
        c = rxData[outDataRX++];
        outDataRX &= RX_BUF_MASK;
        if( c != '[' )                 // Received '[' ?
        {
            ret = c;                   // If not, return char
        }
        else
        {
            //val = Term_Get();
           c = rxData[outDataRX++];
           outDataRX &= RX_BUF_MASK;
            
            if( c == 'A' ||
                c == 'B' ||
                c == 'C' ||
                c == 'D' )             // Arrow keys ?
            {
                ret = c << 8;          // Put code in upper byte
            }
            else
            {
                ret = c;               // If not, return char
            }
        }
    }
    if ((c == 0x0d)||(c == 0x0a))
   {
     ;
   }
   else
   {
     cmdlen++;
   }   
    return ret;
}


//***************************
// Transmit string from Flash
//
// Returns byte count
//***************************
unsigned char Term_Send_FlashStr( const unsigned char * str )
{
    unsigned char count = 0;            // Initialize byte counter
	unsigned char c;

    while( ( c = *str )  != 0 )  // Reached zero byte ?
    {
        Term_Send( c );
        str++;                          // Increment ptr
        count++;                        // Increment byte counter
    }    
    
    return count;                       // Return byte count
}


//***************************
// Transmit string from SRAM
//
// Returns byte count
//***************************
unsigned char Term_Send_RAMStr( unsigned char * str )
{
    unsigned char count = 0;            // Initialize byte counter

    while( *str != 0 )                  // Reached zero byte ?
    {
        Term_Send( *str );
        str++;                          // Increment ptr
        count++;                        // Increment byte counter
    }    
    
    return count;                       // Return byte count
}


//***************************
// Send 'clear bottom of screen' sequence
//***************************
void Term_Erase_ScreenBottom()
{
    send_esc();                            // Send escape sequence start
    
    Term_Send( 'J' );
}


//***************************
// Send 'clear top of screen' sequence
//***************************
void Term_Erase_ScreenTop()
{
    send_esc();                             // Send escape sequence start
    
    Term_Send( '1' );
    Term_Send( 'J' );
}


//***************************
// Send 'clear screen' sequence
//***************************
void Term_Erase_Screen()
{
    send_esc();                             // Send escape sequence start
    
    Term_Send( '2' );
    Term_Send( 'J' );
}


//***************************
// Send 'clear end of line' sequence
//***************************
void Term_Erase_to_End_of_Line()
{
    send_esc();                             // Send escape sequence start
    
    Term_Send( 'K' );
}


//***************************
// Send 'clear start of line' sequence
//***************************
void Term_Erase_to_Start_of_Line()
{
    send_esc();                             // Send escape sequence start
    
    Term_Send( '1' );
    Term_Send( 'K' );
}


//***************************
// Send 'clear line' sequence
//***************************
void Term_Erase_Line()
{
    send_esc();                             // Send escape sequence start
    
    Term_Send( '2' );
    Term_Send( 'K' );
}


//***************************
// Set text mode
//***************************
void Term_Set_Display_Attribute_Mode( unsigned char mode )
{
    send_esc();                             // Send escape sequence start
    
    Term_Send( mode );
    Term_Send( 'm' );
}


//***************************
// Set text colour
//***************************
void Term_Set_Display_Colour( unsigned char fg_bg, unsigned char colour )
{
    send_esc();                             // Send escape sequence start
    
    Term_Send( fg_bg );                 // Select foreground/background
    Term_Send( colour );
    Term_Send( 'm' );
}


//***************************
// Set cursor position
//
// Top-left is (1,1)
//***************************
void Term_Set_Cursor_Position( unsigned char row, unsigned char column )
{
    send_esc();                                    // Send escape sequence start
    
    Term_Send_Value_as_Digits( row );              // Convert row byte
    Term_Send( ';' );
    Term_Send_Value_as_Digits( column );           // Convert column byte
    Term_Send( 'H' );
}


//***************************
// Move cursor
//***************************
void Term_Move_Cursor( unsigned char distance, unsigned char direction )
{
    send_esc();                             // Send escape sequence start
    
    Term_Send_Value_as_Digits( distance );         // Convert distance byte

    Term_Send( direction );
}



//***************************
// Save cursor position
//***************************
void Term_Save_Cursor_Position()
{
    send_esc();                             // Send escape sequence start
    
    Term_Send( 's' );
}


//***************************
// Restore cursor position
//***************************
void Term_Restore_Cursor_Position()
{
    send_esc();                             // Send escape sequence start
    
    Term_Send( 'u' );
}


//***************************
// Enable scroll for entire screen
//***************************
void Term_Set_Scroll_Mode_All()
{
    send_esc();                             // Send escape sequence start
    
    Term_Send( 'r' );
}


//***************************
// Limit screen scrolling to some lines only
//***************************
void Term_Set_Scroll_Mode_Limit( unsigned char start, unsigned char end )
{
    send_esc();                                    // Send escape sequence start
    
    Term_Send_Value_as_Digits( start );            // Convert start line byte
    Term_Send( ';' );
    Term_Send_Value_as_Digits( end );              // Convert end line byte
    Term_Send( 'r' );
}


//***************************
// Send 'print screen' command sequence
//***************************
void Term_Print_Screen()
{
    send_esc();                             // Send escape sequence start
   
    Term_Send( 'i' );
}


//***************************
// Draw frame on terminal client
//***************************
void Term_Draw_Frame( unsigned char top, unsigned char left, 
                      unsigned char height, unsigned char width,
                      unsigned char doubleFrame )
{
    /*** Defines egde character codes for both single and double frames ***/
    __flash static unsigned char edges[] = { 0xda, 0xbf, 0xc0, 0xd9, 0xc4, 0xb3,
                                             0xc9, 0xbb, 0xc8, 0xbc, 0xcd, 0xba };
    // mt: this array may be kept in SRAM (just 12 Bytes)

    unsigned char i = 0;
    height++;
    width++;    
    
    /*** Draw frame ***/
    Term_Set_Cursor_Position( top, left );                // Corners first
    Term_Send(edges[ doubleFrame * 6 + 0 ]);
    
    Term_Set_Cursor_Position( top, left + width );
    Term_Send(edges[ doubleFrame * 6 + 1 ] );
    
    Term_Set_Cursor_Position( top + height, left );
    Term_Send( edges[ doubleFrame * 6 + 2 ] );
    
    Term_Set_Cursor_Position( top + height, left + width );
    Term_Send(edges[ doubleFrame * 6 + 3 ] );
    
    for( i = left + 1; i < left + width; i++ )           // Top and bottom edges
    {
        Term_Set_Cursor_Position( top, i );
        Term_Send(edges[ doubleFrame * 6 + 4 ] );
        
        Term_Set_Cursor_Position( top + height, i );
        Term_Send(edges[ doubleFrame * 6 + 4 ] );
    }
    
    for( i = top + 1; i < top + height; i++ )            // Left and right edges
    {
        Term_Set_Cursor_Position( i, left );
        Term_Send( edges[ doubleFrame * 6 + 5 ] );
        
        Term_Set_Cursor_Position( i, left + width );
        Term_Send(edges[ doubleFrame * 6 + 5 ] );
    }
}


//***************************
// Draw menu on terminal client
//***************************
unsigned char Term_Draw_Menu( const unsigned char * menu, unsigned char selectPos,
                              unsigned char top, unsigned char left, unsigned char doubleFrame )
{
    unsigned char i, width, height;
    const unsigned char  * ptr = menu;
	unsigned char c;
    
    width = height = 0;
    
    while( *ptr != 0 )   // Scan through menu string
    {
        height++;                               // Keep track of item count

        if( selectPos == height )
        {
          Term_Set_Display_Attribute_Mode( MODE_REVERSED );  // Reverse selected item
        }
        else
        {
          Term_Set_Display_Attribute_Mode(MODE_NONE   );
        }
    
        Term_Set_Cursor_Position( top + height, left + 1 );   // Start of item text
        
        i = 0;
        
        while( ( c =*ptr ) != '\n' ) // Scan through item text
        {
            Term_Send( c );                  // Print item character
            i++;                             // Item character count
            ptr++;
        }
        
        ptr++;                                  // Skip newline character
        
        if( i > width )
            width = i;                          // Always keep max width
    }
    
    Term_Set_Display_Attribute_Mode( MODE_NONE );
    if( selectPos == 0 )                        // Draw frame only if selectPos == 0
    {
        Term_Draw_Frame( top, left, height, width, doubleFrame );        
    }
    
    Term_Set_Cursor_Position( top + selectPos, left + 1 );    // Postition at start of selected item
    return height;
}


//***************************
// Handle menu
//***************************
unsigned char Term_Handle_Menu( const unsigned char * menu, unsigned char selectPos,
                                unsigned char top, unsigned char left, unsigned char doubleFrame )
{
    unsigned char height;
    unsigned int ret;
        
    /* Print menu frame */
    height = Term_Draw_Menu( menu, 0, top, left, doubleFrame );
    
    while(1)
    {
        /* Print menu text with selected item reversed */
        Term_Draw_Menu( menu, selectPos, top, left, doubleFrame );
        
        ret = Term_Get_Sequence();             // Decode ESC sequence
        
        if( ret == 13 )                        // Exit on ENTER
            return selectPos;
            
        if( (ret & 0xff) == 0 )                // Arrow key ?
        {
            ret >>= 8;
            
            if( ret == MOVE_UP )
            {
                selectPos--;                   // Move selection up, with wrap
                if( selectPos < 1 )
                    selectPos = height;
            } else if( ret == MOVE_DOWN )
            {
                selectPos++;                   // Move selection down, with wrap
                if( selectPos > height )
                    selectPos = 1;
            }
        }
    }
}

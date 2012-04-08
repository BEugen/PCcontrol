/*************************************************************************
Title:     UART addon-library 
Author:    Martin Thomas <eversmith@heizung-thomas.de>   
           http://www.siwawi.arubi.uni-kl.de/avr_projects
Software:  AVR-GCC 3.3/3.4, Peter Fleury's UART-Library

DESCRIPTION:
    
USAGE:
    Refere to the header file uart_addon.h for a description of the routines. 
                    
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ioavr.h>
#include <intrinsics.h>
#include "usart.h"


/*************************************************************************
Function: uart_puti()
Purpose:  transmit integer as ASCII to UART
Input:    integer value
Returns:  none
**************************************************************************/
void uart_puti( const int val )
{
    char buffer[sizeof(int)*8+1];
    sprintf(buffer,"%d",val);
    putchrs((unsigned char const *)buffer, sizeof(int)*8+1 );

} /* uart_puti */


/*************************************************************************
Function: uart_puthex_nibble()
Purpose:  transmit lower nibble as ASCII-hex to UART
Input:    byte value
Returns:  none
**************************************************************************/
void uart_puthex_nibble(const unsigned char b)
{
    unsigned char  c = b & 0x0f;
    if (c>9) c += 'A'-10;
    else c += '0';
    putch(c);
} /* uart_puthex_nibble */

/*************************************************************************
Function: uart_puthex_byte()
Purpose:  transmit upper and lower nibble as ASCII-hex to UART
Input:    byte value
Returns:  none
**************************************************************************/
void uart_puthex_byte(const unsigned char  b)
{
    uart_puthex_nibble(b>>4);
    uart_puthex_nibble(b);
} /* uart_puthex_byte */

/*************************************************************************
Function: uart_putbin_byte()
Purpose:  transmit byte as ASCII-bin to UART
Input:    byte value
Returns:  none
**************************************************************************/
void uart_putbin_byte(const unsigned char b)
{
    signed char i;
	for (i=7;i>=0;i--) {
		if (b & (1<<i)) {
			putch('1');
		}
		else {
			putch('0');
		}
	}
} /* uart_putbin_byte */

#include <ioavr.h>
#include "usart.h"
#include "types.h"
#include "vars.h"



void  putch(unsigned char byte) 
{
 
    while(!(UCSRA &(1<< UDRE)))
          continue;
    UDR = byte;
}

void  putchrs(const unsigned char *byte, unsigned int count)
{
  unsigned int i = 0;
  while(count--)
  {
     putch(byte[i++]);
  }
}

#pragma vector=USART_RXC_vect
__interrupt void UsartReceiv()
{
    rxData[inDataRX++] = UDR;
    inDataRX &= RX_BUF_MASK;
}

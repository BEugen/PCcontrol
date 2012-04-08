#include	"delay.h"
#include <intrinsics.h>

void DelayMs(unsigned int x)
{ 
  x = x*399*10;
  while(x-- > 0)
  {
    Delay2dot5Us();
  }
}
void Delay2dot5Us()
{
  __delay_cycles(1);
}

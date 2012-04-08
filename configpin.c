#include "configpin.h"
#include <ioavr.h>
#include <intrinsics.h>
#include "vars.h"

void PinInit(void)
{
   //сконфигурируем ножку на выход
   OUTPUT_PORT |= ((1<<POWER_BIT)|(1<<RESET_BIT));
   //сконфигурируем ножку на вход
   INP_INT_PORT &= ~((1<<FAN1)|(1<<FAN2));
   //включим подт€гивающий резистор
   OUT_INT_PORT |= ((1<<FAN1)|(1<<FAN2));
   //прерывание по порту INT0 и INT2 спадающий фронт
   MCUCR |= ((1<<ISC01)|(1<<ISC11));
   GICR |= ((1<<INT1) | (1<<INT2));
}


#pragma vector=INT0_vect
__interrupt void Int0Inter()
{
  FanCounter1++;
}

#pragma vector=INT1_vect
__interrupt void Int1Inter()
{
  FanCounter2++;
}


/*#pragma vector=INT2_vect
__interrupt void Int2Inter()
{
  FanCounter3++;
}*/



#ifndef TIMER_H
#include <ioavr.h>
#include <intrinsics.h>
#define TIMER_H
#define COUNT_TIME_INTERVAL 3
#define INITIAL_TIMER 0x7C
#define INIT_DELITEL 0x03

 #define bitset(var, bitno) ((var) |= 1<< (bitno))
 #define bitclr(var, bitno) ((var) &= ~(1 << (bitno)))
 #define bittst(var, bitno) (var & (1 << bitno)) != 0? 1 : 0

struct TIME_ELAPSED
{
  unsigned int time;
  unsigned int interval;
  unsigned char flag;
  unsigned char type;
};

void InitTimer0(void);
unsigned char CheckTimeElapsed(struct TIME_ELAPSED * time_elapsed);
unsigned char CheckTimeElapsedNoStart(struct TIME_ELAPSED * time_elapsed);
unsigned int ReturnDeltaTimerElapsed(struct TIME_ELAPSED * time_elapsed);

#endif
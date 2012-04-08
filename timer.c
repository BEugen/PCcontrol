#include <ioavr.h>
#include <intrinsics.h>
#include "timer.h"
#include "configpin.h"

static unsigned int time_interval[COUNT_TIME_INTERVAL];

void InitTimer0()
{
    TCCR0 = INIT_DELITEL;
    OCR0 = INITIAL_TIMER;
    TCNT0 = 0x00;
    bitset(TIMSK, OCIE0);
}


#pragma vector=TIMER0_COMP_vect
__interrupt void Timer0Els_COMP()
{
  
  time_interval[0]++;
  if((unsigned int)(time_interval[0] - time_interval[2]) >=500)
  {
    time_interval[2] = time_interval[0];
    time_interval[1]++;
    REVERSE_TEST();
  } 
  TCNT0 = 0x00;
}

unsigned char CheckTimeElapsed(struct TIME_ELAPSED * time_elapsed)
{
  if(time_elapsed -> type < COUNT_TIME_INTERVAL)
  {
    if(time_elapsed -> flag == 0)
    {
      time_elapsed -> time = time_interval[time_elapsed -> type];
      time_elapsed -> flag = 1;
    }
    else
    {
      if((unsigned int)(time_interval[time_elapsed -> type] - time_elapsed -> time) >= time_elapsed -> interval)
      {
        time_elapsed -> flag = 2;
      }
    }
  }
  return time_elapsed -> flag;
}

unsigned char CheckTimeElapsedNoStart(struct TIME_ELAPSED * time_elapsed)
{
  if((unsigned int)(time_interval[time_elapsed -> type] - time_elapsed -> time) >= time_elapsed -> interval && time_elapsed -> flag == 1)
  {
        time_elapsed -> flag = 2;
        return time_elapsed -> flag;
  }
  return time_elapsed -> flag;
}

unsigned int ReturnDeltaTimerElapsed(struct TIME_ELAPSED * time_elapsed)
{
  if(time_elapsed -> flag > 0)
  {
    return (unsigned int)(time_interval[time_elapsed -> type] - time_elapsed -> time);
  }
  return 0;
}

/*interrupt [TIMER0_OVF_vect] void counter(void) //overflow interrupt vector
{ 
    
    if (++t.second==60)        //keep track of time, date, month, and year
    {
        t.second=0;
        if (++t.minute==60) 
        {
            t.minute=0;
            if (++t.hour==24)
            {
                t.hour=0;
                if (++t.date==32)
                {
                    t.month++;
                    t.date=1;
                }
                else if (t.date==31) 
                {                    
                    if ((t.month==4) || (t.month==6) || (t.month==9) || (t.month==11)) 
                    {
                        t.month++;
                        t.date=1;
                    }
                }
                else if (t.date==30)
                {
                    if(t.month==2)
                    {
                       t.month++;
                       t.date=1;
                    }
                }              
                else if (t.date==29) 
                {
                    if((t.month==2) && (not_leap()))
                    {
                        t.month++;
                        t.date=1;
                    }                
                }                          
                if (t.month==13)
                {
                    t.month=1;
                    t.year++;
                }
            }
        }
    }  
    PORTB=~(((t.second&0x01)|t.minute<<1)|t.hour<<7); 


}  
 
char not_leap(void)      //check for leap year
{
    if (!(t.year%100))
        return (char)(t.year%400);
    else
        return (char)(t.year%4);
} */        
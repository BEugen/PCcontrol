#ifndef __TYPES__
#define __TYPES__


#define u8 unsigned char
#define u16 unsigned int
#define u32 uint32_t
#define false 0
#define true  1

#define bit_is_set(var, bitno) ((var) |= 1<< (bitno))
#define bit_is_clear(var, bitno) ((var) &= ~(1 << (bitno)))
#define bit_is_tst(var, bitno) (var & (1 << bitno)) != 0? 1 : 0

#define PSTR(s) s

typedef signed char 	int8_t;
typedef unsigned char 	uint8_t;
typedef signed int 	int16_t;
typedef unsigned int 	uint16_t;
typedef signed long int 	int32_t;
typedef unsigned long int 	uint32_t;
typedef signed long long int 	int64_t;
typedef unsigned long long int 	uint64_t;


typedef struct _parametrs
{ 
  unsigned char id0[8];
  unsigned char id1[8];
  char name0[21];
  char name1[21];
  char timeWaitOffImm;
  char timeWaitOffSafety;
  char timeWatchdogToReset;
  char countWatchdogReset;
  char enableWatchdogReset;
  float upAlarmId[2];
  float fan1Div;
  float fan2Div;
  float fan3Div;
  unsigned int lolimFan[3];
}Parametrs;

typedef struct _values
{
   float tValue[2];
   char usbStatus;
   char powerStatus;
   char powerGoodStatus;
   char relayStatus;
   char countMakeReset;
   char flag; 
   unsigned int Counter;
   unsigned int oldCounter;
   unsigned int Fan[3]; 
}Values;
/*
flag
bit 0 - fan1 low
bit 1 - fan2 low
bit 2 - fan3 low
bit 3 - temp1 high
bit 4 - temp2 high
*/
typedef struct _command
{
   char powerOffImmediatly;
   char powerOffSafety;
   char resetPC;
   char usbOffOn;
   char relayOffOn;
   char logView;
   char resetDevice;
}Command;

typedef struct _events
{
  
  char powerOkEvent;
  char powerEvent;
  char resetEvent;
  char usbLoadEvent;
  char relayEvent;
  char fanEvent;
  char temperatureEvent;
}Event;

typedef struct _eventstore
{
  unsigned char codeByte;
  unsigned char date;
  unsigned char month;
  unsigned int year;
  unsigned char hour;
  unsigned char minute;
  unsigned char second;
  unsigned int eventnumber;
  float value;
}EventStore;

typedef struct _time{ 
unsigned char second;   
unsigned char minute;
unsigned char hour;                                     
unsigned char date;       
unsigned char month;
unsigned int year;      
            }Time;

#endif  //__TYPES__

#include "events.h"
#include "common_files\OWIcrc.h"
#include "configpin.h"
#include "vars.h"
#include "types.h"


void CheckEvents()
{
  for(unsigned char i = 0; i < 3; i++)
  {
    if(!bit_is_tst(eventGroup.fanEvent, i) && bit_is_tst(valGroup.flag, i))
    {
      bit_is_set(eventGroup.fanEvent, i);
      TimeToEvent();
      eventstoreGroup.eventnumber = i;
      eventstoreGroup.value = valGroup.Fan[i];
    }
    if(!bit_is_tst(valGroup.flag, i))
    {
      bit_is_clear(eventGroup.fanEvent, i);
     }
  }
  if(!bit_is_tst(eventGroup.temperatureEvent, 0) && bit_is_tst(valGroup.flag, 3))
  {
      bit_is_set(eventGroup.temperatureEvent, 0);
      TimeToEvent();
      eventstoreGroup.eventnumber = E_TEMP1;
      eventstoreGroup.value = valGroup.tValue[0];
  }
  if(!bit_is_tst(valGroup.flag, 3))
  {
      bit_is_clear(eventGroup.temperatureEvent, 0);
  }
  if(!bit_is_tst(eventGroup.temperatureEvent, 1) && bit_is_tst(valGroup.flag, 4))
  {
      bit_is_set(eventGroup.temperatureEvent, 1);
      TimeToEvent();
      eventstoreGroup.eventnumber = E_TEMP2;
      eventstoreGroup.value = valGroup.tValue[1];
  }
  if(!bit_is_tst(valGroup.flag, 4))
  {
      bit_is_clear(eventGroup.temperatureEvent, 1);
  }
  if(!eventGroup.powerOkEvent && !IN_POWER_GOOD()) //power good to 0
  {
    eventGroup.powerOkEvent = 0x01;
    TimeToEvent();
    eventstoreGroup.eventnumber = E_POWERGOOD;
    eventstoreGroup.value = 0.0; 
  }
  if(eventGroup.powerOkEvent && IN_POWER_GOOD()) //power good to 1
  {
    eventGroup.powerOkEvent = 0x00;
    TimeToEvent();
    eventstoreGroup.eventnumber = E_POWERGOOD;
    eventstoreGroup.value = 1.0; 
  }
  if(eventGroup.usbLoadEvent)
  {
    eventGroup.usbLoadEvent = 0x00;
    TimeToEvent();
    eventstoreGroup.eventnumber = E_USBLOAD;
    eventstoreGroup.value = USB()? 1.0 : 0.0;
  }
  if(eventGroup.relayEvent)
  {
    eventGroup.relayEvent = 0x00;
    TimeToEvent();
    eventstoreGroup.eventnumber = E_RELAY;
    eventstoreGroup.value = RELAY()? 1.0 : 0.0;
  }
  if(eventGroup.powerEvent == 0x01)
  {
    TimeToEvent();
    eventstoreGroup.eventnumber = E_USERPOWER;
    eventstoreGroup.value = 0.0;
  }
  if(eventGroup.powerEvent == 0x02)
  {
    eventGroup.powerEvent = 0x00;
    TimeToEvent();
    eventstoreGroup.eventnumber = E_POWER;
    eventstoreGroup.value = 0.0;
  }
  if(eventGroup.powerEvent == 0x03)
    eventGroup.powerEvent = 0x00;
  
  if(eventGroup.resetEvent == 0x01)
  {
    TimeToEvent();
    eventstoreGroup.eventnumber = E_USERRESET;
    eventstoreGroup.value = 0.0;
  }
  if(eventGroup.resetEvent == 0x02)
  {
    eventGroup.resetEvent = 0x00;
    TimeToEvent();
    eventstoreGroup.eventnumber = E_RESET;
    eventstoreGroup.value = 0.0;
  }
  if(eventGroup.resetEvent == 0x03)
    eventGroup.resetEvent = 0x00;
  //TODO ALL Store Events to EEPROM
}

void TimeToEvent()
{
   eventstoreGroup.codeByte = 'D'^'S';
   eventstoreGroup.date = timeGroup.date;
   eventstoreGroup.month = timeGroup.month;
   eventstoreGroup.year = timeGroup.year;
   eventstoreGroup.hour = timeGroup.hour;
   eventstoreGroup.minute = timeGroup.minute;
   eventstoreGroup.second = timeGroup.second;
}
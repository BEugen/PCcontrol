#ifndef _EVENTS_H_
#define _EVENTS_H_

  enum EventType {E_FAN1, E_FAN2, E_FAN3, E_TEMP1, E_TEMP2, 
                  E_POWERGOOD, E_RESET, E_POWER, 
                  E_USERPOWER, E_USERRESET, E_USBLOAD, E_RELAY};
  void CheckEvents();
  void TimeToEvent();
#endif
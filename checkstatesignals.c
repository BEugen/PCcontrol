#include <ioavr.h>
#include "checkstatesignals.h"
#include "vars.h"
#include "configpin.h"
#include "timer.h"




struct TIME_ELAPSED FanCalcTimeout;
struct TIME_ELAPSED TemeratureSenseTimeout;

OWI_device allDevices[MAX_DEVICES];
unsigned char rom[8];

void InitFanControl()
{
   FanCalcTimeout.interval = 35;
   FanCalcTimeout.type = 1;
   FanCalcTimeout.flag = 0;
   
   TemeratureSenseTimeout.interval = 10;
   TemeratureSenseTimeout.type = 1;
   TemeratureSenseTimeout.flag = 0;
}
void CheckSateSignals(Values * values)
{
     unsigned int timeElapsed = 0;
     float temperature = 0.0f;
     static unsigned char searchFlag = SEARCH_SENSORS;
     unsigned char crcFlag = 0;
     unsigned char num = 0;
     float coeffFan =0;
  
     values -> powerStatus = IN_POWER();
     values -> powerGoodStatus = IN_POWER_GOOD();
     if(CheckTimeElapsed(&FanCalcTimeout) == 2)
     {
       timeElapsed = ReturnDeltaTimerElapsed(&FanCalcTimeout);
       if(timeElapsed != 0)
       {
         coeffFan = parmGroup.fan1Div > 0? 60.0/parmGroup.fan1Div : 60.0;
         values -> Fan[0] = (unsigned int)(FanCounter1 * coeffFan / timeElapsed);
         coeffFan = parmGroup.fan2Div > 0? 60.0/parmGroup.fan2Div : 60.0;
         values -> Fan[1] = (unsigned int)(FanCounter2 * coeffFan / timeElapsed);
       }
       FanCalcTimeout.flag = 0;
       CheckTimeElapsed(&FanCalcTimeout);
       FanCounter1 = 0;
       FanCounter2 = 0;
     }
     if(CheckTimeElapsed(&TemeratureSenseTimeout) == 2)
     {
       if (searchFlag == SEARCH_SENSORS)
       {
         num = 0;
         crcFlag = OWI_SearchDevices(allDevices, MAX_DEVICES, BUS, &num);
         if ((num == MAX_DEVICES)&&(crcFlag != SEARCH_CRC_ERROR))
         {
            searchFlag = SENSORS_FOUND;  
          }
       }
           
       crcFlag = DS18B20_ReadTemperature(BUS, allDevices[0].id, &temperature);
       if (crcFlag != READ_CRC_ERROR)
       { 
         values -> tValue[0] = temperature;
       }
       else
       {
           searchFlag = SEARCH_SENSORS;
       }
       
       crcFlag = DS18B20_ReadTemperature(BUS, allDevices[1].id, &temperature);
       if (crcFlag != READ_CRC_ERROR)
       { 
          values -> tValue[1] = temperature;
       }
       else
       {
          searchFlag = SEARCH_SENSORS;
       }
       TemeratureSenseTimeout.flag = 0;
     }
     
     if(valGroup.tValue[0] >= parmGroup.upAlarmId[0])
     {
       bit_is_set(valGroup.flag, 3);
     }
     else
     {
       bit_is_clear(valGroup.flag, 3);
     }
     if(valGroup.tValue[1] >= parmGroup.upAlarmId[1])
     {
       bit_is_set(valGroup.flag, 4);
     }
     else
     {
       bit_is_clear(valGroup.flag, 4);
     }
     for(unsigned char i =0; i < 3; i++)
     {
       if(valGroup.Fan[i] <= parmGroup.lolimFan[i])
       {
        bit_is_set(valGroup.flag, i);
       }
       else
       {
        bit_is_clear(valGroup.flag, i);
       }
     }
}


unsigned char DS18B20_ReadTemperature(unsigned char bus, unsigned char * id, float * temperature)
{
    unsigned char scratchpad[9];
    unsigned char i;
    int temp;

    OWI_DetectPresence(bus);
    OWI_MatchRom(id, bus);
    OWI_SendByte(DS18B20_CONVERT_T ,bus);
    
    while (!OWI_ReadBit(bus));

    OWI_DetectPresence(bus);
    OWI_MatchRom(id, bus);
    OWI_SendByte(DS18B20_READ_SCRATCHPAD, bus);
    for (i = 0; i<=8; i++){
      scratchpad[i] = OWI_ReceiveByte(bus);
    }
    
    if(OWI_CheckScratchPadCRC(scratchpad) != OWI_CRC_OK){
      return READ_CRC_ERROR;
    }
    temp = scratchpad[0];
    if (scratchpad[1] > 0x80)
    {
      temp = !temp + 1;
      temp *=-1;
    }
    temp = temp>>1;   
    *temperature = temp - 0.25f + (scratchpad[7] - scratchpad[6])/(float)scratchpad[7];   
    return READ_SUCCESSFUL;
}


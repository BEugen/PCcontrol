#include "command.h"
#include "menu.h"
#include "types.h"
#include "vars.h"
#include "timer.h"
#include "configpin.h"
#include "delay.h"

struct TIME_ELAPSED ResetTimeout;
struct TIME_ELAPSED PowerOffSafetyTimeout;
struct TIME_ELAPSED PowerOffImmTimeout;
struct TIME_ELAPSED WatchdogTimeout;


void InitCommandTimers()
{
   ResetTimeout.interval = 1;
   ResetTimeout.type = 1;
   ResetTimeout.flag = 0;
   PowerOffSafetyTimeout.interval = 1;
   PowerOffSafetyTimeout.flag = 0;
   PowerOffSafetyTimeout.type = 1;
   PowerOffImmTimeout.interval = parmGroup.timeWaitOffImm * TIME_COEFF;
   PowerOffImmTimeout.flag = 0;
   PowerOffImmTimeout.type = 1;
   WatchdogTimeout.type = 1;
   WatchdogTimeout.interval = parmGroup.timeWatchdogToReset * TIME_COEFF;
   WatchdogTimeout.flag = 0;
}
void CheckCmdForExecute()
{
   if(comGroup.resetPC)
   {
      ON_RESET(); 
      if(comGroup.resetPC == 1)
      {
        DrawResOffOnScreen("Reset PC...  Please wait... ");
        comGroup.resetPC ++;
      }
      if(CheckTimeElapsed(&ResetTimeout)== 2)
      {
        OFF_RESET();
        ResetTimeout.flag = 0;
        comGroup.resetPC = 0;
        DrawMenuAll();
      }
   }
   if(comGroup.powerOffSafety)
   {     
     if(comGroup.powerOffSafety == 1)
     {
       ON_POWER();
       PowerOffSafetyTimeout.interval = parmGroup.timeWaitOffSafety * TIME_COEFF;
       PowerOffSafetyTimeout.flag = 0;
       comGroup.powerOffSafety++;
       DrawResOffOnScreen("Safety power off PC...  Please wait... ");
       DelayMs(1500);
       OFF_POWER();
     }
     if((comGroup.powerOffSafety == 2 && (CheckTimeElapsed(&PowerOffSafetyTimeout) == 2)) || IN_POWER()) //todo: add or check off input
     {
       PowerOffSafetyTimeout.flag = 0;
       comGroup.powerOffSafety = 0;
       DrawMenuAll();
     }
   }
   if(comGroup.powerOffImmediatly)
   {     
     if(comGroup.powerOffImmediatly == 1)
     {
       ON_POWER();
       PowerOffImmTimeout.interval = parmGroup.timeWaitOffImm * TIME_COEFF;
       PowerOffImmTimeout.flag = 0;
       comGroup.powerOffImmediatly++;
       DrawResOffOnScreen("Immediately power off PC...  Please wait... ");
     }
     if((comGroup.powerOffImmediatly == 2 && (CheckTimeElapsed(&PowerOffImmTimeout) == 2)) || IN_POWER()) //todo: add  or check off input
     {
       OFF_POWER();
       PowerOffImmTimeout.flag = 0;
       comGroup.powerOffImmediatly = 0;
       DrawMenuAll();
     }
   }
   if(comGroup.relayOffOn)
   {     
     if(valGroup.relayStatus)
       DrawResOffOnScreen("Relay off ...  Please wait... ");
     else
       DrawResOffOnScreen("Relay on ...  Please wait... ");
     valGroup.relayStatus = !valGroup.relayStatus;
     REVERSE_RELAY();
     comGroup.relayOffOn = 0;
     DrawMenuAll();
   }
   if(comGroup.usbOffOn)
   {     
     if(valGroup.usbStatus)
       DrawResOffOnScreen("USB load off ...  Please wait... ");
     else
       DrawResOffOnScreen("USB load on ...  Please wait... ");
     valGroup.usbStatus = !valGroup.usbStatus;
     REVERSE_USB();
     comGroup.usbOffOn = 0;
     DrawMenuAll();
   }
}

void CheckWatchdog()
{
  if(parmGroup.enableWatchdogReset)
  {
    if(CheckTimeElapsed(&WatchdogTimeout) == 2)
    {
      if(valGroup.countMakeReset == parmGroup.countWatchdogReset)
        return;
      if(valGroup.Counter == valGroup.oldCounter)
      {
        valGroup.countMakeReset++;
        comGroup.resetPC = 1;
      }
      else
      {
         valGroup.oldCounter = valGroup.Counter;
         valGroup.countMakeReset = 0;
      }
      WatchdogTimeout.flag = 0;
    }
  }
}
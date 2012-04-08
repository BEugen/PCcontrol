#ifndef _CHECK_STATE_SIGNAL_
#define _CHECK_STATE_SIGNAL_

#include "types.h"

#include "OWIPolled.h"
#include "OWIHighLevelFunctions.h"
#include "OWIBitFunctions.h"
#include "common_files\OWIcrc.h"

#define DS18B20_FAMILY_ID                0x28 
#define DS18B20_CONVERT_T                0x44
#define DS18B20_READ_SCRATCHPAD          0xbe
#define DS18B20_WRITE_SCRATCHPAD         0x4e
#define DS18B20_COPY_SCRATCHPAD          0x48
#define DS18B20_RECALL_E                 0xb8
#define DS18B20_READ_POWER_SUPPLY        0xb4


#define BUS   OWI_PIN_1

//?????????? ????????? ?? ???? 1Wire
#define MAX_DEVICES       0x02

//???? ?????? ??? ??????? ?????? ???????????
#define READ_SUCCESSFUL   0x00
#define READ_CRC_ERROR    0x01

#define SEARCH_SENSORS 0x00
#define SENSORS_FOUND 0xff

void InitFanControl();
void CheckSateSignals(Values * values);
unsigned char DS18B20_ReadTemperature(unsigned char bus, unsigned char * id, float * temperature);
#endif
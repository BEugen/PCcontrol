#include "types.h"
#include "vars.h"

u8 rxData [RX_BUF_SIZE];  
u8 inDataRX, outDataRX;
u8 txData [TX_BUF_SIZE];   
u8 inDataTX, outDataTX;
char txt_from_console[MAX_TEXT_INPUT_LEN+1];
char txtbuf[TX_BUF_SIZE];
char txvalue[TX_VALUE];
unsigned int FanCounter1;
unsigned int FanCounter2;
Parametrs parmGroup;
Values valGroup;
Command comGroup;
Event eventGroup;
Time timeGroup;
EventStore eventstoreGroup;

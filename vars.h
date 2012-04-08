#ifndef __VARS__
#define __VARS__

#include "types.h"

#define TX_BUF_SIZE 128
#define TX_BUF_MASK (TX_BUF_SIZE-1)
#define RX_BUF_SIZE 16
#define RX_BUF_MASK (RX_BUF_SIZE-1)
#define MAX_CMD_LEN 8
#define MAX_TEXT_INPUT_LEN 16
#define TX_VALUE 30

extern u8 rxData [RX_BUF_SIZE];
extern u8 inDataRX, outDataRX;
extern u8 txData [TX_BUF_SIZE];   
extern u8 inDataTX, outDataTX;
extern char txt_from_console[MAX_TEXT_INPUT_LEN+1];
extern char txtbuf[TX_BUF_SIZE];
extern char txvalue[TX_VALUE];
extern Parametrs parmGroup;
extern Values valGroup;
extern Command comGroup;
extern Event eventGroup;
extern EventStore eventstoreGroup;
extern Time timeGroup;
extern unsigned int FanCounter1;
extern unsigned int FanCounter2;

#endif // __VARS__

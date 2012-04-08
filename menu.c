#include "menu.h"
#include "TerminalDriver.h"

#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h> 
#include <ctype.h>
#include <pgmspace.h>
#include "vars.h"
#include "types.h"

enum Menustates {MEN0, MEN1, MEN2, MENA, MENB, MENC };
enum Menustates state = MEN0;
char selected = 1;

__flash char menu0_1[] = "Power ";
__flash char menu0_2[] = "Reset PC\n\n";
__flash char menu0_3[] = "Load on USB ";
__flash char menu0_4[] = "View Log\n\nSetup\n\nReset Device\n\n";
__flash char menu0_5[] = "Relay ";
unsigned char menuA[] = "Choice\n\nChoice\n\nBack\n";

void DrawHeadMenu()
{
   Term_Initialise();
   Term_Set_Display_Colour( COL_BACKGROUND, COL_BLACK  );
   Term_Set_Display_Colour( COL_FOREGROUND, COL_WHITE  );
   Term_Erase_Screen();
   Term_Draw_Frame(7,18,7,75,0);
   Term_Set_Cursor_Position(9,20);
   Term_Send_FlashStr("Temperature 1: ");
   Term_Set_Cursor_Position(11,20);
   Term_Send_FlashStr("Temperature 2: ");
   Term_Set_Cursor_Position(13,20);
   Term_Send_FlashStr("Power: ");
   Term_Set_Cursor_Position(9,48);
   Term_Send_FlashStr("Fan1: ");
   Term_Set_Cursor_Position(11,48);
   Term_Send_FlashStr("Fan2: ");
   Term_Set_Cursor_Position(13,48);
   Term_Send_FlashStr("Fan3: ");
   Term_Set_Cursor_Position(9,65);
   Term_Send_FlashStr("Heart Beat: ");
   Term_Set_Cursor_Position(11,65);
   Term_Send_FlashStr("Power good: ");
   Term_Set_Cursor_Position(13,65);
   Term_Send_FlashStr("Load on USB: ");
}

void DrawMenu()
{
    unsigned char top = 40;
    GenerateMenu01(&valGroup);
    switch(state)
    {
      case MEN0:
         top = 35;
        break;
      case MEN1:
         top = 32;
        break;
      case MEN2:
         top = 27;
        break;
    }
    
    Term_Draw_Menu((unsigned char *)txtbuf, selected, 18, 35, 0 ); 
    Term_Set_Display_Colour( COL_BACKGROUND, COL_BLACK  );
    Term_Set_Display_Colour( COL_FOREGROUND, COL_WHITE  );
    Term_Draw_Frame(top,18,1,75,0);
    Term_Set_Cursor_Position(25,20);
}

void DrawMenuAll()
{
    DrawHeadMenu();
    DrawMenu();
}
void CheckCmd()
{
  unsigned int ret;
   ret = Term_Get_Sequence();
   if(ret == 0)
   {
     outDataRX = 0;
     return;
   }
   if(ret !=13)
   {
      ret >>= 8;
      if(ret ==  MOVE_UP)
          selected-=2;
      if(ret == MOVE_DOWN)
         selected+=2;
   }
   
   switch(state)
   {
      case MEN0:
        if(selected < 1 || (selected & 0x80) == 0x80)
          selected = 0x0d;
        if(selected > 0x0d)
         selected = 1;
        if(ret == 13)
        {
          switch(selected)
          {
              case 1:
                comGroup.powerOffSafety = 1;
              break;
              case 3:
                comGroup.powerOffImmediatly = 1;
              break;
              case 5:
                comGroup.resetPC = 1;              
              break;
              case 7:
                comGroup.usbOffOn = 1;
              break; 
              case 9:
                comGroup.relayOffOn = 1;
              break;          
          }
          outDataRX = 0;
          inDataRX = 0;
          memset(rxData, 0x00, RX_BUF_SIZE); 
          break;
        }
        Term_Draw_Menu((unsigned char *)txtbuf, selected, 18, 35, 0 );
        outDataRX = 0;
        inDataRX = 0;
        memset(rxData, 0x00, RX_BUF_SIZE);         
      break;
     case MEN1:
       if(selected < 1 || (selected & 0x80) == 0x80)
          selected = 9;
        if(selected > 9)
         selected = 1;
        Term_Draw_Menu((unsigned char *)txtbuf, selected, 18, 35, 0 );
        outDataRX = 0;
        inDataRX = 0;
        memset(rxData, 0x00, RX_BUF_SIZE);   
       break;
     case MEN2:
       if(selected < 1 || (selected & 0x80) == 0x80)
          selected = 5;
        if(selected > 5)
         selected = 1;
        Term_Draw_Menu((unsigned char *)txtbuf, selected, 18, 35, 0 );
        outDataRX = 0;
        inDataRX = 0;
        memset(rxData, 0x00, RX_BUF_SIZE);   
       break;
   }
}


void DrawMenuSetup()
{
  state = MENA;
  selected = 1;
  Term_Draw_Menu(menuA, 1, 18, 35, 0 );
}

void GenerateMenu01(Values * grValues)
{
  unsigned int len = 0;
  char * start = txtbuf;
  memset(txtbuf, 0x00, TX_BUF_SIZE);
  if(grValues -> powerGoodStatus)
  {
    len = 6;
    strncpy_P(start, menu0_1, len);
    start += len;
    if(grValues -> powerStatus)
    {      
      strcat(start, "OFF (Safety)\n\n");
      start += 14;
      strncpy_P(start, menu0_1, len);
      start += len;
      strcat(start, "OFF (Immediately)\n\n");
      start += 19;
      len = 10;
      strncpy_P(start, menu0_2, len);
      start +=len;
      state = MEN0;
    }
    else
    {
       strcat(start, "ON\n\n");
       start += 4;
       state = MEN1;
    }
    len = 12;
    strncpy_P(start, menu0_3, len);
    start +=len;
    if(grValues -> usbStatus)
    {     
      strcat(start, "OFF\n\n");
      start +=5;
    }
    else
    {
       strcat(start, "ON\n\n");
       start +=4;
    }
    
    
  }
  else
  {
    state = MEN2;
  }
  len = 6;
  strncpy_P(start, menu0_5, len);
  start +=len;
  if(grValues -> relayStatus)
  {
      strcat(start, "OFF\n\n");
      start +=5;
  }
  else
  {
       strcat(start, "ON\n\n");
       start +=4;
  }
  len = 31;
  strncpy_P(start, menu0_4, len);
}


void DrawResOffOnScreen(unsigned char * str)
{
   DrawHeadMenu();
   Term_Set_Cursor_Position(18,20);
   Term_Set_Display_Colour( COL_FOREGROUND, COL_RED  );
   Term_Send_FlashStr(str);
   Term_Set_Display_Colour( COL_BACKGROUND, COL_BLACK  );
   Term_Set_Display_Colour( COL_FOREGROUND, COL_WHITE  );
   Term_Draw_Frame(20,18,1,75,0);
   Term_Set_Cursor_Position(25,20);
}

void DrawValues()
{
   memset(txvalue, 0x00, TX_VALUE);
   sprintf(txvalue, "%.2f C", valGroup.tValue[0]);
   Term_Set_Display_Colour( COL_BACKGROUND, COL_BLACK  );
   if( bit_is_tst(valGroup.flag, 3))
   {
     Term_Set_Display_Colour( COL_FOREGROUND, COL_RED  );
   }
   else
   {
     Term_Set_Display_Colour( COL_FOREGROUND, COL_WHITE  );
   }
   Term_Set_Cursor_Position(9,35);
   Term_Send_FlashStr((unsigned char *)txvalue);
   
   memset(txvalue, 0x00, TX_VALUE);
   sprintf(txvalue, "%.2f C", valGroup.tValue[1]);
   if( bit_is_tst(valGroup.flag, 4))
   {
     Term_Set_Display_Colour( COL_FOREGROUND, COL_RED  );
   }
   else
   {
     Term_Set_Display_Colour( COL_FOREGROUND, COL_WHITE  );
   }
   Term_Set_Cursor_Position(11,35);
   Term_Send_FlashStr((unsigned char *)txvalue);

   
   memset(txvalue, 0x00, TX_VALUE);
   if(valGroup.powerStatus)
   {
     strncpy(txvalue, "ON ", 3);
   }
   else
   {
     strncpy(txvalue, "OFF", 3);
   }
   Term_Set_Cursor_Position(13,27);
   Term_Set_Display_Colour( COL_FOREGROUND, COL_WHITE  );
   Term_Send_FlashStr((unsigned char *)txvalue);
   
   memset(txvalue, 0x00, TX_VALUE);
   sprintf(txvalue, "%d", valGroup.Counter);
   Term_Set_Cursor_Position(9,78);
   Term_Send_FlashStr((unsigned char *)txvalue);
   
   memset(txvalue, 0x00, TX_VALUE);
   if(valGroup.powerGoodStatus)
   {
     strncpy(txvalue, "OK", 2);
   }
   else
   {
     strncpy(txvalue, "NO", 2);
   }
   Term_Set_Cursor_Position(11,78);
   Term_Send_FlashStr((unsigned char *)txvalue);
   
   memset(txvalue, 0x00, TX_VALUE);
   if(valGroup.usbStatus)
   {
     Term_Set_Display_Colour( COL_FOREGROUND, COL_RED  );
     strncpy(txvalue, "ON ", 3);
   }
   else
   {
     Term_Set_Display_Colour( COL_FOREGROUND, COL_WHITE  );
     strncpy(txvalue, "OFF", 3);
   }
   Term_Set_Cursor_Position(13,78);
   Term_Send_FlashStr((unsigned char *)txvalue);
   
   memset(txvalue, 0x00, TX_VALUE);
   if( bit_is_tst(valGroup.flag, 0))
   {
     Term_Set_Display_Colour( COL_FOREGROUND, COL_RED  );
   }
   else 
   {
     Term_Set_Display_Colour( COL_FOREGROUND, COL_WHITE  );
   }
   Term_Set_Cursor_Position(9,55);
   sprintf(txvalue, "%d rpm", valGroup.Fan[0]);
   Term_Send_FlashStr((unsigned char *)txvalue);
   
   memset(txvalue, 0x00, TX_VALUE);
   if( bit_is_tst(valGroup.flag, 1))
   {
     Term_Set_Display_Colour( COL_FOREGROUND, COL_RED  );
   }
   else 
   {
     Term_Set_Display_Colour( COL_FOREGROUND, COL_WHITE  );
   }
   Term_Set_Cursor_Position(11,55);
   sprintf(txvalue, "%d rpm", valGroup.Fan[1]);
   Term_Send_FlashStr((unsigned char *)txvalue);
   
   memset(txvalue, 0x00, TX_VALUE);
   if( bit_is_tst(valGroup.flag, 2))
   {
     Term_Set_Display_Colour( COL_FOREGROUND, COL_RED  );
   }
   else 
   {
     Term_Set_Display_Colour( COL_FOREGROUND, COL_WHITE  );
   }
   Term_Set_Cursor_Position(13,55);
   sprintf(txvalue, "%d rpm", valGroup.Fan[2]);
   Term_Send_FlashStr((unsigned char *)txvalue);
   
   Term_Set_Display_Colour( COL_FOREGROUND, COL_WHITE  );
}
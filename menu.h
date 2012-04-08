#ifndef _MENU_H_
#define _MENU_H_

#include "vars.h"

void DrawHeadMenu();
void DrawMenu();
void CheckCmd();
void DrawMenuSetup();
void DrawMenuAll();
void DrawValues();
void DrawResOffOnScreen(unsigned char * str);
void GenerateMenu01(Values * grValues);
#endif
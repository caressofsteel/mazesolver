// -------------------------------------------------------------------------------
// Filename:            Console.h
// Author:              David Rodgers
// Course:              CS3424 :: Briana Morrison :: Spring 2008
// Assignment Number:   02
// Due Date:            February 28, 2008 @ 11:59:59pm
// -------------------------------------------------------------------------------
// Console.h: Various Utility Functions For WIN32 Console Applications
// -------------------------------------------------------------------------------

#ifndef CONSOLE_H_
#define CONSOLE_H_

#define BLINK 128

#include <cmath>
#include <windows.h>

using namespace std;

void ClearScreen();
void GotoXY(short , short);
void SetColor(short color);

#endif
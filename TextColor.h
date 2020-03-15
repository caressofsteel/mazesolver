// -------------------------------------------------------------------------------
// Filename:            TextColor.h
// Author:              David Rodgers
// Course:              CS3424 :: Briana Morrison :: Spring 2008
// Assignment Number:   02
// Due Date:            February 28, 2008 @ 11:59:59pm
// -------------------------------------------------------------------------------
// TextColor.h: Allows For Colored Console Text Using An Overloaded << Operator
// -------------------------------------------------------------------------------
// Thanks Member Remere at OTFANS.NET for code contained in this file.
// http://otfans.net/showthread.php?t=40061
// -------------------------------------------------------------------------------

#ifndef TEXTCOLOR_H_
#define TEXTCOLOR_H_

#include <windows.h>

// -----------------------------------------------------------------------
// COLORS: ENUMERATE COLOR CHOICES
// -----------------------------------------------------------------------
typedef enum
{
  sBLACK,
  sBLUE,
  sGREEN,
  sCYAN,
  sRED,
  sMAGENTA,
  sBROWN,
  sLIGHTGRAY,
  sDARKGRAY,
  sLIGHTBLUE,
  sLIGHTGREEN,
  sLIGHTCYAN,
  sLIGHTRED,
  sLIGHTMAGENTA,
  sYELLOW,
  sWHITE
} COLORS;

static int __BACKGROUND = sBLACK;
static int __FOREGROUND = sLIGHTGRAY;

// -----------------------------------------------------------------------
// ColorHandle: ALLOWS ONE LINE COLORING WITH << OPERATOR
// -----------------------------------------------------------------------
class ColorHandle
{
    public:
        int color;
        
        ColorHandle(int _color)
        {
            color = _color;
        }
        
        static void textcolor(int color)
        {
             __FOREGROUND = color;
             SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (__BACKGROUND << 4));
        }

        static void background(int color)
        {
            __BACKGROUND = color;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), __FOREGROUND + (color << 4));
        }

        static void background(ColorHandle& color)
        {
             background(color.color);
        }
};

// -----------------------------------------------------------------------
// OVERLOADED OSTREAM FOR ADDITION OF COLORED TEXT
// -----------------------------------------------------------------------
ostream& operator<<(ostream& os, ColorHandle& ch) 
{
    ColorHandle::textcolor(ch.color);
    return os;
}

// -----------------------------------------------------------------------
// COLOR DEFINITIONS FOR COLORHANDLE CLASS
// -----------------------------------------------------------------------
ColorHandle BLACK(sBLACK);
ColorHandle BLUE(sBLUE);
ColorHandle GREEN(sGREEN);
ColorHandle CYAN(sCYAN);
ColorHandle RED(sRED);
ColorHandle MAGENTA(sMAGENTA);
ColorHandle BROWN(sBROWN);
ColorHandle LIGHTGRAY(sLIGHTGRAY);
ColorHandle DARKGRAY(sDARKGRAY);
ColorHandle LIGHTBLUE(sLIGHTBLUE);
ColorHandle LIGHTGREEN(sLIGHTGREEN);
ColorHandle LIGHTCYAN(sLIGHTCYAN);
ColorHandle LIGHTRED(sLIGHTRED);
ColorHandle LIGHTMAGENTA(sLIGHTMAGENTA);
ColorHandle YELLOW(sYELLOW);
ColorHandle WHITE(sWHITE);

#endif
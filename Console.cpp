// -------------------------------------------------------------------------------
// Filename:            Console.cpp
// Author:              David Rodgers
// Course:              CS3424 :: Briana Morrison :: Spring 2008
// Assignment Number:   02
// Due Date:            February 28, 2008 @ 11:59:59pm
// -------------------------------------------------------------------------------
// Console.cpp: Various Utility Functions For WIN32 Console Applications
// -------------------------------------------------------------------------------

#include "console.h"

POINT screensize;

// -----------------------------------------------------------------------
// CLEARSCREEN: CLEAR SCREEN OF A WINDOWS OS
// -----------------------------------------------------------------------
void ClearScreen()
{
    COORD coordScreen = { 0, 0 }; 
    DWORD cCharsWritten; 
    CONSOLE_SCREEN_BUFFER_INFO csbi; 
    DWORD dwConSize; 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
  
    GetConsoleScreenBufferInfo(hConsole, &csbi); 
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y; 
    screensize.x = csbi.dwSize.X;
    screensize.y = csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten); 
    GetConsoleScreenBufferInfo(hConsole, &csbi); 
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten); 
    SetConsoleCursorPosition(hConsole, coordScreen); 
}

// -----------------------------------------------------------------------
// GOTOXY: MOVES CURSOR TO COORDINATE X,Y ON SCREEN
// X = Left\Right 
// Y = Top\Bottom
// -----------------------------------------------------------------------
void GotoXY(short x, short y)
{
    COORD point;
    if((x < 0 || x > screensize.x) || (y < 0 || y > screensize.y))
    {
        return;
    }
    
    point.X = x; 
    point.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}


// -----------------------------------------------------------------------
// SETCOLOR: ALLOWS MULTI-LINE ANSI COLORING OF TEXT
// -----------------------------------------------------------------------
void SetColor(short color)
{
    switch (color)
    {
    
        case 0:	// White on Black
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
                FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;
        
        case 1:	// Red on Black
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
                FOREGROUND_RED);
                break;
        
        case 2:	// Green on Black
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
                FOREGROUND_GREEN);
                break;
        
        case 3:	// Yellow on Black
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
                FOREGROUND_RED | FOREGROUND_GREEN);
                break;
        
        case 4:	// Blue on Black
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
                FOREGROUND_BLUE);
                break;
        
        case 5:	// Magenta on Black
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
                FOREGROUND_RED | FOREGROUND_BLUE);
                break;
        
        case 6:	// Cyan on Black
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
                FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;
        
        case 7:	// Black on Gray
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY |
                BACKGROUND_INTENSITY);
                break;
        
        case 8:	// Black on White
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY |
                FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                break;
        
        case 9:	// Red on White
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY |
                FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
                FOREGROUND_RED);
                break;
        
        case 10: // Green on White
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY |
                FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
                FOREGROUND_GREEN);
                break;
        
        case 11: // Yellow on White
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY |
                FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
                FOREGROUND_RED | FOREGROUND_GREEN);
                break;
        
        case 12: // Blue on White
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY |
                FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
                FOREGROUND_BLUE);
                break;
        
        case 13: // Magenta on White
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY |
                FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
                FOREGROUND_RED | FOREGROUND_BLUE);
                break;
        
        case 14: // Cyan on White
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY |
                FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
                FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;
        
        case 15: // White on White
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY |
                FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
                FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;

        case 16: // Grey on Black
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | 
                FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;
        
        default : // White on Black
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
                FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;
    }
}
#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "../include/myBigChars.h"
#include "../include/mySimpleComputer.h"

#define MIN_ROWS 27
#define MIN_COLS 100

#define MAIN_FG_COLOR WHITE
#define MAIN_BG_COLOR BLACK

void setColor (enum colors fg, enum colors bg);

#define setMainColor() setColor (MAIN_FG_COLOR, MAIN_BG_COLOR)

char *getBigChar (int code);

void printText (int x, int y, const char *text);
void printTitle (int x, int y, enum colors fg, enum colors bg,
                 const char *text);
void printKeys ();
void printMemory ();
void printCell (int address, enum colors fg, enum colors bg);
void printFlags (void);
void printDecodedCommand (int value);
void printAccumulator (void);
void printCounters (void);
void printTerm (int address, int input);
void printCommand (void);
void printBigCell (void);

#endif // _CONSOLE_H

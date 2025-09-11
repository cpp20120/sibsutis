#include "console.h"

#include <stdio.h>

void
setColor (enum colors fg, enum colors bg)
{
  mt_setfgcolor (fg);
  mt_setbgcolor (bg);
}

void
printMemory ()
{
  bc_box (1, 1, 61, 15, WHITE, BLACK, "Оперативная память", RED, BLACK);
  setMainColor ();

  for (int j = 0; j < MEMORY_SIZE; ++j)
    printCell (j, WHITE, BLACK);
}

void
printCell (int address, enum colors fg, enum colors bg)
{
  int value = 0;
  if (sc_memoryGet (address, &value) != -1)
    {
      mt_gotoXY (((address % 10) + 1) * 6 - 4, 2 + address / 10);

      int acc = 0;
      sc_accumulatorGet2 (&acc);
      if (acc == address)
        setColor (bg, fg);
      else
        setColor (fg, bg);

      int sign = 0, command = 0, operand = 0;
      sc_commandDecode (value, &sign, &command, &operand);
      printf ("%c", sign ? '-' : '+');

      printf ("%02X%02X", command, operand); // и тут насрал

      setMainColor ();
    }
}

void
printFlags (void)
{
  int value;

  bc_box (85, 1, 107, 3, WHITE, BLACK, "Регистр  Флагов", RED, BLACK);
  setMainColor ();

  mt_gotoXY (90, 2);
  printf ((sc_regGet (FLAG_OVERFLOW, &value) == OK && value) ? "P  " : "_  ");
  printf ((sc_regGet (FLAG_DIVISION, &value) == OK && value) ? "O  " : "_  ");
  printf ((sc_regGet (FLAG_MEMORY, &value) == OK && value) ? "M  " : "_  ");
  printf ((sc_regGet (FLAG_INTERRUPT, &value) == OK && value) ? "T  " : "_  ");
  printf ((sc_regGet (FLAG_COMMAND, &value) == OK && value) ? "E  " : "_  ");
}

void
printDecodedCommand (int value)
{
  bc_box (1, 16, 61, 18, WHITE, BLACK, "Редактируемая ячейка (формат)", RED,
          WHITE);
  setMainColor ();

  mt_gotoXY (2, 17);
  int sign = 0, command = 0, operand = 0;
  sc_commandDecode (value, &sign, &command, &operand);
  char *c = sign ? "-" : "";
  int old_value = value;
  if (sign)
    value = (~value & 0b11111111111111) + 1;
  // printf ("dec: %s%05d | oct: %s%05o | hex: %s%04X %sbin: %d", c, value, c,
  //         value, c, value, sign ? "" : "   ", sign);

  printf ("dec: %s%05d | oct: %05o | hex: %04X   bin: ", c, value, old_value,
          old_value);

  for (int i = 14; i >= 0; --i)
    printf ("%d", (old_value >> i) & 1);
}

void
printAccumulator (void)
{
  int value = 0;
  sc_accumulatorGet (&value);

  bc_box (62, 1, 84, 3, WHITE, BLACK, "Аккумулятор", RED, BLACK);
  setMainColor ();

  mt_gotoXY (64, 2);
  int sign = 0, command = 0, operand = 0;
  sc_commandDecode (value, &sign, &command, &operand);
  printf ("sc: %c", sign ? '-' : '+');
  printf ("%02X%02X hex: %04X", command, operand, value);
}

void
printCounters (void)
{
  int value = 0;
  sc_icounterGet (&value);

  bc_box (62, 4, 84, 6, WHITE, BLACK, "Счётчик команд", RED, BLACK);
  setMainColor ();

  mt_gotoXY (64, 5);
  printf ("T: %03d     IC: %03x", 0, value);
}

void
printTerm (int address, int input)
{
  static int history[5][2]
      = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
  if (address == -1)
    {
      for (int i = 0; i < 5; i++)
        {
          for (int j = 0; j < 2; j++)
            {
              history[i][0] = -1;
              history[i][1] = -1;
            }
        }
    }
  else if (address != -2)
    {
      for (int i = 0; i < 4; i++)
        {
          for (int j = 0; j < 2; j++)
            {
              history[i][0] = history[i + 1][0];
              history[i][1] = history[i + 1][1];
            }
        }
      int value;
      sc_memoryGet (address, &value);
      history[4][0] = address;
      history[4][1] = value;
    }
  else
    {
      for (int i = 0; i < 5; i++)
        {
          for (int j = 0; j < 2; j++)
            {
              history[i][0] = history[i][0];
              history[i][1] = history[i][1];
            }
        }
    }

  bc_box (67, 19, 78, 25, WHITE, BLACK, "IN--OUT", GREEN, WHITE);
  setMainColor ();

  for (int k = 0; k < 5; k++)
    {
      mt_gotoXY (68, 20 + k);
      if (history[k][0] == -1)
        {
          printf ("%03d %c %04X", 0, '>', 0);
        }
      else
        {
          int sign = 0, command = 0, operand = 0;
          sc_commandDecode (history[k][1], &sign, &command, &operand);
          printf ("%03d %c %02X%02X", history[k][0], input ? '>' : '<',
                  command, operand);
        }
    }
  mt_gotoXY (68, 500);
}

void
printKeys ()
{
  bc_box (79, 19, 107, 25, WHITE, BLACK, "Клавиши", GREEN, WHITE);
  mt_gotoXY (80, 20);
  printf ("l - load s - save i - reset");
  mt_gotoXY (80, 21);
  printf ("r - run t - step");
  mt_gotoXY (80, 22);
  printf ("ESC - выход");
  mt_gotoXY (80, 23);
  printf ("F5 - accumulator");
  mt_gotoXY (80, 24);
  printf ("F6 - instruction counter");
}

void
printCommand (void)
{
  int address;
  sc_accumulatorGet2 (&address);
  int command_value;
  sc_memoryGet (address, &command_value);

  bc_box (85, 4, 107, 6, WHITE, BLACK, "Команда", RED, BLACK);

  mt_gotoXY (91, 5);
  setMainColor ();

  int sign = 0, command = 0, operand = 0;
  sc_commandDecode (command_value, &sign, &command, &operand);
  // int command_flag = 0;
  // sc_regGet (FLAG_COMMAND, &command_flag);
  if (sc_commandValidate (command) != ERROR) // || !command_flag)
    {
      printf ("  %c %02x : %02x", sign ? '-' : '+', command, operand);
      // sc_regSet (FLAG_COMMAND, 0);
    }
  else // if (command_flag)
    {
      // sc_regSet (FLAG_COMMAND, 1);
      printf ("! %c %02x : %02x", sign ? '-' : '+', command,
              operand); // насрал
    }
}

void
printBigCell (void)
{
  bc_box (62, 7, 107, 18, WHITE, BLACK, "Редактируемая ячейка (увеличено)",
          RED, WHITE);
  mt_gotoXY (63, 17);
  setColor (BLUE, BLACK);
  int address = 0;
  sc_accumulatorGet2 (&address);
  printf (" Номер редактируемой ячейки: %03d", address);
  setMainColor ();

  int value = 0;
  sc_memoryGet (address, &value);
  int sign = 0, command = 0, operand = 0;
  sc_commandDecode (value, &sign, &command, &operand);
  mt_gotoXY (63, 8);
  if (sign)
    bc_printB (getBigChar (17), 0);
  else
    bc_printB (getBigChar (16), 0);

  for (size_t i = 0; i < 4; ++i)
    {
      if (i < 2)
        {
          // char *number = getBigChar (command % 16);
          // mt_gotoXY (63 + 8 * (i + 1), 8);
          // bc_printB (number, i+1);
          // command /= 16;
          char *number = getBigChar ((command >> (4 * (1 - i))) & 0xF);
          bc_printB (number, i + 1);
        }
      else
        {
          // char *number = getBigChar (operand % 16);
          // mt_gotoXY (63 + 8 * (i + 1), 8);
          // bc_printB (number, i+1);
          // operand /= 16;
          char *number = getBigChar ((operand >> (4 * (3 - i))) & 0xF);
          bc_printB (number, i + 1);
        } // ладно, и тут насрал
    }
}

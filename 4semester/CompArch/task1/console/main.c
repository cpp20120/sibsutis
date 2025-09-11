#include "console.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "../include/myReadkey.h"

enum Mode
{
  Quit = 0,
  Default,
  ChangeCell,
};

static int
checkTerminal ()
{
  if (!isatty (STDOUT_FILENO))
    {
      fprintf (stderr, "Ошибка: вывод не направлен в терминал.\n");
      return 1;
    }
  return 0;
}

static int
checkSize ()
{
  int rows, cols;
  if (mt_getscreensize (&rows, &cols) == -1)
    {
      fprintf (stderr, "Ошибка: невозможно определить размер экрана.\n");
      return 1;
    }

  if (rows < MIN_ROWS || cols < MIN_COLS)
    {
      fprintf (stderr, "Ошибка: размер экрана слишком мал.\n");
      return 1;
    }

  return 0;
}

void
t_func (int *cur_cell, int *x, int *y)
{
  int i = *cur_cell;
  sc_accumulatorSet2 (i);
  sc_icounterSet (i);
  int value = 0;
  sc_accumulatorGet2 (&i);
  sc_memoryGet (i, &value);
  mt_clrscr ();

  printMemory ();
  printAccumulator ();
  printCounters ();
  printCommand ();
  printFlags ();
  printBigCell ();

  printDecodedCommand (value);
  printKeys ();
  printTerm (-2, 0);
  for (int i = 0; i < 128; i++)
    {
      int command_value;
      sc_memoryGet (i, &command_value);
      int sign1 = 0, command1 = 0, operand1 = 0;
      sc_commandDecode (command_value, &sign1, &command1, &operand1);
      if (sc_commandValidate (command1) == ERROR)
        {
          sc_regSet (FLAG_COMMAND, 1);
        }
    }
  int sign = 0, command = 0, operand = 0;
  sc_commandDecode (value, &sign, &command, &operand);

  switch (command)
    {
    case 0x01:
      break;
    case 0x00:
      {
        mt_gotoXY (0, MIN_ROWS + 1);
        printf ("Ракшун Сергей ИП 314\nЖинов Никита ИП 314");
        mt_gotoXY (0, 6767);
      }
      break;
    case 0x0A:
      {
        if (operand < 0 || operand > 127)
          {
            sc_regSet (FLAG_MEMORY, 1);
          }
        else
          {
            mt_gotoXY (0, MIN_ROWS + 1);
            printf ("Введите новое значение ячейки памяти (dec): ");
            fflush (stdout);

            char input[10] = { 0 };

            struct termios oldt, newt;
            tcgetattr (STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag |= ICANON | ECHO;
            tcsetattr (STDIN_FILENO, TCSANOW, &newt);

            scanf ("%s", input);

            tcsetattr (STDIN_FILENO, TCSANOW, &oldt);

            int value1 = atoi (input);
            int address = 0;
            sc_accumulatorGet2 (&address);
            sc_memorySet (address, value1);
            printTerm (address, value1);

            mt_gotoXY (0, MIN_ROWS + 1);
            printf ("%*s", 50, " ");
          }
        break;
      }
    case 0x0B:
      {
        if (operand < 0 || operand > 127)
          {
            sc_regSet (FLAG_MEMORY, 1);
          }
        else
          {
            int value1 = 0;
            sc_memoryGet (operand, &value1);
            mt_gotoXY (0, MIN_ROWS + 1);
            printf ("%d", value1);
          }
        break;
      }
    case 0x14:
      {
        if (operand < 0 || operand > 127)
          {
            sc_regSet (FLAG_MEMORY, 1);
          }
        else
          {
            int value1 = 0;
            sc_memoryGet (operand, &value1);
            sc_accumulatorSet (value1);
          }
        break;
      }
    case 0x15:
      {
        if (operand < 0 || operand > 127)
          {
            sc_regSet (FLAG_MEMORY, 1);
          }
        else
          {
            int value1 = 0;
            sc_accumulatorGet (&value1);
            sc_memorySet (operand, value1);
          }
        break;
      }
    case 0x1E:
      {
        if (operand < 0 || operand > 127)
          {
            sc_regSet (FLAG_MEMORY, 1);
          }
        else
          {
            int value1 = 0, value2 = 0;
            sc_accumulatorGet (&value1);
            sc_memoryGet (operand, &value2);
            if (value1 + value2 > 16383 || value1 + value2 < -16384)
              {
                sc_regSet (FLAG_OVERFLOW, 1);
              }
            else
              {
                sc_accumulatorSet (value1 + value2);
              }
          }
        break;
      }
    case 0x1F:
      {
        if (operand < 0 || operand > 127)
          {
            sc_regSet (FLAG_MEMORY, 1);
          }
        else
          {
            int value1 = 0, value2 = 0;
            sc_accumulatorGet (&value1);
            sc_memoryGet (operand, &value2);
            if (value1 - value2 > 16383 || value1 - value2 < -16384)
              {
                sc_regSet (FLAG_OVERFLOW, 1);
              }
            else
              {
                sc_accumulatorSet (value1 - value2);
              }
          }
        break;
      }
    case 0x20:
      {
        if (operand < 0 || operand > 127)
          {
            sc_regSet (FLAG_MEMORY, 1);
          }
        else
          {
            int value1 = 0, value2 = 0;
            sc_accumulatorGet (&value1);
            sc_memoryGet (operand, &value2);
            if (value2 == 0)
              {
                sc_regSet (FLAG_DIVISION, 1);
              }
            else if (value1 / value2 > 16383 || value1 / value2 < -16384)
              {
                sc_regSet (FLAG_OVERFLOW, 1);
              }
            else
              {
                sc_accumulatorSet (value1 / value2);
              }
          }
        break;
      }
    case 0x21:
      {
        if (operand < 0 || operand > 127)
          {
            sc_regSet (FLAG_MEMORY, 1);
          }
        else
          {
            int value1 = 0, value2 = 0;
            sc_accumulatorGet (&value1);
            sc_memoryGet (operand, &value2);
            if (value1 * value2 > 16383 || value1 * value2 < -16384)
              {
                sc_regSet (FLAG_OVERFLOW, 1);
              }
            else
              {
                sc_accumulatorSet (value1 * value2);
              }
          }
        break;
      }
    case 0x28:
      {
        if (operand < 0 || operand > 127)
          {
            sc_regSet (FLAG_MEMORY, 1);
          }
        else
          {
            i = operand - 1;
          }
        break;
      }
    case 0x29:
      {
        if (operand < 0 || operand > 127)
          {
            sc_regSet (FLAG_MEMORY, 1);
          }
        else
          {
            int value1 = 0;
            int sign = 0, c = 0, a = 0;
            sc_commandDecode (value1, &sign, &c, &a);
            if (sign)
              {
                i = operand - 1;
              }
          }
        break;
      }
    case 0x2A:
      {
        if (operand < 0 || operand > 127)
          {
            sc_regSet (FLAG_MEMORY, 1);
          }
        else
          {
            int value1 = 0;
            sc_accumulatorGet (&value1);
            if (value1 == 0)
              {
                i = operand - 1;
              }
          }
        break;
      }
    case 0x3A:
      {
        int res = 0;
        sc_accumulatorGet (&res);
        if (operand < 0 || operand > 127)
          {
            sc_regSet (FLAG_MEMORY, 1);
          }
        else if (res % 2 == 0)
          {
            i = operand - 1;
            res = i;
          }
      }
      break;
    case 0x3B:
      {
        int res = 0;
        sc_accumulatorGet (&res);
        if (operand < 0 || operand > 127)
          sc_regSet (FLAG_MEMORY, 1);
        else if (res % 2 != 0)
          {
            i = operand - 1;
            res = i;
          }
      }
      break;
    case 0x42:
      {
        if (operand < 0 || operand > 127)
          sc_regSet (FLAG_MEMORY, 1);
        else
          {
            int s = 0, c = 0, acc_operand = 0;
            int acc = 0;
            sc_accumulatorGet (&acc);
            sc_commandDecode (acc, &s, &c, &acc_operand);

            int a = 0;
            sc_memoryGet (operand, &a);
            int b = 0;
            sc_memoryGet (acc_operand, &b);

            if (a - b > 16383 || a - b < -16384)
              {
                sc_regSet (FLAG_OVERFLOW, 1);
              }
            else
              {
                sc_accumulatorSet (a - b);
              }
          }
      }
      break;
    case 0x43:
      {
        if (operand < 0 || operand > 127)
          sc_regSet (FLAG_MEMORY, 1);
        else
          {
            int acc = 0;
            sc_accumulatorGet (&acc);
            int val = 0;
            sc_memoryGet (operand, &val);
            int r = val << acc;
            if (r > 0b111111111111111)
              {
                r &= 0b111111111111111;
                sc_regSet (FLAG_OVERFLOW, 1);
              }
            sc_accumulatorSet (r);
          }
      }
      break;
    default:
      break;
    }
  sleep (1);
  int z = (i % 12) + 1;
  int z1 = (i / 10);
  *x = z;
  *y = z1;
}

void
r_func (void)
{
  sc_regSet (FLAG_INTERRUPT, 0);
  int flag = 0;
  for (int i = 0; i < 128; i++)
    {
      sc_accumulatorSet2 (i);
      sc_icounterSet (i);
      int value = 0;
      sc_accumulatorGet2 (&i);
      sc_memoryGet (i, &value);
      if (flag == 1)
        {
          break;
        }
      mt_clrscr ();

      printMemory ();
      printAccumulator ();
      printCounters ();
      printCommand ();
      printFlags ();
      printBigCell ();

      printDecodedCommand (value);
      printKeys ();
      printTerm (-2, 0);
      for (int i = 0; i < 128; i++)
        {
          int command_value;
          sc_memoryGet (i, &command_value);
          int sign1 = 0, command1 = 0, operand1 = 0;
          sc_commandDecode (command_value, &sign1, &command1, &operand1);
          if (sc_commandValidate (command1) == ERROR)
            {
              sc_regSet (FLAG_COMMAND, 1);
            }
        }
      int sign = 0, command = 0, operand = 0;
      sc_commandDecode (value, &sign, &command, &operand);

      switch (command)
        {
        case 0x01:
          break;
        case 0x00:
          {
            mt_gotoXY (0, MIN_ROWS + 1);
            printf ("Ракшун Сергей ИП 314\nЖинов Никита ИП 314");
            mt_gotoXY (0, 6767);
          }
          break;
        case 0x0A:
          {
            if (operand < 0 || operand > 127)
              {
                sc_regSet (FLAG_MEMORY, 1);
              }
            else
              {
                mt_gotoXY (0, MIN_ROWS + 1);
                printf ("Введите новое значение ячейки памяти (dec): ");
                fflush (stdout);

                char input[10] = { 0 };

                struct termios oldt, newt;
                tcgetattr (STDIN_FILENO, &oldt);
                newt = oldt;
                newt.c_lflag |= ICANON | ECHO;
                tcsetattr (STDIN_FILENO, TCSANOW, &newt);

                scanf ("%s", input);

                tcsetattr (STDIN_FILENO, TCSANOW, &oldt);

                int value1 = atoi (input);
                int address = 0;
                sc_accumulatorGet2 (&address);
                sc_memorySet (address, value1);
                printTerm (address, value1);

                mt_gotoXY (0, MIN_ROWS + 1);
                printf ("%*s", 50, " ");
              }
            break;
          }
        case 0x0B:
          {
            if (operand < 0 || operand > 127)
              {
                sc_regSet (FLAG_MEMORY, 1);
              }
            else
              {
                int value1 = 0;
                sc_memoryGet (operand, &value1);
                mt_gotoXY (0, MIN_ROWS + 1);
                printf ("%d", value1);
              }
            break;
          }
        case 0x14:
          {
            if (operand < 0 || operand > 127)
              {
                sc_regSet (FLAG_MEMORY, 1);
              }
            else
              {
                int value1 = 0;
                sc_memoryGet (operand, &value1);
                sc_accumulatorSet (value1);
              }
            break;
          }
        case 0x15:
          {
            if (operand < 0 || operand > 127)
              {
                sc_regSet (FLAG_MEMORY, 1);
              }
            else
              {
                int value1 = 0;
                sc_accumulatorGet (&value1);
                sc_memorySet (operand, value1);
              }
            break;
          }
        case 0x1E:
          {
            if (operand < 0 || operand > 127)
              {
                sc_regSet (FLAG_MEMORY, 1);
              }
            else
              {
                int value1 = 0, value2 = 0;
                sc_accumulatorGet (&value1);
                sc_memoryGet (operand, &value2);
                if (value1 + value2 > 16383 || value1 + value2 < -16384)
                  {
                    sc_regSet (FLAG_OVERFLOW, 1);
                  }
                else
                  {
                    sc_accumulatorSet (value1 + value2);
                  }
              }
            break;
          }
        case 0x1F:
          {
            if (operand < 0 || operand > 127)
              {
                sc_regSet (FLAG_MEMORY, 1);
              }
            else
              {
                int value1 = 0, value2 = 0;
                sc_accumulatorGet (&value1);
                sc_memoryGet (operand, &value2);
                if (value1 - value2 > 16383 || value1 - value2 < -16384)
                  {
                    sc_regSet (FLAG_OVERFLOW, 1);
                  }
                else
                  {
                    sc_accumulatorSet (value1 - value2);
                  }
              }
            break;
          }
        case 0x20:
          {
            if (operand < 0 || operand > 127)
              {
                sc_regSet (FLAG_MEMORY, 1);
              }
            else
              {
                int value1 = 0, value2 = 0;
                sc_accumulatorGet (&value1);
                sc_memoryGet (operand, &value2);
                if (value2 == 0)
                  {
                    sc_regSet (FLAG_DIVISION, 1);
                  }
                else if (value1 / value2 > 16383 || value1 / value2 < -16384)
                  {
                    sc_regSet (FLAG_OVERFLOW, 1);
                  }
                else
                  {
                    sc_accumulatorSet (value1 / value2);
                  }
              }
            break;
          }
        case 0x21:
          {
            if (operand < 0 || operand > 127)
              {
                sc_regSet (FLAG_MEMORY, 1);
              }
            else
              {
                int value1 = 0, value2 = 0;
                sc_accumulatorGet (&value1);
                sc_memoryGet (operand, &value2);
                if (value1 * value2 > 16383 || value1 * value2 < -16384)
                  {
                    sc_regSet (FLAG_OVERFLOW, 1);
                  }
                else
                  {
                    sc_accumulatorSet (value1 * value2);
                  }
              }
            break;
          }
        case 0x28:
          {
            if (operand < 0 || operand > 127)
              {
                sc_regSet (FLAG_MEMORY, 1);
              }
            else
              {
                i = operand - 1;
              }
            break;
          }
        case 0x29:
          {
            if (operand < 0 || operand > 127)
              {
                sc_regSet (FLAG_MEMORY, 1);
              }
            else
              {
                int value1 = 0;
                int sign = 0, c = 0, a = 0;
                sc_commandDecode (value1, &sign, &c, &a);
                if (sign)
                  {
                    i = operand - 1;
                  }
              }
            break;
          }
        case 0x2A:
          {
            if (operand < 0 || operand > 127)
              {
                sc_regSet (FLAG_MEMORY, 1);
              }
            else
              {
                int value1 = 0;
                sc_accumulatorGet (&value1);
                if (value1 == 0)
                  {
                    i = operand - 1;
                  }
              }
            break;
          }
        case 0x2B:
          {
            flag = 1;
            break;
          }
        case 0x3A:
          {
            int res = 0;
            sc_accumulatorGet (&res);
            if (operand < 0 || operand > 127)
              {
                sc_regSet (FLAG_MEMORY, 1);
              }
            else if (res % 2 == 0)
              {
                i = operand - 1;
                res = i;
              }
          }
          break;
        case 0x3B:
          {
            int res = 0;
            sc_accumulatorGet (&res);
            if (operand < 0 || operand > 127)
              sc_regSet (FLAG_MEMORY, 1);
            else if (res % 2 != 0)
              {
                i = operand - 1;
                res = i;
              }
          }
          break;
        case 0x42:
          {
            if (operand < 0 || operand > 127)
              sc_regSet (FLAG_MEMORY, 1);
            else
              {
                int s = 0, c = 0, acc_operand = 0;
                int acc = 0;
                sc_accumulatorGet (&acc);
                sc_commandDecode (acc, &s, &c, &acc_operand);

                int a = 0;
                sc_memoryGet (operand, &a);
                int b = 0;
                sc_memoryGet (acc_operand, &b);

                if (a - b > 16383 || a - b < -16384)
                  {
                    sc_regSet (FLAG_OVERFLOW, 1);
                  }
                else
                  {
                    sc_accumulatorSet (a - b);
                  }
              }
          }
          break;
        case 0x43:
          {
            if (operand < 0 || operand > 127)
              sc_regSet (FLAG_MEMORY, 1);
            else
              {
                int acc = 0;
                sc_accumulatorGet (&acc);
                int val = 0;
                sc_memoryGet (operand, &val);
                int r = val << acc;
                if (r > 0b111111111111111)
                  {
                    r &= 0b111111111111111;
                    sc_regSet (FLAG_OVERFLOW, 1);
                  }
                sc_accumulatorSet (r);
              }
          }
          break;
        default:
          break;
        }
      sleep (1);
    }
  sc_regSet (FLAG_INTERRUPT, 1);
}

static int
check ()
{
  return checkTerminal () || checkSize ();
}

static void
setNoncanonicalMode ()
{
  struct termios ttystate;
  tcgetattr (STDIN_FILENO, &ttystate);
  ttystate.c_lflag &= ~(ICANON | ECHO);
  ttystate.c_cc[VMIN] = 1;
  tcsetattr (STDIN_FILENO, TCSADRAIN, &ttystate);
}

static void
loadMemory ()
{
  for (int i = 0; i < rand () % MEMORY_SIZE; ++i)
    sc_memorySet (i, rand () % 32000);
  // sc_memorySet (0, -1);
}

static void
setFlags ()
{
  sc_regSet (FLAG_OVERFLOW, 0);
  sc_regSet (FLAG_DIVISION, 0);
  sc_regSet (FLAG_MEMORY, 0);
  sc_regSet (FLAG_INTERRUPT, 1);
}

static void
init ()
{
  srand (time (NULL));

  rk_mytermsave ();
  setNoncanonicalMode ();

  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_accumulatorInit2 ();
  sc_icounterInit ();
  sc_regInit ();

  loadMemory ();
  setFlags ();

  mt_init ();
  setMainColor ();
}

static void
clear ()
{
  mt_setdefaultcolor ();
  rk_mytermrestore ();
}

static void
changeSelectCell (enum keys key)
{
  int cur_cell = 0;
  sc_accumulatorGet2 (&cur_cell);

  int x = cur_cell % 10, y = cur_cell / 10;

  switch (key)
    {
    case KEY_UP:
      --y;
      if (y == -1 && (x == 8 || x == 9))
        y = 11;
      break;
    case KEY_DOWN:
      ++y;
      if (y == 12 && (x == 8 || x == 9))
        y = 0;
      break;
    case KEY_RIGHT:
      ++x;
      if (x == 8 && y == 11)
        {
          x = 0;
          y = 0;
        }
      break;
    case KEY_LEFT:
      --x;
      break;
    case KEY_i:
      for (int i = 0; i < MEMORY_SIZE; ++i)
        sc_memorySet (i, 0);
      sc_regSet (FLAG_OVERFLOW, 0);
      sc_regSet (FLAG_DIVISION, 0);
      sc_regSet (FLAG_MEMORY, 0);
      sc_regSet (FLAG_INTERRUPT, 1);
      sc_regSet (FLAG_COMMAND, 0);
      sc_accumulatorSet (0);
      sc_icounterSet (0);
      printTerm (-1, 0);
      break;
    case KEY_F5:
      {
        mt_setfgcolor (WHITE);
        mt_setbgcolor (BLACK);

        mt_gotoXY (0, 30);
        printf ("Введите новое значение аккумулятора (dec): ");
        fflush (stdout);

        char input[10] = { 0 };

        struct termios oldt, newt;
        tcgetattr (STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag |= ICANON | ECHO;
        tcsetattr (STDIN_FILENO, TCSANOW, &newt);

        scanf ("%s", input);

        tcsetattr (STDIN_FILENO, TCSANOW, &oldt);

        int value = atoi (input);
        sc_accumulatorSet (value);

        mt_gotoXY (0, 30);
        printf ("%*s", 50, " ");

        break;
      }
    case KEY_F6:
      {
        mt_setfgcolor (WHITE);
        mt_setbgcolor (BLACK);

        mt_gotoXY (0, 30);
        printf ("Введите новое значение счётчика команд (dec): ");
        fflush (stdout);

        char input[10] = { 0 };

        struct termios oldt, newt;
        tcgetattr (STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag |= ICANON | ECHO;
        tcsetattr (STDIN_FILENO, TCSANOW, &newt);

        scanf ("%s", input);
        int value = atoi (input);

        if (value < 128 && value >= 0)
          {
            tcsetattr (STDIN_FILENO, TCSANOW, &oldt);
            sc_icounterSet (value);
            x = value % 10;
            y = value / 10;
          }
        else
          {
            sc_icounterGet (&value);
            tcsetattr (STDIN_FILENO, TCSANOW, &oldt);
            sc_icounterSet (value);
          }

        mt_gotoXY (0, 30);
        printf ("%*s", 50, " ");

        break;
      }
    case KEY_s:
      {
        mt_setfgcolor (WHITE);
        mt_setbgcolor (BLACK);

        mt_gotoXY (0, 30);
        printf ("Введите имя файла для сохранения: ");
        fflush (stdout);

        char filename[256] = { 0 };

        struct termios oldt, newt;
        tcgetattr (STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag |= ICANON | ECHO;
        tcsetattr (STDIN_FILENO, TCSANOW, &newt);

        scanf ("%s", filename);

        tcsetattr (STDIN_FILENO, TCSANOW, &oldt);

        if (sc_memorySave (filename) == -1)
          {
            mt_gotoXY (0, 30);
            printf ("Ошибка сохранения файла!");
            sleep (1500000);
          }

        mt_gotoXY (0, 30);
        printf ("%*s", 50, " ");

        break;
      }
    case KEY_l:
      {
        mt_setfgcolor (WHITE);
        mt_setbgcolor (BLACK);

        mt_gotoXY (0, 30);
        printf ("Введите имя файла для загрузки: ");
        fflush (stdout);

        char filename[256] = { 0 };

        struct termios oldt, newt;
        tcgetattr (STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag |= ICANON | ECHO;
        tcsetattr (STDIN_FILENO, TCSANOW, &newt);

        scanf ("%s", filename);

        tcsetattr (STDIN_FILENO, TCSANOW, &oldt);

        if (sc_memoryLoad (filename) == -1)
          {
            mt_gotoXY (0, 30);
            printf ("Ошибка загрузки файла!");
            sleep (1500000);
          }

        mt_gotoXY (0, 30);
        printf ("%*s", 50, " ");

        break;
      }
    case KEY_r:
      r_func ();
      break;
    case KEY_t:
      t_func (&cur_cell, &x, &y);
      break;
    case KEY_ENTER:
      {
        mt_setfgcolor (WHITE);
        mt_setbgcolor (BLACK);

        mt_gotoXY (0, 30);
        printf ("Введите новое значение ячейки памяти (dec): ");
        fflush (stdout);

        char input[10] = { 0 };

        struct termios oldt, newt;
        tcgetattr (STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag |= ICANON | ECHO;
        tcsetattr (STDIN_FILENO, TCSANOW, &newt);

        scanf ("%s", input);

        tcsetattr (STDIN_FILENO, TCSANOW, &oldt);

        int value = atoi (input);
        int address = 0;
        sc_accumulatorGet2 (&address);
        sc_memorySet (address, value);
        printTerm (address, value);

        mt_gotoXY (0, 30);
        printf ("%*s", 50, " ");
      }
      break;
    default:
      break;
    }

  if (x < 0)
    {
      x = 9;
      y--;
      if (y == -1)
        x = 7;
    }
  else if (x > 9)
    {
      x = 0;
      y++;
    }
  if (y < 0)
    y = 12;
  else if (y > 12)
    y = 0;

  cur_cell = y * 10 + x;
  sc_accumulatorSet2 (cur_cell);
  sc_icounterSet (cur_cell);
}

static int
isExit (enum keys key)
{
  return key != KEY_ESC;
}

int
main ()
{
  int err = 0;
  if (check ())
    err = 1;
  else
    {
      init ();
      for (int i = 0; i < 128; i++)
        {
          int command_value;
          sc_memoryGet (i, &command_value);
          int sign = 0, command = 0, operand = 0;
          sc_commandDecode (command_value, &sign, &command, &operand);
          if (sc_commandValidate (command) == ERROR)
            {
              sc_regSet (FLAG_COMMAND, 1);
            }
        }

      enum Mode is_run = Default;
      while ((int)is_run)
        {
          mt_clrscr ();

          // view
          printMemory ();
          printAccumulator ();
          printCounters ();
          printCommand ();
          printFlags ();
          printBigCell ();

          int value = 0, address = 0;
          sc_accumulatorGet2 (&address);
          sc_memoryGet (address, &value);
          printDecodedCommand (value);
          printKeys ();
          printTerm (-2, 0);
          for (int i = 0; i < 128; i++)
            {
              int command_value;
              sc_memoryGet (i, &command_value);
              int sign = 0, command = 0, operand = 0;
              sc_commandDecode (command_value, &sign, &command, &operand);
              if (sc_commandValidate (command) == ERROR)
                {
                  sc_regSet (FLAG_COMMAND, 1);
                }
            }

          // do
          enum keys key = KEY_NULL;
          rk_readkey (&key);
          changeSelectCell (key);

          // check close program
          is_run = isExit (key);

          mt_gotoXY (0, MIN_ROWS + 1);
        }

      clear ();
    }

  return err;
}

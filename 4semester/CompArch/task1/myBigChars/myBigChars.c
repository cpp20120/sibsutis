#include "../include/myBigChars.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
bc_strlen (char *str)
{
  int len = 0;
  if (str != NULL)
    {
      for (int i = 0; str[i] != '\0'; ++i)
        {
          if ((str[i] >> 6 & 0b11) != 0b10)
            ++len;
        }
    }
  return len;
}

int
bc_printA (char *str)
{
  write (STDOUT_FILENO, "\eN", 3);
  printf ("%s", str);
  write (STDOUT_FILENO, "\eO", 3);
  return 0;
}
int
bc_printB (char *str, int Xpos) // насрал
{
  write (STDOUT_FILENO, "\eN", 3);
  char *str_copy = malloc (strlen (str) + 1);
  if (!str_copy)
    {
      perror ("malloc failed");
      return 0;
    }
  strcpy (str_copy, str);

  char *line = strtok (str_copy, "\n");
  int Ypos = 1;
  while (line != NULL)
    {
      mt_gotoXY (63 + Xpos * 9, 7 + Ypos);
      Ypos++;
      printf ("%s\n", line);
      line = strtok (NULL, "\n");
    }
  free (str_copy);
  write (STDOUT_FILENO, "\eO", 3);
  return 0;
}
int
bc_box (int x1, int y1, int x2, int y2, enum colors box_fg, enum colors box_bg,
        char *header, enum colors header_fg, enum colors header_bg)
{
  mt_gotoXY (x1, y1);

  mt_setfgcolor (box_fg);
  mt_setbgcolor (box_bg);

  bc_printA ("┌");
  for (int cx = x1 + 1; cx < x2; ++cx)
    {
      bc_printA ("─");
    }
  bc_printA ("┐");

  // отрисовка заголовка
  if (header != NULL)
    {
      int header_len = bc_strlen (header);
      int header_begin = x1 + (x2 - x1) / 2.0 - header_len / 2.0;
      mt_setfgcolor (header_fg);
      mt_setbgcolor (header_bg);
      mt_gotoXY (header_begin, y1);
      printf (" %s ", header);
    }
  mt_setfgcolor (box_fg);
  mt_setbgcolor (box_bg);

  // середина
  for (int cy = y1 + 1; cy < y2; ++cy)
    {
      mt_gotoXY (x1, cy);
      bc_printA ("│");
      mt_gotoXY (x2, cy);
      bc_printA ("│");
    }

  // последняя строка
  mt_gotoXY (x1, y2);
  bc_printA ("└");
  for (int cx = x1 + 1; cx < x2; ++cx)
    {
      bc_printA ("─");
    }
  bc_printA ("┘");

  // возвращаемся к изначальным цветам терминала
  mt_setdefaultcolor ();
  mt_gotoXY (x1, y2 + 1);

  return 0;
}

int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  if (x < 0 || x > 7 || y < 0 || y > 7 || (value != 0 && value != 1))
    return -1;

  int index = x / 4;
  int bit_pos = (x % 4) * 8 + y;

  if (value)
    big[index] |= (1 << bit_pos);
  else
    big[index] &= ~(1 << bit_pos);

  return 0;
}

int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  if (x < 0 || x > 7 || y < 0 || y > 7 || value == NULL)
    return -1;

  int index = x / 4;
  int bit_pos = (x % 4) * 8 + y;

  *value = (big[index] >> bit_pos) & 1;

  return 0;
}

int
bc_printbigchar (int big[2], int x, int y, enum colors fg, enum colors bg)
{
  mt_setfgcolor (fg);
  mt_setbgcolor (bg);

  for (int i = 0; i < 8; i++)
    {
      mt_gotoXY (x + i, y);
      for (int j = 0; j < 8; j++)
        {
          int value;
          bc_getbigcharpos (big, i, j, &value);
          if (value)
            bc_printA ("\u2593");
          else
            bc_printA (" ");
        }
    }

  mt_setdefaultcolor ();
  return 0;
}

// int
// bc_bigcharwrite (int fd, int *big, int count)
// {
//   if (fd < 0 || big == NULL || count <= 0)
//     return -1;

//   ssize_t written = write (fd, big, count * 2 * sizeof(int));
//   if (written != count * 2 * sizeof(int))
//     return -1;

//   return 0;
// }

int
bc_bigcharread (int fd, int *big, int need_count, int *count)
{
  if (fd < 0 || big == NULL || need_count <= 0 || count == NULL)
    return -1;

  ssize_t read_bytes = read (fd, big, need_count * 2 * sizeof (int));
  if (read_bytes <= 0)
    {
      *count = 0;
      return -1;
    }

  *count = read_bytes / (2 * sizeof (int));
  return 0;
}
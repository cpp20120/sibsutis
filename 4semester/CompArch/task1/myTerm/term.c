#include "../include/term.h"

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

int
mt_clrscr ()
{
  fflush (stdout);

  return write (STDOUT_FILENO, CLEAR_TERMINAL_ESCAPE,
                CLEAR_TERMINAL_ESCAPE_LEN)
                 == -1
             ? ERROR
             : OK;
}

int
mt_gotoXY (int x, int y)
{
  fflush (stdout);

  char buf[26] = { 0 };
  int len = snprintf (buf, sizeof (buf), GOTO_XY_ESCAPE, y, x);
  return write (STDOUT_FILENO, buf, len) == -1 ? ERROR : OK;
}

int
mt_getscreensize (int *rows, int *cols)
{
  fflush (stdout);

  int error_code = OK;

  struct winsize ws;
  if (ioctl (STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || rows == NULL
      || cols == NULL)
    error_code = ERROR;
  else
    {
      *rows = ws.ws_row;
      *cols = ws.ws_col;
    }

  return error_code;
}

int
mt_setfgcolor (enum colors color)
{
  fflush (stdout);

  char buf[16] = { 0 };
  int len = snprintf (buf, sizeof (buf), SET_FG_COLOR_ESCAPE, color);
  return write (STDOUT_FILENO, buf, len) == -1 ? ERROR : OK;
}

int
mt_setbgcolor (enum colors color)
{
  fflush (stdout);

  char buf[16] = { 0 };
  int len = snprintf (buf, sizeof (buf), SET_BG_COLOR_ESCAPE, color);
  return write (STDOUT_FILENO, buf, len) == -1 ? ERROR : OK;
}

int
mt_setdefaultcolor ()
{
  fflush (stdout);

  int error_code = OK;

  if (mt_setfgcolor (DEFAULT) == ERROR)
    error_code = ERROR;
  if (mt_setbgcolor (DEFAULT) == ERROR)
    error_code = ERROR;

  return error_code;
}

int
mt_setcursorvisible (int value)
{
  fflush (stdout);

  int error_code = OK;

  if (value && write (STDOUT_FILENO, SET_CURSOR_VISIBLE_ON_ESCAPE, 6) == -1)
    error_code = ERROR;
  else if (write (STDOUT_FILENO, SET_CURSOR_VISIBLE_OFF_ESCAPE, 6) == -1)
    error_code = ERROR;

  return error_code;
}

int
mt_delline (void)
{
  fflush (stdout);

  return write (STDOUT_FILENO, DEL_LINE_ESCAPE, DEL_LINE_ESCAPE_LEN) == -1
             ? ERROR
             : OK;
}
#include "../include/myReadkey.h"

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

static struct termios term_params;

int
rk_readkey (enum keys *key)
{
  size_t k = 0;
  int err = read (STDIN_FILENO, &k, sizeof (k));
  if (k == KEY_ENTER || k == KEY_ESC || k == KEY_PLUS || k == KEY_MINUS
      || (k >= KEY_0 && k <= KEY_9) || (k >= KEY_A && k <= KEY_Z)
      || (k >= KEY_a && k <= KEY_z) || k == KEY_UP || k == KEY_DOWN
      || k == KEY_RIGHT || k == KEY_LEFT || k == KEY_F5 || k == KEY_F6)
    *key = k;
  else
    *key = KEY_NULL;
  return err;
}

int
rk_mytermsave ()
{
  return tcgetattr (STDIN_FILENO, &term_params);
}

int
rk_mytermrestore ()
{
  return tcsetattr (STDIN_FILENO, TCSADRAIN, &term_params);
}

int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
  struct termios new_term_params;

  if (tcgetattr (STDOUT_FILENO, &new_term_params))
    return -1;

  if (regime)
    {
      new_term_params.c_lflag
          &= ~(ICANON | (echo ? 0 : ECHO) | (sigint ? 0 : ISIG));
      new_term_params.c_cc[VTIME] = vtime;
      new_term_params.c_cc[VMIN] = vmin;
    }
  else
    {
      new_term_params.c_lflag
          |= ICANON | (echo ? ECHO : 0) | (sigint ? ISIG : 0);
    }

  return tcsetattr (STDOUT_FILENO, TCSANOW, &new_term_params);
}

int
rk_readvalue (int *value, int timeout)
{
  char buffer[32] = { 0 };
  size_t i = 0;
  char c;
  *value = 0;

  rk_mytermregime (1, timeout / 100, 0, 1, 1);

  while (1)
    {
      if (read (STDIN_FILENO, &c, 1) <= 0)
        {
          rk_mytermregime (0, 0, 1, 1, 1);
          return -1;
        }

      if (c == '\n' || c == '\r')
        {
          buffer[i] = '\0';
          *value = atoi (buffer);
          rk_mytermregime (0, 0, 1, 1, 1);
          return 0;
        }
      else if (c >= '0' && c <= '-')
        {
          if (i < sizeof (buffer) - 1)
            {
              buffer[i++] = c;
              write (STDOUT_FILENO, &c, 1);
            }
        }
      else if (c == 127 || c == '\b')
        {
          if (i > 0)
            {
              i--;
              write (STDOUT_FILENO, "\b \b", 3);
            }
        }
    }
}
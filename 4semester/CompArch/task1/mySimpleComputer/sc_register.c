#include "../include/mySimpleComputer.h"

#include <stdint.h>
#include <stdlib.h>

static int instruction_counter = 0;
static uint8_t flags = 0;
static int accumulator = 0;
static int accumulator2 = 0;

int
sc_accumulatorInit ()
{
  accumulator = 0;
  return OK;
}

int
sc_accumulatorSet (int value)
{
  int status_code = OK;
  int real_value = (value << 1 >> 1);
  if (real_value <= (MAX_CELL_VALUE >> 1))
    {
      if (value < 0)
        accumulator = (value & (MAX_CELL_VALUE >> 1)) | (1 << 14);
      else
        accumulator = value;
    }
  else
    status_code = ERROR;
  return status_code;
}

int
sc_accumulatorGet (int *value)
{
  if (!value)
    return ERROR;
  *value = accumulator;
  return OK;
}

int
sc_accumulatorInit2 ()
{
  accumulator2 = 0;
  return OK;
}

int
sc_accumulatorSet2 (int value)
{
  if (value < MIN_ICOUNTER || value > MAX_ICOUNTER)
    return ERROR;
  accumulator2 = value;
  return OK;
}

int
sc_accumulatorGet2 (int *value)
{
  if (!value)
    return ERROR;
  *value = accumulator2;
  return OK;
}

int
sc_regInit ()
{
  flags = 0;
  return OK;
}

int
sc_regSet (int reg, int value)
{
  if (reg != FLAG_OVERFLOW && reg != FLAG_DIVISION && reg != FLAG_MEMORY
      && reg != FLAG_COMMAND && reg != FLAG_INTERRUPT)
    return ERROR;
  if (value)
    flags |= reg;
  else
    flags &= ~reg;
  return OK;
}

int
sc_regGet (int reg, int *value)
{
  if (!value
      || (reg != FLAG_OVERFLOW && reg != FLAG_DIVISION && reg != FLAG_MEMORY
          && reg != FLAG_COMMAND && reg != FLAG_INTERRUPT))
    return ERROR;
  *value = (flags & reg) ? 1 : 0;
  return OK;
}

int
sc_icounterInit ()
{
  instruction_counter = 0;
  return OK;
}

int
sc_icounterSet (int value)
{
  if (value < MIN_ICOUNTER || value > MAX_ICOUNTER)
    return ERROR;
  instruction_counter = value;
  return OK;
}

int
sc_icounterGet (int *value)
{
  if (!value)
    return ERROR;
  *value = instruction_counter;
  return OK;
}
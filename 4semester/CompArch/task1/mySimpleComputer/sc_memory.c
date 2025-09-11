#include "../include/mySimpleComputer.h"

#include <stdio.h>
#include <stdlib.h>

static int memory[MEMORY_SIZE] = { 0 };

static void
copyMemory (int *mem, int *buff)
{
  for (int i = 0; i < MEMORY_SIZE; ++i)
    buff[i] = mem[i];
}

int
sc_memoryInit ()
{
  for (int i = 0; i < MEMORY_SIZE; ++i)
    memory[i] = MIN_CELL_VALUE;
  return OK;
}

int
sc_memoryGet (int address, int *value)
{
  int status_code = OK;

  if (address >= 0 && address < MEMORY_SIZE && value != NULL)
    {
      *value = memory[address];
    }
  else
    {
      status_code = ERROR;
    }
  return status_code;
}
int
sc_memorySet (int address, int value)
{
  int status_code = OK;
  int real_value = (value << 1 >> 1);
  if (address >= 0 && address < MEMORY_SIZE
      && real_value <= (MAX_CELL_VALUE >> 1))
    {
      if (value < 0)
        memory[address] = (value & (MAX_CELL_VALUE >> 1)) | (1 << 14);
      else
        memory[address] = value;
    }
  else
    status_code = ERROR;
  return status_code;
}

int
sc_memoryLoad (char *filename)
{
  int status_code = OK;

  int memory_buffer[MEMORY_SIZE] = { 0 };
  copyMemory (memory, memory_buffer);

  if (filename != NULL)
    {
      FILE *file = fopen (filename, "rb");

      if (file != NULL)
        {
          for (int i = 0; i < MEMORY_SIZE; ++i)
            {
              if (fread ((char *)&(memory_buffer[i]), sizeof (int), 1, file)
                  < 1)
                {
                  status_code = ERROR;
                  fclose (file);
                  break;
                }
            }
          if (!status_code)
            {
              copyMemory (memory_buffer, memory);
              fclose (file);
            }
        }
      else
        status_code = ERROR;
    }
  else
    status_code = ERROR;

  return status_code;
}

int
sc_memorySave (char *filename)
{
  int status_code = OK;

  if (filename != NULL)
    {
      FILE *file = fopen (filename, "wb");

      if (file != NULL)
        {
          for (int i = 0; i < MEMORY_SIZE; ++i)
            fwrite ((char *)&(memory[i]), sizeof (int), 1, file);

          fclose (file);
        }
      else
        status_code = ERROR;
    }
  else
    status_code = ERROR;

  return status_code;
}

#include "../include/mySimpleComputer.h"

#include <stdlib.h>

int
sc_commandDecode (int value, int *sign, int *command, int *operand)
{
  int error_code = OK;

  int buffer_sign = (value & SIGN_MASK) >> SIGN_POS;
  int buffer_command = (value & MAX_COMMAND_CODE) >> COMMANG_POS;
  int buffer_operand = value & MAX_OPERAND_CODE;

  if (sign == NULL || command == NULL || operand == NULL)
    error_code = ERROR;
  else
    {
      *sign = buffer_sign;
      *command = buffer_command;
      *operand = buffer_operand;
    }

  return error_code;
}

int
sc_commandEncode (int sign, int command, int operand, int *value)
{
  int error_code = OK;

  if ((sign != 0 && sign != 1) || !(command >= 0 && command <= MAX_CODE)
      || !(operand >= 0 && operand <= MAX_CODE) || value == NULL)
    error_code = ERROR;
  else
    *value = (sign << SIGN_POS) | (command << COMMANG_POS) | operand;

  return error_code;
}

int
sc_commandValidate (int command)
{
  int error_code = OK;

  if (command < 0 || command > MAX_COMMANG_VALUE)
    error_code = ERROR;

  return error_code;
}
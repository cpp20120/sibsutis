#ifndef _INCLUDE_MY_SIMPLE_COMPUTER_H
#define _INCLUDE_MY_SIMPLE_COMPUTER_H

#include "common.h"

#define SIGN_MASK 0b100000000000000
#define SIGN_POS 14
#define MAX_COMMAND_CODE 0b11111110000000
#define COMMANG_POS 7
#define MAX_OPERAND_CODE 0b1111111
#define MAX_CODE 0b1111111
#define MAX_COMMANG_VALUE 76

#define MEMORY_SIZE 128
#define MIN_CELL_VALUE 0
#define MAX_CELL_VALUE 0b111111111111111

#define FLAG_OVERFLOW 0x01
#define FLAG_DIVISION 0x02
#define FLAG_MEMORY 0x04
#define FLAG_COMMAND 0x08
#define FLAG_INTERRUPT 0x10
#define MAX_ICOUNTER 0b111111111111111
#define MIN_ICOUNTER 0

/**
 * @brief Encodes the cell value in accordance with the format of the Simple
 * Computer command and using the received sign, command number, and operand
 * as field values, and places the result in value. If invalid values are
 * specified for the sign, command, or operand, the function terminates with
 * the status -1 and the value value does not change. Otherwise, the completion
 * status is 0. For the sign, operand, and command, all values that match the
 * format of the Simple Computer command are valid.
 *
 * @param sign - command sign.
 * @param command - CPU commands.
 * @param operand - command operand.
 * @param value - a pointer to the memory location where the encoded value will
 * be written.
 * @return int
 */
int sc_commandEncode (int sign, int command, int operand, int *value);

/**
 * @brief Decodes the value of a memory location as a Simple Computer command.
 * If decoding is not possible, the function terminates with the status -1 and
 * the output parameters do not change their values. Otherwise, completion
 * status = 0.
 *
 * @param value - the value of the memory location.
 * @param sign - the pointer where the sign will be written.
 * @param command - the pointer where the command will be written.
 * @param operand - the pointer where the operand will be written.
 * @return int
 */
int sc_commandDecode (int value, int *sign, int *command, int *operand);

/**
 * @brief Checks the value of the "command" field for correctness. If the value
 * is incorrect, -1 is returned. Otherwise, 0 is returned.
 *
 * @param command - command.
 * @return int
 */
int sc_commandValidate (int command);

/**
 * @brief Initializes the RAM of a Simple Computer, setting all its cells to
 * zero values.
 *
 * @return int
 */
int sc_memoryInit ();

/**
 * @brief Sets the value of the specified memory location as value. If the
 * address exceeds the acceptable limits or the value does not match the
 * acceptable range of values, the function returns -1, otherwise it terminates
 * correctly and returns 0.
 *
 * @param address - address per memory location
 * @param value - new cell value
 * @return int
 */
int sc_memorySet (int address, int value);

/**
 * @brief Returns the value of the specified memory location in value. If the
 * address exceeds the acceptable limits or an incorrect pointer is passed to
 * value, then the function terminates with the status -1. If the function is
 * executed successfully, it terminates with the status 0.
 *
 * @param address - address per memory location
 * @param value - a pointer to where the value is stored
 * @return int
 */
int sc_memoryGet (int address, int *value);

/**
 * @brief Saves the contents of the memory to a binary file (using the write or
 * fwrite function). If an incorrect pointer to the file name is passed or some
 * error has occurred in writing data to the file, the function terminates with
 * the status -1. If successful, the function ends with a status of 0.
 *
 * @param filename - the name of the file where the "RAM" is saved
 * @return int
 */
int sc_memorySave (char *filename);

/**
 * @brief Loads the contents of RAM from the specified file (using the read or
 * fread function). If an incorrect pointer to the file name is passed or some
 * error occurs when reading data from the file, the function terminates with
 * the status -1, while the contents of the "RAM" do not change (i.e. it should
 * not deteriorate). If successful, the function ends with a status of 0.
 *
 * @param filename - the name of the file where the "RAM" is loaded from
 * @return int
 */
int sc_memoryLoad (char *filename);

/**
 * @brief Initializes the flags register, setting all its flags to zero.
 *
 * @return int
 */
int sc_regInit ();

/**
 * @brief Sets the specified flag in the flags register to the specified value.
 *
 * @param reg - flag to set: FLAG_OVERFLOW, FLAG_DIVISION, FLAG_MEMORY,
 *              FLAG_COMMAND, FLAG_INTERRUPT
 * @param value - value to set the flag to: 0 or 1
 *
 * @return int - 0 if operation was successful, -1 otherwise
 */
int sc_regSet (int reg, int value);

/**
 * @brief Retrieves the value of the specified flag from the flags register.
 *
 * @param reg - flag to get: FLAG_OVERFLOW, FLAG_DIVISION, FLAG_MEMORY,
 *              FLAG_COMMAND, FLAG_INTERRUPT
 * @param value - a pointer to where the flag value is stored
 *
 * @return int - 0 if operation was successful, -1 otherwise
 */
int sc_regGet (int reg, int *value);

/**
 * @brief Initializes the accumulator register, setting it to zero.
 *
 * @return int - 0 if operation was successful, -1 otherwise
 */
int sc_accumulatorInit ();

/**
 * @brief Sets the value of the accumulator register.
 *
 * @param value - new value of the accumulator
 *
 * @return int - 0 if operation was successful, -1 otherwise
 */
int sc_accumulatorSet (int value);

/**
 * @brief Retrieves the value of the accumulator register.
 *
 * @param value - a pointer to where the accumulator value is stored
 *
 * @return int - 0 if operation was successful, -1 otherwise
 */
int sc_accumulatorGet (int *value);

/**
 * @brief Initializes the instruction counter register, setting it to zero.
 *
 * @return int - 0 if operation was successful, -1 otherwise
 */
int sc_icounterInit ();

/**
 * @brief Sets the value of the instruction counter register.
 *
 * @param value - new value of the instruction counter
 *
 * @return int - 0 if operation was successful, -1 otherwise
 */
int sc_icounterSet (int value);

/**
 * @brief Retrieves the value of the instruction counter register
 *
 * @param value - a pointer to where the instruction counter value is stored
 *
 * @return int - 0 if operation was successful, -1 otherwise
 */
int sc_icounterGet (int *value);
int sc_accumulatorInit2 ();
int sc_accumulatorSet2 (int value);
int sc_accumulatorGet2 (int *value);

#endif // _INCLUDE_MY_SIMPLE_COMPUTER_H

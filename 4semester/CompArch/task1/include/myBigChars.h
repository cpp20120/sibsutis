#ifndef _MY_BIG_CHARS_H
#define _MY_BIG_CHARS_H

#include "term.h"

/**
 * @brief Counts the number of characters in a UTF-8 string. If decoding of any
 * character is impossible or an incorrect pointer is passed, the function
 * returns 0.
 *
 * @param str - UTF-8 string.
 * @return int
 */
int bc_strlen (char *str);

/**
 * @brief Outputs a string of characters using an additional encoding table.
 *
 * @param str - string.
 * @return int
 */
int bc_printA (char *str);
/**
 * @brief Outputs a string of characters using an additional encoding table.
 *
 * @param str - string.
 * @return int
 */
int bc_printB (char *str, int Xpos); // насрал
/**
 * @brief Displays a pseudographic frame in which the upper-left corner is
 * located in row x1 and column y1, and its width and height are equal to y2
 * columns and x2 rows. The color of the pseudographic symbols and their
 * background are specified in the parameters box_fg, box_bg. If a valid
 * pointer to header is passed and the received string is decoded from UTF-8,
 * then the header string with the specified character color on the specified
 * background color is displayed in the upper line of the frame in the middle.
 *
 * @param x1 - x coordinate of the upper-left corner
 * @param y1 - y coordinate of the upper-left corner
 * @param x2 - width
 * @param y2 - height
 * @param box_fg - frame color
 * @param box_bg - background color of the frame
 * @param header - title
 * @param header_fg - title color
 * @param header_bg - background color of the title
 * @return int
 */
int bc_box (int x1, int y1, int x2, int y2, enum colors box_fg,
            enum colors box_bg, char *header, enum colors header_fg,
            enum colors header_bg);

/**
 * @brief Manipulates the font element and sets the value of the familiar "big
 * character" in row x and column y to value.
 *
 * @param big
 * @param x
 * @param y
 * @param value
 * @return int
 */
int bc_setbigcharpos (int *big, int x, int y, int value);

/**
 * @brief Returns the value of the position in the "big character" in row x and
 * column y.
 *
 * @param big
 * @param x
 * @param y
 * @param value
 * @return int
 */
int bc_getbigcharpos (int *big, int x, int y, int *value);

/**
 * @brief Displays a "large symbol" measuring eight rows by eight columns, the
 * upper-left corner is 83 The second one is located in row x and column y. The
 * third and fourth parameters determine the color and background of the
 * displayed characters. The "symbol" is output based on the values of an array
 * of integers as follows. The first line outputs the 8 least significant bits
 * of the first number, the next 8 in the second, and the next 4 in the third.
 * In line 5, the 8 least significant bits of the second number are output,
 * etc. In this case, if the value if bit = 0, then the "space" character is
 * output, otherwise it is a character that fills in the familiarity
 * (ACS_CKBOARD).
 *
 * @param c
 * @param x
 * @param y
 * @param fg
 * @param bg
 * @return int
 */
int bc_printbigchar (int c[2], int x, int y, enum colors fg, enum colors bg);

/**
 * @brief Writes a set number of "large characters" to a file. The recording
 * format is determined by the user. Characters are written in binary format.
 *
 * @param fd
 * @param big
 * @param count
 * @return int
 */
int bc_bigcharwrite (int fd, int *big, int count);

/**
 * @brief Reads a set number of "large characters" from a file. The third
 * parameter specifies the address of the variable where the number of
 * characters read is placed, or 0, in case of an error.
 *
 * @param fd
 * @param big
 * @param need_count
 * @param count
 * @return int
 */
int bc_bigcharread (int fd, int *big, int need_count, int *count);

#endif // _MY_BIG_CHARS_H

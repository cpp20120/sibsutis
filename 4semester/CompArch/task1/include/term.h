#ifndef _TERM_H
#define _TERM_H

#include "common.h"

/**
 * @file term.h
 * @brief Terminal control functions
 *
 * This file provides functions for controlling the terminal, including
 * managing colors, cursor position, screen size, and other terminal-related
 * features.
 */

#define CLEAR_TERMINAL_ESCAPE "\e[H\e[J"
#define CLEAR_TERMINAL_ESCAPE_LEN 7

#define GOTO_XY_ESCAPE "\e[%d;%dH"

#define SET_FG_COLOR_ESCAPE "\e[3%dm"
#define SET_BG_COLOR_ESCAPE "\e[4%dm"

#define SET_CURSOR_VISIBLE_ON_ESCAPE "\e[?25h"
#define SET_CURSOR_VISIBLE_OFF_ESCAPE "\e[?25l"
#define SET_CURSOR_VISIBLE_ESCAPE_LEN 7

#define DEL_LINE_ESCAPE "\e[2K"
#define DEL_LINE_ESCAPE_LEN 5

#define mt_init() fflush (stdout)

/**
 * @enum colors
 * @brief Enumeration of colors for text and background
 *
 * This enumeration defines the available colors that can be used to set the
 * text or background color in the terminal.
 */
enum colors
{
  BLACK,      /**< Black color */
  RED,        /**< Red color */
  GREEN,      /**< Green color */
  YELLOW,     /**< Yellow color */
  BLUE,       /**< Blue color */
  MAGENTA,    /**< Magenta color */
  CYAN,       /**< Cyan color */
  WHITE,      /**< White color */
  DEFAULT = 9 /**< Default color */
};

/**
 * @brief Clears the terminal screen
 *
 * This function clears the terminal screen and moves the cursor to the
 * top-left corner.
 *
 * @return 0 on success, -1 on error
 */
int mt_clrscr ();

/**
 * @brief Moves the cursor to the specified position
 *
 * This function moves the terminal cursor to the position (x, y), where (1, 1)
 * is the top-left corner of the screen.
 *
 * @param x The X coordinate (column)
 * @param y The Y coordinate (row)
 * @return 0 on success, -1 on error
 */
int mt_gotoXY (int x, int y);

/**
 * @brief Gets the size of the terminal screen
 *
 * This function retrieves the number of rows and columns available in the
 * terminal.
 *
 * @param rows Pointer to the variable where the number of rows will be stored
 * @param cols Pointer to the variable where the number of columns will be
 * stored
 * @return 0 on success, -1 on error
 */
int mt_getscreensize (int *rows, int *cols);

/**
 * @brief Sets the text color
 *
 * This function sets the text color in the terminal.
 *
 * @param color The text color from the @ref colors enumeration
 * @return 0 on success, -1 on error
 */
int mt_setfgcolor (enum colors color);

/**
 * @brief Sets the background color
 *
 * This function sets the background color in the terminal.
 *
 * @param color The background color from the @ref colors enumeration
 * @return 0 on success, -1 on error
 */
int mt_setbgcolor (enum colors color);

/**
 * @brief Resets text and background colors to default
 *
 * This function resets the text and background colors to their default values.
 *
 * @return 0 on success, -1 on error
 */
int mt_setdefaultcolor ();

/**
 * @brief Controls the visibility of the cursor
 *
 * This function enables or disables the visibility of the cursor in the
 * terminal.
 *
 * @param value 1 to enable cursor visibility, 0 to disable
 * @return 0 on success, -1 on error
 */
int mt_setcursorvisible (int value);

/**
 * @brief Deletes the current line in the terminal
 *
 * This function deletes the entire line where the cursor is currently located.
 *
 * @return 0 on success, -1 on error
 */
int mt_delline ();

#endif // _INCLUDE_TERM_H

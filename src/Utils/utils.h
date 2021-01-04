#ifndef _UTILS_H

#include "string"
#include "algorithm"
#define RED	"\033[0;31m" /** Color for error messages */
#define NO_COLOR "\033[0m" /** Color for normal text */
#define CLEAR_SCREEN "\x1b[2J\x1b[H" /**Used to clear the terminal/console*/

/**
 * Will check is the string passed is a integer
 * @param str The string to confirm if is a integer
 * @return Bool if the string is a integer, false otherwise
 */
bool isNumeric(std::string& str);

/**
 * Will check is the string passed is a float
 * @param str The string to confirm if is a float
 * @return Bool if the string is a float, false otherwise
 */
bool isFloat(std::string& str);

#endif //_UTILS_H

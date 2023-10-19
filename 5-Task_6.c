#include "main.h"

/**
 * get_size - Determines the size to cast the argument
 * @format: The formatted string to print the arguments in
 * @i: The list of arguments to be printed
 *
 * Return: The size to cast the argument
 */

int get_size(const char *format, int *i)
{
	int size = 0;
	int curr_i = *i + 1;

	if (format[curr_i] == 'l')
		size = S_LONG;
	else if (format[curr_i] == 'h')
		size = S_SHORT;

	*i = (size == 0) ? curr_i - 1 : curr_i;

	return (size);
}

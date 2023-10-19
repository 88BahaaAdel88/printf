#include "main.h"

/**
 * get_flags - Determines which flags are active
 * @format: Formatted string to print the arguments in
 * @i: An input parameter.
 * Return:The active flags
 */
int get_flags(const char *format, int *i)
{
	int flags = 0;
	const char *flag_chars = "-+0# ";
	const int flag_values[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE};

	for (int curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
		{
			for (int j = 0; flag_chars[j] != '\0'; j++)
			{
				if (format[curr_i] == flag_chars[j])
				{
					flags |= flag_values[j];
					break;
				}
			}
			if (flag_chars[j] == 0)
				break;
		}

		*i = curr_i - 1;

		return (flags);
}

#include "main.h"

/**
 * handle_write_char - Prints a character
 * @c: The character to be printed
 * @buffer: An array used as a buffer for printing
 * @flags: The active flags
 * @width: The width specification
 * @precision: The precision specification
 * @size: The size specifier
 *
 * Return: The number of characters printed
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}
/**
 * handle_write_char - Prints a character
 * @c: The character to be printed
 * @buffer: An array used as a buffer for printing
 * @flags: The active flags
 * @width: The width specification
 * @precision: The precision specification
 * @size: The size specifier
 *
 * Return: The number of characters printed
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, padd, extra_ch));
}
/**
 * write_num - Writes a number to a buffer
 * @ind: The index at which the number starts in the buffer
 * @buffer: The buffer to write to
 * @flags: The active flags
 * @width: The width specification
 * @prec: The precision specification
 * @length: The length of the number
 * @padd: The padding character
 * @extra_c: An extra character to be printed
 *
 * Return: The number of characters printed
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}
/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if num is negative
 * @ind: Index at which number starts in the buffer
 * @buffer: Array of characters
 * @flags: Flags specification
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specification
 *
 * Return: Number of written characters
 */
int write_unsgnd(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ';
	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (int i = 0; i < width - length; i++)
			buffer[i] = padd;

			buffer[width - length] = '\0';

	if (flags & F_MINUS)
		return (write(1, &buffer[ind], length) + write(1, &buffer[0], width - length));
	else
		return (write(1, &buffer[0], width - length) + write(1, &buffer[ind], length));
	}

	return (write(1, &buffer[ind], length));
}
/**
 * @brief Writes a memory address to the buffer
 *
 * @param buffer The buffer to write to
 * @param ind The index at which the number starts in the buffer
 * @param length The length of the number
 * @param width The width specifier
 * @param flags The flags specifier
 * @param padd The character representing the padding
 * @param extra_c The character representing extra char
 * @param padd_start The index at which padding should start
 *
 * @return The number of written characters.
 */
int write_pointer(char buffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start)
{
	if (width > length)
	{
		for (int i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[width - length + 3] = '\0';
		
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], width - length));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], width - length) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], width - padd_start + 3) + write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}

	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}

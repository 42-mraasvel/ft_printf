/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 09:01:17 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/20 11:25:52 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

/*
** Puts flags in the same manner as printf.
** Order: '#+ -0'
** '+' overwrites ' '
** '-' overwrites '0'
** Return: -1 on write error.
*/

int	put_flags_on_error(t_flags flags)
{
	if (write(1, "%", 1) == -1)
		return (-1);
	if (flags.hash == 1)
		if (write(1, "#", 1) == -1)
			return (-1);
	if (flags.plus == 1)
	{
		if (write(1, "+", 1) == -1)
			return (-1);
	}
	else if (flags.space == 1)
		if (write(1, " ", 1) == -1)
			return (-1);
	if (flags.minus == 1)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
	}
	else if (flags.zero == 1)
		if (write(1, "0", 1) == -1)
			return (-1);
	return (1);
}

/*
** Mimics printf's output for invalid conversion character.
** Return: Bytes written to stdout on success.
** Return: -1 on error.
*/
//write does not return -1 here

int	print_conversion_error(t_flags flags)
{
	int		bytes_printed;

	bytes_printed = put_flags_on_error(flags);
	if (bytes_printed == -1)
		return (-1);
	if (flags.hash == 1)
		bytes_printed++;
	if (flags.plus == 1 || flags.space == 1)
		bytes_printed++;
	if (flags.minus == 1 || flags.zero == 1)
		bytes_printed++;
	if (flags.field_width != 0)
		ft_putnbr_fd(flags.field_width, 1);
	if (flags.precision >= 0)
	{
		write(1, ".", 1);
		ft_putnbr_fd(flags.precision, 1);
	}
	return (bytes_printed);
}

/*
** Reads conversion char and calls it's function.
** Returns bytes written if conversion char is valid.
** Returns -1 if conversion char is invalid.
*/

int	conversion_caller(char conversion_type, va_list start, t_flags flags, int n)
{
	if (conversion_type == 'c')
		return (convert_character(start, flags));
	if (conversion_type == 's')
		return (convert_string(start, flags));
	if (conversion_type == 'p')
		return (convert_pointer(start, flags));
	if (conversion_type == 'd')
		return (convert_digit(start, flags));
	if (conversion_type == 'i')
		return (convert_digit(start, flags));
	if (conversion_type == 'u')
		return (convert_udigit(start, flags));
	if (conversion_type == 'x')
		return (convert_hex(start, flags, 0));
	if (conversion_type == 'X')
		return (convert_hex(start, flags, 1));
	if (conversion_type == 'n')
		return (convert_n(start, flags, n));
	if (conversion_type == 'f')
		return (convert_double(start, flags));
	if (conversion_type == 'g')
		return (convert_g(start, flags));
	if (conversion_type == 'e')
		return (convert_e(start, flags));
	return (-1);
}

/*
** t_flags contains boolean values for each flag.
** Reads in flags in sequence like real printf:
** 1. Sequence one: '#0- +'.
** 2. Sequence two: Minimum Field Width and Precision.
** if the values are too large, it will return an error.
** 3. Sequence three: Length Modifiers ('l', 'll', 'h' and 'hh').
** In the sequence functions:
** index i is incremented to point to the conversion char.
** Definitions of these functions are in flagsequence.c
**
** If the conversion character is invalid, it will print the S1 and S2 flags,
** only one copy of each flag, in the expected order.
**
** If the flags and conversion character are correct,
** the appropriate conversion function is called.
** Return value is equal to the bytes written, or -1 on error.
** Index i will be incremented to point to the next char.
*/

int	conversion(const char *format, size_t *i, va_list start, int n)
{
	t_flags	flags;
	int		return_value;

	flags = flags_sequence_one(format, i);
	flags = flags_sequence_two(format, i, flags, start);
	if (flags.field_width == -2 || flags.precision == -2)
		return (-1);
	flags = flags_sequence_three(format, i, flags);
	if (format[*i] == '%')
	{
		(*i)++;
		return (convert_percentage(flags));
	}
	else
		return_value = conversion_caller(format[*i], start, flags, n);
	if (return_value == -1)
		return (print_conversion_error(flags));
	(*i)++;
	return (return_value);
}

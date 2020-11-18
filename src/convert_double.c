/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_double.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/18 16:37:09 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/18 18:30:52 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

// check for nan, inf and update zero flag?
static int	get_fchars_count(t_bits nbr, t_flags flags, int *tenth_exp)
{
	int	decimal_digits;
	int	chars;

	if (nbr.bitfields.expo != 2047)
	{
		decimal_digits == ft_get_tenth_exp(nbr.number);
		chars = flags.precision == -1 ? 6 : flags.precision;
	}
	else
		chars = 3;
	if (flags.precision != 0 || (flags.precision == 0 && flags.hash == 1))
		chars++;
	if (nbr.bitfields.sign == 1 || flags.space == 1 || flags.plus == 1)
		chars++;;
	chars += decimal_digits > 0 ? decimal_digits : 1;
	return (chars);
}

/*
** Edge cases:
** 1. +inf or -inf: Exponent == 2047(max val) and Mantissa == 0.
** The sign (most significant bit) represents the positive or negative value.
** 2. nan (not a number): Exponent == 2047(max val) and Mantissa != 0.
** 3. Zero: Exponent == 0 && Mantissa == 0. Can be positive or negative.
** 4. Subnormals: Exponent == 0 && Mantissa != 0.
*/

static int	put_floating_point_number(t_bits nbr, t_flags flags, int chars)
{
	if (nbr.bitfields.sign == 0 && flags.plus == 1)
	{
		if (write(1, "+", 1) == -1)
			return (-1);
	}
	else if (nbr.bitfields.sign == 0 && flags.space == 0)
		if (write(1, " ", 1) == -1)
			return (-1);
}

/*
** The union t_bits, contains a struct with bitfield.
** These fields represent three things in the double:
** 1. The sign (positive or negative)
** 2. The exponent (mantissa * 2^exponent = actual double value).
** 3. The mantissa (the binary fraction of the double)
** If the exponent != 0, then the mantissa is represented like 1.00111011....
** where the digits after the radix point are the final 52 bits of the double.
** For inf or nan: leading zero's are not printed.
*/

int			convert_float(va_list start, t_flags flags)
{
	t_bits	nbr;
	int		tenth_exp;
	int		chars;

	nbr.number = va_arg(start, double);
	if (flags.minus == 1 || nbr.bitfields.expo == 2047)
		flags.zero = 0;
	chars = get_fchars_count(nbr, flags, &tenth_exp);
	if (flags.zero == 0 && flags.minus == 0 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, 0) == -1)
			return (-1);
	
	// print point if there were no decimals printed, but hash specified it should be.
	if (flags.precision == 0 && flags.hash == 1)
		if (write(1, ".", 1) == -1)
			return (-1);
	if (flags.minus == 1 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, 0) == -1)
			return (-1);
	return (chars > flags.field_width ? chars : flags.field_width);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_double.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/18 16:37:09 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/20 09:08:19 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

static int	double_edgecases(t_bits nbr, t_flags flags)
{
	if (nbr.bitfields.expo == 2047 && nbr.bitfields.mant != 0)
	{
		if (write(1, "nan", 3) == -1)
			return (-1);
		return (0);
	}
	if (nbr.bitfields.sign == 1)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
	}
	else if (flags.plus == 1)
	{
		if (write(1, "+", 1) == -1)
			return (-1);
	}
	else if (flags.space == 1)
		if (write(1, " ", 1) == -1)
			return (-1);
	if (nbr.bitfields.expo == 2047 && nbr.bitfields.mant == 0)
	{
		if (write(1, "inf", 3) == -1)
			return (-1);
	}
	return (0);
}

/*
** Edge cases:
** 1. +inf or -inf: Exponent == 2047(max val) and Mantissa == 0.
** The sign (most significant bit) represents the positive or negative value.
** 2. nan (not a number): Exponent == 2047(max val) and Mantissa != 0.
** 3. Zero: Exponent == 0 && Mantissa == 0. Can be positive or negative.
** 4. Subnormals: Exponent == 0 && Mantissa != 0.
** Prints sign and leading zero's, or inf/nan.
*/

static int	ft_printf_double(t_bits nbr, t_flags flags, int chars)
{
	if (double_edgecases(nbr, flags) == -1)
		return (-1);
	if (nbr.bitfields.expo == 2047)
		return (chars);
	if (flags.zero == 1 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, 1) == -1)
			return (-1);
	nbr.bitfields.sign = 0;
	if (ft_put_double(nbr.number, flags.precision) == -1)
		return (-1);
	if (flags.precision == 0 && flags.hash == 1)
		if (write(1, ".", 1) == -1)
			return (-1);
	return (chars);
}

/*
** If 'nan' chars = 3.
** If 'inf' chars = 3 or 4 (depends on sign/flags)
** Else chars = integer count + precision(fraction count) + possible sign.
** If integer count is <= 0; we have to put 1 number before the radix point.
** If precision == 0 and hash is not active, we won't write a radix point
*/

static int	get_fchars_count(t_bits nbr, t_flags flags)
{
	int	chars;
	int	decimals;

	if (nbr.bitfields.expo == 2047 && nbr.bitfields.mant != 0)
		return (3);
	if (nbr.bitfields.expo == 2047 && nbr.bitfields.mant == 0)
		chars = 3;
	else
	{
		decimals = ft_get_tenth_exp(nbr.number);
		chars = flags.precision == -1 ? 6 : flags.precision;
	}
	if (nbr.bitfields.sign == 1 || flags.space == 1 || flags.plus == 1)
		chars++;
	if (nbr.bitfields.expo == 2047)
		return (chars);
	chars += decimals > 0 ? decimals + 1 : 1;
	if (flags.precision != 0 || flags.hash == 1)
		chars++;
	return (chars);
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

int			convert_double(va_list start, t_flags flags)
{
	t_bits	nbr;
	int		chars;

	nbr.number = va_arg(start, double);
	if (flags.precision < 0)
		flags.precision = 6;
	if (flags.minus == 1 || nbr.bitfields.expo == 2047)
		flags.zero = 0;
	chars = get_fchars_count(nbr, flags);
	if (flags.zero == 0 && flags.minus == 0 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, 0) == -1)
			return (-1);
	if (ft_printf_double(nbr, flags, chars) == -1)
		return (-1);
	if (flags.minus == 1 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, 0) == -1)
			return (-1);
	return (chars > flags.field_width ? chars : flags.field_width);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_e.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/20 08:49:01 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/20 09:20:19 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static int	ft_printf_e(t_bits nbr, t_flags flags, int chars)
{
	if (nbr.bitfields.expo == 2047 && nbr.bitfields.mant != 0)
		return (write(1, "nan", 3));
	if (nbr.bitfields.sign == 1)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
	}
	if (flags.plus == 1)
	{
		if (write(1, "+", 1) == -1)
			return (-1);
	}
	else if (flags.space == 1)
		if (write(1, " ", 1) == -1)
			return (-1);
	if (flags.zero == 1 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, flags.zero) == -1)
			return (-1);
	if (nbr.bitfields.expo == 2047)
		return (write(1, "inf", 1));
	// put double in scientific notation and that's it.
	return (chars);
}

static int	get_echars_count(t_bits nbr, t_flags flags)
{
	int	chars;

	if (nbr.bitfields.expo == 2047 && nbr.bitfields.mant != 0)
		return (3);
	else if (nbr.bitfields.expo == 2047)
		chars = 3;
	else
		chars = 1 + flags.precision;
	if (nbr.bitfields.sign == 1 || flags.plus == 1 || flags.space == 1)
		chars++;
	if (flags.hash == 0 && flags.precision == 0)
		return (chars);
	if (nbr.bitfields.expo != 2047)
		chars++;
	return (chars);
}

int			convert_e(va_list start, t_flags flags)
{
	t_bits	nbr;
	int		chars;

	if (flags.precision < 0)
		flags.precision = 6;
	nbr.number = va_arg(start, double);
	if (flags.minus == 1 || nbr.bitfields.expo == 2047)
		flags.zero = 0;
	chars = get_echars_count(nbr, flags);
	if (flags.minus == 0 && flags.zero == 0 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, 0) == -1)
			return (-1);
	if (ft_printf_e(nbr, flags, chars) == -1)
		return (-1);
	if (flags.hash == 1 && flags.precision == 0)
		if (write(1, ".", 1) == -1)
			return (-1);
	if (flags.minus == 1 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, 0) == -1)
			return (-1);
	return (chars > flags.field_width ? chars : flags.field_width);
}

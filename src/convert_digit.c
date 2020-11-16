/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_digit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 09:34:01 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/15 16:22:48 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

static long long	get_nbr(va_list start, t_flags flags)
{
	long long	nbr;

	if (flags.l == 1)
		nbr = (long)va_arg(start, long);
	else if (flags.ll == 1)
		nbr = va_arg(start, long long);
	else if (flags.h == 1)
		nbr = (short)va_arg(start, int);
	else if (flags.hh == 1)
		nbr = (signed char)va_arg(start, int);
	else
		nbr = (int)va_arg(start, int);
	return (nbr);
}

static int			get_dchars_count(long long nbr, t_flags *flags)
{
	int	chars;

	if ((*flags).minus == 0 && (*flags).precision == -1 && (*flags).zero == 1)
	{
		(*flags).precision = (*flags).field_width;
		if (nbr < 0 || (*flags).plus == 1 || (*flags).space == 1)
			(*flags).precision--;
		(*flags).field_width = 0;
	}
	if ((*flags).precision == 0 && nbr == 0)
		return (0);
	if ((*flags).precision > 0)
		(*flags).zero = 0;
	chars = (ssize_t)ft_numlen_base(nbr, 10);
	chars = chars > (*flags).precision ? chars : (*flags).precision;
	if (nbr < 0 || ((*flags).plus == 1 || (*flags).space == 1))
		chars++;
	return (chars);
}

/*
** Flags: "'0', '-', ' ', '+', MFW, OP, l, ll, h, hh".
** 'l' = long 'll' = long long
** 'h' = short , 'hh' = signed char.
*/

int					convert_digit(va_list start, t_flags flags)
{
	long long	nbr;
	int			chars;

	nbr = get_nbr(start, flags);
	chars = get_dchars_count(nbr, &flags);
	if (flags.minus == 0 && flags.field_width > chars)
		if (put_field_width(flags.field_width - chars,
		flags.zero) == -1)
			return (-1);
	if (nbr >= 0 && flags.plus == 1)
	{
		if (write(1, "+", 1) == -1)
			return (-1);
	}
	else if (nbr >= 0 && flags.space == 1)
		if (write(1, " ", 1) == -1)
			return (-1);
	if (!(nbr == 0 && flags.precision == 0))
		if (ft_putll(nbr, flags.precision) == -1)
			return (-1);
	if (flags.minus == 1 && flags.field_width > chars)
		if (put_field_width(flags.field_width - chars, 0) == -1)
			return (-1);
	return (flags.field_width > chars ?
	flags.field_width : chars);
}

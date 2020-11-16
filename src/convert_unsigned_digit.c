/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_unsigned_digit.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 09:34:01 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/15 16:24:28 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static unsigned long long	get_unbr(va_list start, t_flags flags)
{
	unsigned long long	nbr;

	if (flags.l == 1)
		nbr = (unsigned long)va_arg(start, unsigned long);
	else if (flags.ll == 1)
		nbr = va_arg(start, unsigned long long);
	else if (flags.h == 1)
		nbr = (unsigned short)va_arg(start, unsigned int);
	else if (flags.hh == 1)
		nbr = (unsigned char)va_arg(start, unsigned int);
	else
		nbr = (unsigned int)va_arg(start, unsigned int);
	return (nbr);
}

/*
** replaces precision with field_width if there's no precision
** and the '0' flag is activated.
** removes '0' flag if precision is active.
*/

static int					get_udchars_count(long long nbr, t_flags *flags)
{
	int	chars;

	if (flags->precision == 0 && nbr == 0)
		return (0);
	if (flags->precision >= 0)
		flags->zero = 0;
	chars = ft_unumlen_base(nbr, 10);
	return (chars > flags->precision ? chars : flags->precision);
}

/*
** Flags: "'0', '-', MFW, OP, l, ll, h, hh".
** 'l' = unsigned long 'll' = unsigned long long
** 'h' = unsigned short , 'hh' = unsigned char.
** Saves any data type as unsigned long long,
** this way it can print any digit with typecasting.
*/

int							convert_udigit(va_list start, t_flags flags)
{
	unsigned long long	nbr;
	int					chars;

	nbr = get_unbr(start, flags);
	chars = get_udchars_count(nbr, &flags);
	if (flags.minus == 0 && flags.field_width > chars)
		if (put_field_width(flags.field_width - chars, flags.zero) == -1)
			return (-1);
	if (!(nbr == 0 && flags.precision == 0))
		if (ft_putllu(nbr, flags.precision) == -1)
			return (-1);
	if (flags.minus == 1 && flags.field_width > chars)
		if (put_field_width(flags.field_width - chars, 0) == -1)
			return (-1);
	return (chars > flags.field_width ? chars : flags.field_width);
}

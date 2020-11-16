/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_unsigned_digit.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 09:34:01 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/16 14:26:49 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

unsigned long long	get_unsigned_nbr(va_list start, t_flags flags)
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

int					get_uchars_count(unsigned long long nbr, t_flags flags)
{
	int	len;

	if (nbr == 0 && flags.precision == 0)
		return (0);
	len = ft_unumlen_base(nbr, 10);
	return (len > flags.precision ? len : flags.precision);
}

/*
** FLAGS: '0' '-' MFW OP (LENMOD)
** Saves any data type as unsigned long long,
** this way it can print any digit with typecasting.
*/

int					convert_udigit(va_list start, t_flags flags)
{
	unsigned long long	nbr;
	int					chars;

	if (flags.precision >= 0 || flags.minus == 1)
		flags.zero = 0;
	nbr = get_unsigned_nbr(start, flags);
	chars = get_uchars_count(nbr, flags);
	if (flags.minus == 0 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, flags.zero) == -1)
			return (-1);
	if (nbr != 0 || flags.precision != 0)
		if (ft_putllu(nbr, flags.precision) == -1)
			return (-1);
	if (flags.minus == 1 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, flags.zero) == -1)
			return (-1);
	return (chars > flags.field_width ? chars : flags.field_width);
}

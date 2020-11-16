/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_hex.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 15:10:50 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/15 16:38:12 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

static unsigned long long	get_uhnbr(va_list start, t_flags flags)
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
** Replace precision with field_width
** if no precision specified and '0' flag is active.
** Returns total chars that will be printed, excluding field width.
*/

int							get_xchars_toprint(unsigned long long nbr,
							t_flags *flags)
{
	int	chars;

	chars = 0;
	chars += ft_unumlen_base(nbr, 16);
	if (flags->precision >= 0)
		flags->zero = 0;
	if (nbr == 0 && flags->precision == 0)
		return (0);
	if (flags->field_width > 0 && flags->minus == 0 && flags->zero == 1 && flags->precision == -1)
	{
		flags->precision = flags->field_width;
		if (flags->hash == 1)
			flags->precision -= 2;
		flags->field_width = 0;
	}
	chars = chars > flags->precision ? chars : flags->precision;
	if (flags->hash == 1)
		chars += 2;
	return (chars);
}

/*
** FLAGS: '#' '0' '-' MFW OP
** 'l' = unsigned long 'll' = unsigned long long
** 'h' = unsigned short 'hh' unsigned char
*/

int							convert_hex(va_list start, t_flags flags,
							int upcase)
{
	unsigned long long	nbr;
	int					chars;

	nbr = get_uhnbr(start, flags);
	chars = get_xchars_toprint(nbr, &flags);
	if (flags.minus == 0 && flags.field_width > chars)
		if (put_field_width(flags.field_width - chars, flags.zero) == -1)
			return (-1);
	if (nbr != 0 && flags.hash == 1 && upcase == 0)
		if (write(1, "0x", 2) == -1)
			return (-1);
	if (nbr != 0 && flags.hash == 1 && upcase == 1)
		if (write(1, "0X", 2) == -1)
			return (-1);
	if (!(nbr == 0 && flags.precision == 0))
		if (ft_putllu_base(nbr, 16, flags.precision, upcase) == -1)
			return (-1);
	if (flags.minus == 1 && flags.field_width > chars)
		if (put_field_width(flags.field_width - chars, 0) == -1)
			return (-1);
	return (chars > flags.field_width ? chars : flags.field_width);
}

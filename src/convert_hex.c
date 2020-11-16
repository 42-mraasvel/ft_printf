/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_hex.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 15:10:50 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/16 14:53:10 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

int	get_xchars_count(unsigned long long nbr, t_flags flags)
{
	int	len;

	len = 0;
	if (flags.precision == 0 && nbr == 0)
		return (0);
	len = ft_unumlen_base(nbr, 16);
	len = len > flags.precision ? len : flags.precision;
	if (flags.hash == 1)
		len += 2;
	return (len);
}

/*
** FLAGS: '#' '0' '-' MFW OP
** 'l' = unsigned long 'll' = unsigned long long
** 'h' = unsigned short 'hh' unsigned char
** Prints alphabetical chars in uppercase if upcase != 0.
*/

int	convert_hex(va_list start, t_flags flags, int upcase)
{
	unsigned long long	nbr;
	int					chars;

	if (flags.precision >= 0 || flags.minus == 1)
		flags.zero = 0;
	nbr = get_unsigned_nbr(start, flags);
	chars = get_xchars_count(nbr, flags);
	if (flags.zero == 0 && flags.minus == 0 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, 0) == -1)
			return (-1);
	if (flags.zero == 1)
	{
		if (ft_putllu_base(nbr, 16, flags.field_width - chars, upcase) == -1)
			return (-1);
	}
	else if (ft_putllu_base(nbr, 16, flags.precision, upcase) == -1)
		return (-1);
	if (flags.minus == 1 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, 0) == -1)
			return (-1);
	return (chars > flags.field_width ? chars : flags.field_width);
}

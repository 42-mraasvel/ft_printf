/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_pointer.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 21:24:08 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/22 13:18:29 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*
** Flags: '-', Field Width
** Return chars written or -1 on any error.
*/

int			convert_pointer(va_list start, t_flags flags)
{
	int					chars;
	unsigned long long	p;

	p = (unsigned long long)va_arg(start, void*);
	chars = ft_unumlen_base(p, 16) + 2;
	if (flags.minus == 0 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, 0) == -1)
			return (-1);
	if (write(1, "0x", 2) == -1)
		return (-1);
	if (ft_putllu_base(p, 16, 0, 0) == -1)
		return (-1);
	if (flags.minus == 1 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, 0) == -1)
			return (-1);
	return (chars > flags.field_width ? chars : flags.field_width);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_string.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 20:07:53 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/16 09:13:17 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

static int	get_schars(char *string, t_flags flags)
{
	int	len;

	if (string == 0)
		len = 6;
	else
		len = ft_strlen(string);
	if (flags.precision >= 0)
		len = len < flags.precision ? len : flags.precision;
	return (len);
}

/*
** Flags: '-' (left or right FW)
** Field Width (min chars total), Precision (max from string)
** '%ls' could mean wchar_t string. (bonus)
*/

int			convert_string(va_list start, t_flags flags)
{
	int		chars;
	char	*string;

	string = va_arg(start, char*);
	chars = get_schars(string, flags);
	if (flags.minus == 0 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, 0) == -1)
			return (-1);
	if (string == 0)
	{
		if (ft_putstr_p("(null)", chars) == -1)
			return (-1);
	}
	else if (ft_putstr_p(string, chars) == -1)
		return (-1);
	if (flags.minus == 1 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, 0) == -1)
			return (-1);
	return (chars > flags.field_width ? chars : flags.field_width);
}

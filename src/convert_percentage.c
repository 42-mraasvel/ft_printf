/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_percentage.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 15:03:58 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/15 16:13:33 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

#include <stdio.h>

/*
** Flags: '-' '0' Field Width
*/

int	convert_percentage(t_flags flags)
{
	if (flags.minus == 0 && flags.field_width > 1)
		if (put_fw(flags.field_width - 1, flags.zero) == -1)
			return (-1);
	if (write(1, "%", 1) == -1)
		return (-1);
	if (flags.minus == 1 && flags.field_width > 1)
		if (put_fw(flags.field_width - 1, 0) == -1)
			return (-1);
	return (flags.field_width > 1 ? flags.field_width : 1);
}

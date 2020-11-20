/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_e.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/20 08:49:01 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/20 08:53:12 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_echars_count(t_bits nbr, t_flags flags)
{
	int	chars;

	
}

int			convert_e(va_list start, t_flags flags)
{
	t_bits	nbr;
	int		chars;

	nbr.number = va_arg(start, double);
	chars = get_echars_count(nbr, flags);
}

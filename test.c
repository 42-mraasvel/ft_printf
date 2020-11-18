/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 21:13:55 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/18 11:43:13 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "src/libft.h"
#include "src/ft_printf.h"

/*
** '#' '0' '-' ' ' '+'
** Field Width, Precision, '*' .*
** 'l' 'll' 'h' 'hh'
*/

void	printf_compare_function(char *format)
{
	int	return_value;
	int	ft_return_value;

	return_value = printf(format, 3, -12);
	ft_return_value = ft_printf(format, 3, -12);
	printf("return printf: %d\n", return_value);
	printf("return ft_printf: %d\n", ft_return_value);
}

int	main(void)
{
	printf_compare_function("%.*i");
	return (0);
}

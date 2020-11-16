/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 21:13:55 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/16 10:14:51 by mraasvel      ########   odam.nl         */
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

int	main(void)
{
	int return_val;

	ft_printf("|");
	return_val = ft_printf("%8.5d", 0);
	ft_printf("|\n");
	printf("return: %d\n", return_val);
	return (0);
}

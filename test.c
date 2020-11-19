/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 21:13:55 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/16 10:26:45 by mraasvel      ########   odam.nl         */
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
	int	(*print)(const char *format, ...);

	print = &printf;
	print("|");
	return_val = printf("%#x", 0);
	print("|\n");
	print("return: %d\n", return_val);
	return (0);
}

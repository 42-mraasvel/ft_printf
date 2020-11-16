/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 21:13:55 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/15 16:35:42 by mraasvel      ########   odam.nl         */
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
	printf("ft_printf:\n");
	ft_printf("|%0x|", 0);
	printf("\nprintf:\n");
	printf("|%0x|", 0);
	printf("\n");
	return (0);
}

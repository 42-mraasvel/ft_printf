/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.cß                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 21:13:55 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/19 08:31:32 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <wchar.h>
#include <float.h>
#include <locale.h>
#include "src/libft.h"
#include "src/ft_printf.h"

union				test
{
	double			v;
	struct 			s_test
	{
		unsigned long long	mant : 52;
		unsigned int	expo : 11;
		unsigned int	sign : 1;
	}				s;
};


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
	union test	un;

	un.v = 1238;
	put_binary_representation_of_area(&un.v, 8);
	printf("\n");
	un.s.expo = 2047;
	un.s.sign = 0;
	un.s.mant = 0;
	printf("%+.0f\n", un.v);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/19 18:58:42 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/19 19:17:00 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <wchar.h>
#include <float.h>
#include <string.h>
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
	int			ret;
	int			ft_ret;

	un.v = 0.000012345;
	// put_binary_representation_of_area(&un.v, 8);
	// printf("\n");
	// un.s.expo = 0;
	// un.s.sign = 0;
	// un.s.mant = 0;
	ret = printf("|%g|\n", un.v);
	// ft_ret = ft_printf("|%#+012.*f|\n", 29347, un.v);
	printf("\nreturn: %d\nft_ret: %d\n", ret, ft_ret);
	// printf("len: %ld\n", strlen("134217728.000073"));
	return (0);
}

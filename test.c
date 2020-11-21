/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/20 19:26:39 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/21 17:07:37 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <float.h>
#include "src/ft_printf.h"
#include "src/ft_double.h"

typedef union	u_f_test
{
	double			value;
	struct		bitfield
	{
		uint64_t	mantissa : 52;
		uint16_t	exponent : 11;
		uint8_t		sign : 1;
	}				bits;
}				f_test;

void	test_num(int num, int (*print)(const char *format, ...))
{
	print("TEST_E|%2d|:\t", num);
}

void	put_ret(int ret, int (*print)(const char *format, ...))
{
	print("\tReturn value: %d|\n", ret);
}

int		test_e(int (*print)(const char *format, ...))
{
	int	ret;
	f_test nbr;

	nbr.bits.mantissa = 0;
	nbr.bits.exponent = 2047;
	nbr.bits.sign = 1;
	test_num(0, print); ret = print("|%e|", nbr.value);
	put_ret(ret, print);
	nbr.bits.mantissa = 1;
	nbr.bits.exponent = 2047;
	nbr.bits.sign = 1;
	test_num(0, print); ret = print("|%e|", nbr.value);
	put_ret(ret, print);
	nbr.bits.mantissa = 1;
	nbr.bits.exponent = 2047;
	nbr.bits.sign = 0;
	test_num(0, print); ret = print("|%e|", nbr.value);
	put_ret(ret, print);
	nbr.bits.mantissa = 0;
	nbr.bits.exponent = 2047;
	nbr.bits.sign = 0;
	test_num(0, print); ret = print("|%e|", nbr.value);
	put_ret(ret, print);
	nbr.bits.mantissa = 0;
	nbr.bits.exponent = 2047;
	nbr.bits.sign = 1;
	test_num(0, print); ret = print("|%-10e|", nbr.value);
	put_ret(ret, print);
	nbr.bits.mantissa = 1;
	nbr.bits.exponent = 2047;
	nbr.bits.sign = 1;
	test_num(0, print); ret = print("|%010e|", nbr.value);
	put_ret(ret, print);
	nbr.bits.mantissa = 1;
	nbr.bits.exponent = 2047;
	nbr.bits.sign = 0;
	test_num(0, print); ret = print("|%#-5.0e|", nbr.value);
	put_ret(ret, print);
	nbr.bits.mantissa = 0;
	nbr.bits.exponent = 2047;
	nbr.bits.sign = 0;
	test_num(0, print); ret = print("|%#+05.1e|", nbr.value);
	put_ret(ret, print);
	return (0);
}

/*
** '#' '0' '-' ' ' '+'.
** FW / Precision
*/

int		main(int argc, char **argv)
{
	ft_printf("%.11e\n", 0.000000000010000000);
	// if (argc == 1)
	// {
	// 	ft_printf("FT_PRINTF\n");
	// 	test_e(&ft_printf);
	// }
	// else
	// {
	// 	printf("PRINTF\n");
	// 	test_e(&printf);
	// }
	return (0);
}

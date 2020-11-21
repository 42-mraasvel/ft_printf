/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/20 19:26:39 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/21 13:15:20 by mraasvel      ########   odam.nl         */
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
	print("TEST_F|%2d|:\t", num);
}

void	put_ret(int ret, int (*print)(const char *format, ...))
{
	print("\tReturn value: %d|\n", ret);
}

int		test_f(int (*print)(const char *format, ...))
{
	int	ret;
	f_test nbr;

	test_num(0, print); ret = print("|%f|", 1.0);
	put_ret(ret, print);
	test_num(1, print); ret = print("|%#f|", 1.0);
	put_ret(ret, print);
	test_num(2, print); ret = print("|%.0f|", 1.0);
	put_ret(ret, print);
	test_num(3, print); ret = print("|%#.0f|", 1.0);
	put_ret(ret, print);
	test_num(4, print); ret = print("|%#.5f|", 12345.67890);
	put_ret(ret, print);
	test_num(5, print); ret = print("|%010.0f|", 12345.67890);
	put_ret(ret, print);
	test_num(6, print); ret = print("|%#010.0f|", 12345.67890);
	put_ret(ret, print);
	test_num(7, print); ret = print("|%+010.0f|", 12345.67890);
	put_ret(ret, print);
	test_num(8, print); ret = print("|%+010.0f|", -12345.67890);
	put_ret(ret, print);
	test_num(9, print); ret = print("|%+010.0f|", -0.0);
	put_ret(ret, print);
	test_num(10, print); ret = print("|% 010.0f|", 1234.0);
	put_ret(ret, print);
	test_num(11, print); ret = print("|% 010.0f|", 0.0);
	put_ret(ret, print);
	test_num(12, print); ret = print("|% 010.0f|", -0.0);
	put_ret(ret, print);
	test_num(13, print); ret = print("|%0*.*f|", 0, 0, -0.0);
	put_ret(ret, print);
	test_num(14, print); ret = print("|%+*.*f|", 0, 0, 0.0);
	put_ret(ret, print);
	test_num(15, print); ret = print("|%+*.*f|", 0, -100, 0.0);
	put_ret(ret, print);
	test_num(16, print); ret = print("|%+*.*f|", -10, 0, 0.0);
	put_ret(ret, print);
	test_num(17, print); ret = print("|%+*.f|", -1, 0.0);
	put_ret(ret, print);
	test_num(18, print); ret = print("|%+*.f|", 0, 0.0);
	put_ret(ret, print);
	test_num(19, print); ret = print("|%+-12f|", 0.0);
	put_ret(ret, print);
	test_num(20, print); ret = print("|%.10f|", 1.00000000049);
	put_ret(ret, print);
	test_num(21, print); ret = print("|%.0f|", 9.4999999999999999);
	put_ret(ret, print);
	test_num(22, print); ret = print("|%.0f|", 8.500000000000001);
	put_ret(ret, print);
	test_num(23, print); ret = print("|%.0f|", 8.50000000000000000);
	put_ret(ret, print);
	test_num(24, print); ret = print("|%.0f|", 7.50000000000000000);
	put_ret(ret, print);
	nbr.bits.exponent = 2047;
	nbr.bits.mantissa = 0;
	nbr.bits.sign = 1;
	test_num(25, print); ret = print("|%.0f|", nbr.value);
	put_ret(ret, print);
	test_num(26, print); ret = print("|%10f|", nbr.value);
	put_ret(ret, print);
	test_num(27, print); ret = print("|%010f|", nbr.value);
	put_ret(ret, print);
	test_num(28, print); ret = print("|%#-10.1f|", nbr.value);
	put_ret(ret, print);
	nbr.bits.exponent = 2047;
	nbr.bits.mantissa = 0;
	nbr.bits.sign = 0;
	test_num(29, print); ret = print("|%.0f|", nbr.value);
	put_ret(ret, print);
	test_num(30, print); ret = print("|%+10f|", nbr.value);
	put_ret(ret, print);
	test_num(31, print); ret = print("|%+010f|", nbr.value);
	put_ret(ret, print);
	test_num(32, print); ret = print("|%#-10.1f|", nbr.value);
	put_ret(ret, print);
	nbr.bits.exponent = 2047;
	nbr.bits.mantissa = 1;
	nbr.bits.sign = 0;
	test_num(33, print); ret = print("|%.0f|", nbr.value);
	put_ret(ret, print);
	test_num(33, print); ret = print("|%+10f|", nbr.value);
	put_ret(ret, print);
	test_num(34, print); ret = print("|%+010f|", nbr.value);
	put_ret(ret, print);
	test_num(35, print); ret = print("|%#-10.1f|", nbr.value);
	put_ret(ret, print);
	nbr.bits.exponent = 2047;
	nbr.bits.mantissa = 1;
	nbr.bits.sign = 1;
	test_num(36, print); ret = print("|%.0f|", nbr.value);
	put_ret(ret, print);
	test_num(37, print); ret = print("|%10f|", nbr.value);
	put_ret(ret, print);
	test_num(38, print); ret = print("|%010f|", nbr.value);
	put_ret(ret, print);
	test_num(39, print); ret = print("|%#-10.1f|", nbr.value);
	put_ret(ret, print);
	test_num(40, print); ret = print("|%#-10.0f|", 1.499999999999999999999999999);
	put_ret(ret, print);
	test_num(41, print); ret = print("|%010.0f|", 1.499999999999999);
	put_ret(ret, print);
	test_num(42, print); ret = print("|%010.0f|", 1.4999999999999999);
	put_ret(ret, print);
	test_num(43, print); ret = print("|%010.0f|", 1.5);
	put_ret(ret, print);
	test_num(44, print); ret = print("|%010.0f|", 0.5);
	put_ret(ret, print);
	test_num(45, print); ret = print("|%.15f|", 0.999999999999999);
	put_ret(ret, print);
	test_num(46, print); ret = print("|%.10f|", 1234567890.1234567890);
	put_ret(ret, print);
	test_num(47, print); ret = print("|%.10f|", 0.123456789);
	put_ret(ret, print);
	test_num(48, print); ret = print("|%.15f|", 0.9999999999999999);
	put_ret(ret, print);
	test_num(49, print); ret = print("|%.15f|", 9.9999999999999999);
	put_ret(ret, print);
	test_num(50, print); ret = print("|%.15f|", 999999999999.9999999999999999);
	put_ret(ret, print);
	return (0);
}

/*
** '#' '0' '-' ' ' '+'.
** FW / Precision
*/

int		main(int argc, char **argv)
{
	if (argc == 1)
	{
		ft_printf("FT_PRINTF\n");
		test_f(&ft_printf);
	}
	else
	{
		printf("PRINTF\n");
		test_f(&printf);
	}
	return (0);
}

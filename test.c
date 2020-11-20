/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/19 18:58:42 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/20 18:32:25 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <wchar.h>
#include <float.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
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

void	ft_putchar_nonprint(int (*print)(const char *format, ...), char c)
{
	if (c == 0)
		print("\\0");
	else if (c == 7)
		print("\\a");
	else if (c == 8)
		print("\\b");
	else if (c == 9)
		print("\\t");
	else if (c == 10)
		print("\\n");
	else if (c == 11)
		print("\\v");
	else if (c == 12)
		print("\\f");
	else if (c == 13)
		print("\\r");
	else
		print("%c", c);
}

void	ft_putstr_nonprint(int (*print)(const char *format, ...), char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
	{
		ft_putchar_nonprint(print, s[i]);
		i++;
	}
}

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

void	test_edge_float(char *format)
{
	union test	uni;

	uni.s.sign = 0;
	uni.s.expo = 0;
	uni.s.mant = 0;
	printf("\tPositive zero: ");
	printf(format, uni.v);
	uni.s.sign = 1;
	uni.s.expo = 0;
	uni.s.mant = 0;
	printf("\tNegative zero: ");
	printf(format, uni.v);
	uni.s.sign = 0;
	uni.s.expo = 2047;
	uni.s.mant = 0;
	printf("\t+INF: ");
	printf(format, uni.v);
	uni.s.sign = 1;
	uni.s.expo = 2047;
	uni.s.mant = 0;
	printf("\t-INF: ");
	printf(format, uni.v);
	uni.s.sign = 0;
	uni.s.expo = 2047;
	uni.s.mant = 1;
	printf("\t+NaN: ");
	printf(format, uni.v);
	uni.s.sign = 1;
	uni.s.expo = 2047;
	uni.s.mant = 1;
	printf("\t-NaN: ");
	printf(format, uni.v);
}

/*
** All possible flags:
** '-' '0' '.' '*'  and min field width with all conversions.
** 'l' 'll' 'h' 'hh' '#' ' ' '+'.
*/

char	**generate_flags(char conversion_t)
{
	char	**formats;
	char	*string;
	int		n;

	n = 8;
	formats = (char**)ft_calloc((n + 1), sizeof(char*));
	if (formats == 0)
		return (0);
	string = ft_calloc(100, 1);
	if (string == 0)
		return (0);
	ft_memcpy(string, "%#", 2);
	string[2] = conversion_t;
	string[3] = '\n';
	formats[0] = ft_strdup(string);
	ft_memcpy(string, "%+", 2);
	string[2] = conversion_t;
	formats[1] = ft_strdup(string);
	ft_memcpy(string, "% ", 2);
	string[2] = conversion_t;
	formats[2] = ft_strdup(string);
	ft_memcpy(string, "%-10", 4);
	string[4] = conversion_t;
	string[5] = '\n';
	formats[3] = ft_strdup(string);
	ft_memcpy(string, "%010", 4);
	string[4] = conversion_t;
	formats[4] = ft_strdup(string);
	ft_memcpy(string, "%.10", 4);
	string[4] = conversion_t;
	formats[5] = ft_strdup(string);
	ft_memcpy(string, "%.1", 3);
	string[3] = conversion_t;
	string[4] = '\n';
	string[5] = '\0';
	formats[6] = ft_strdup(string);
	ft_memcpy(string, "%.0", 3);
	string[3] = conversion_t;
	formats[7] = ft_strdup(string);
	return (formats);
}

int	main(void)
{
	char	**formats;
	t_bits	val;

	val.number = 9.90041;
	ft_printf("%.0e\n", val.number);
	// printf("%.3g\n", 123.001);
	// formats = generate_flags('g');
	// int i = 0;
	// while (formats[i] != 0)
	// {
	// 	printf("printf(\"");
	// 	ft_putstr_nonprint(&printf, formats[i]);
	// 	printf("\");\n");
	// 	test_edge_float(formats[i]);
	// 	printf("\n");
	// 	i++;
	// }
	// free(formats);
	return (0);
}

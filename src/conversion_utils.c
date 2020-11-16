/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 19:43:46 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/14 21:42:58 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

int	put_n_chars_fast(int n, unsigned char c)
{
	size_t	remains;
	size_t	num;
	char	*large_buffer;

	remains = n % 10000;
	large_buffer = (char*)malloc(10000 * sizeof(char));
	if (large_buffer == 0)
		return (-1);
	ft_memset(large_buffer, c, 10000);
	num = n;
	while (num > 10000)
	{
		if (write(1, large_buffer, 10000) == -1)
		{
			free(large_buffer);
			return (-1);
		}
		num -= 10000;
	}
	if (write(1, large_buffer, remains) == -1)
		n = -1;
	free(large_buffer);
	return (n);
}

int	put_field_width(int field_width, int zero)
{
	int				bytes_written;
	unsigned char	c;

	bytes_written = 0;
	if (zero == 1)
		c = '0';
	else
		c = ' ';
	if (field_width > 10000)
	{
		if (put_n_chars_fast(field_width, c) == -1)
			return (-1);
		return (field_width);
	}
	while (bytes_written < field_width)
	{
		if (write(1, &c, 1) == -1)
			return (-1);
		bytes_written++;
	}
	return (field_width);
}

int	put_fw(int field_width, int zero)
{
	if (zero == 1)
	{
		if (ft_putnofc(field_width, '0') == -1)
			return (-1);
	}
	else if (ft_putnofc(field_width, ' ') == -1)
		return (-1);
	return (field_width);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_hex.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 21:25:13 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/14 10:37:55 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

static void		ft_str_toupper(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
}

static char		*get_base(void)
{
	char	*base;
	int		i;

	base = (char*)malloc(17 * sizeof(char));
	if (base == 0)
		return (0);
	base[16] = '\0';
	i = 0;
	while (i < 16)
	{
		base[i] = i < 10 ? i + '0' : i + 'a' - 10;
		i++;
	}
	return (base);
}

static int		put_hex(unsigned long long nbr, char *base)
{
	int len;
	int	return_value;

	len = 0;
	if (nbr != 0)
	{
		return_value = put_hex(nbr / 16, base);
		if (return_value == -1)
			return (-1);
		len += return_value;
		if (write(1, &base[nbr % 16], 1) == -1)
			return (-1);
		len++;
		return (len);
	}
	return (0);
}

static int		put_trailing_zeros(unsigned long long nbr, int min_len)
{
	int		numlen;
	ssize_t	bytes_written;

	numlen = 0;
	bytes_written = 0;
	while (nbr != 0)
	{
		nbr = nbr / 16;
		numlen++;
	}
	if (min_len > numlen)
		bytes_written = put_field_width(min_len - numlen, 1);
	return (bytes_written);
}

/*
** will print uppercase if it's not 0.
** min_len will print trailing zeros
*/

int				ft_putnbr_hex(unsigned long long nbr, int upcase, int min_len)
{
	char	*base;
	int		return_value;
	int		bytes_written;

	base = get_base();
	if (base == 0)
		return (-1);
	if (upcase != 0)
		ft_str_toupper(base);
	return_value = 0;
	if (min_len > 0)
		return_value = put_trailing_zeros(nbr, min_len);
	if (return_value == -1)
		return (-1);
	bytes_written = put_hex(nbr, base);
	if (bytes_written == -1)
		return (-1);
	free(base);
	return (bytes_written + return_value);
}

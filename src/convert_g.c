/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_g.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/20 10:07:03 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/20 15:46:18 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

/*
** takes string containing only the significant digits.
** We want to insert a radix point if power >= 0
** Remove trailing zero's if necessary (hash flag)
*/

static char	*modify_digits(char *digits, t_flags flags, int pow)
{
	int	len;

	if (flags.precision == pow + 1)
		digits = insert_radix_point(digits, pow);
	else if (pow >= 0)
		digits = insert_radix_point(digits, pow);
	if (digits == NULL)
		return (NULL);
	len = ft_strlen(digits) - 1;
	if (flags.hash == 0)
	{
		while (len > 0)
		{
			if (digits[len] != '0')
				break ;
			digits[len] = '\0';
			len--;
		}
	}
	return (digits);
}

static int	get_gchars_count(t_bits nbr, char *digits, t_flags flags, int pow)
{
	int	chars;

	chars = 0;
	if (nbr.bitfields.sign == 1 || flags.plus == 1 || flags.space == 1)
		chars++;
	if (!(flags.precision == pow + 1 && flags.hash == 0) && pow < 0)
		chars++;
	chars += ft_strlen(digits);
	if (flags.precision == pow + 1 && flags.hash == 0)
		chars--;
	if (pow < 0)
		chars += -pow;
	return (chars);
}

static int	print_digits(char *digits, t_flags flags, int pow, int chars)
{
	if (flags.zero == 1 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, flags.zero) == -1)
			return (-1);
	if (pow < 0)
	{
		if (write(1, "0.", 2) == -1)
			return (-1);
		if (ft_putnofc(-pow - 1, '0') == -1)
			return (-1);
	}
	if (flags.hash == 0 && flags.precision == pow + 1)
		digits[pow + 1] = '\0';
	if (ft_putstr(digits) == -1)
		return (-1);
	return (chars);
}

static int	output_g(t_bits nbr, char *digits, t_flags flags, int pow)
{
	int	chars;

	chars = get_gchars_count(nbr, digits, flags, pow);
	if (flags.minus == 1)
		flags.zero = 0;
	if (flags.minus == 0 && flags.zero == 0 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, 0) == -1)
			return (-1);
	if (nbr.bitfields.sign == 1)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
	}
	if (nbr.bitfields.sign == 0 && flags.plus == 1)
		if (write(1, "+", 1) == -1)
			return (-1);
	if (nbr.bitfields.sign == 0 && flags.space == 1)
		if (write(1, " ", 1) == -1)
			return (-1);
	if (print_digits(digits, flags, pow, chars) == -1)
		return (-1);
	if (flags.minus == 1 && flags.field_width > chars)
		if (put_fw(flags.field_width - chars, 0) == -1)
			return (-1);
	return (flags.field_width > chars ? flags.field_width : chars);
}

int			convert_g(va_list start, t_flags flags)
{
	t_bits	nbr;
	int		chars;
	int		pow;
	char	*digits;

	nbr.number = va_arg(start, double);
	if (nbr.bitfields.expo == 2047)
		return (convert_e_for_g(nbr, flags));
	pow = ft_get_tenth_exp(nbr.number);
	if (flags.precision < 0)
		flags.precision = 6;
	if (flags.precision == 0)
		flags.precision = 1;
	if (pow < -4 || pow > flags.precision)
		return (convert_e_for_g(nbr, flags));
	digits = extract_n_digits_from_double(nbr.number, flags.precision, 1);
	if (digits == NULL)
		return (-1);
	digits = modify_digits(digits, flags, pow);
	if (digits == NULL)
		return (-1);
	chars = output_g(nbr, digits, flags, pow);
	free(digits);
	return (chars);
}

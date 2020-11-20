/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_g.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/20 10:07:03 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/20 13:56:59 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"
#include <stdio.h> // rm

/*
** takes string containing only the significant digits.
** Add leading zero's if necessary
** We want to insert a radix point if necessary
** Remove trailing zero's if necessary
*/

// step 1: + 0.000 if pow < 0
// step 2: <digits before radix point>+. <digits after radix point> if pow >= 0
// step 3: 1.2000 before, 1.2 after: leave if hash flag is active.

static int	modify_digits(char *digits, t_flags flags, int pow)
{
	int	len;

	len = ft_strlen(digits);
}

// static int	get_gchars_count(char *digits, t_flags flags, int pow)
// {
	
// }

int			convert_g(va_list start, t_flags flags)
{
	t_bits	nbr;
	// int		chars;
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
	if (digits == 0)
		return (-1);
	printf("digits: %s\n", digits);
	free(digits);
	return (0);
}

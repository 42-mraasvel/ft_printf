/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_double.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/20 20:47:54 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/21 12:20:22 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLE_H
# define DOUBLE_H

# include <stdint.h>

typedef union	u_double
{
	double			value;
	struct		s_bitfield
	{
		uint64_t	mantissa : 52;
		uint16_t	exponent : 11;
		uint8_t		sign : 1;
	}				bits;
}				t_double;

char			*ft_dtoa_f(double nbr, int precision);
char			*ft_round_f(char *nbr, char *rounder);

int				ft_numlen_dbl(double num);
double			ft_pow(double x, double y);

#endif
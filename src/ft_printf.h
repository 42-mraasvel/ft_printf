/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 09:00:04 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/19 08:29:19 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** Includes for prototypes.
*/

# include <stddef.h>
# include <stdarg.h>

/*
** Signs to signal which flags are on.
*/

typedef struct		s_flags
{
	int		hash;
	int		zero;
	int		minus;
	int		space;
	int		plus;
	int		field_width;
	int		precision;
	int		l;
	int		ll;
	int		h;
	int		hh;
}					t_flags;

int					ft_printf(const char *format, ...);

/*
** Union to extract bits from double;
** for floating point conversion.
*/

typedef union		u_bits
{
	double			number;
	struct 			s_bitfields
	{
		unsigned long long	mant : 52;
		unsigned int	expo : 11;
		unsigned int	sign : 1;
	}				bitfields;
}					t_bits;

/*
** conversion.c
*/

int					conversion(const char *format, size_t *i, va_list start, int n);

/*
** flagsequence.c / flagsequence_utils.c
*/

int					ft_is_printf_flag(char c);
int					check_max_accepted_value(const char *number);
t_flags				flags_sequence_one(const char *format, size_t *i);
t_flags				flags_sequence_two(const char *format, size_t *i,
					t_flags flags, va_list start);
t_flags				flags_sequence_three(const char *format,
					size_t *i, t_flags flags);

/*
** convert_*.c functions
*/

int					convert_percentage(t_flags flags);
int					convert_character(va_list start, t_flags flags);
int					convert_string(va_list start, t_flags flags);
int					convert_pointer(va_list start, t_flags flags);
int					convert_digit(va_list start, t_flags flags);
int					convert_udigit(va_list start, t_flags flags);
int					convert_hex(va_list start, t_flags flags, int upcase);
int					convert_n(va_list start, t_flags flags, int n);

/*
** ft_putnbr_hex.c
** conversion_utils.c
** I will put these functions in libft.
*/

int					put_field_width(int field_width, int zero);
// better version of put_field_width.
int					put_fw(int field_width, int zero);
unsigned long long	get_unsigned_nbr(va_list start, t_flags flags);

#endif

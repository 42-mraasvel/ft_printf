/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/24 14:58:40 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/10/31 16:24:32 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*src;

	src = s;
	while (n > 0)
	{
		*src = c;
		src++;
		n--;
	}
	return (s);
}
